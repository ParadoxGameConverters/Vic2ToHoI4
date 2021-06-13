#include "OutHoi4World.h"
#include "Decisions/OutDecisions.h"
#include "Diplomacy/OutAiPeaces.h"
#include "Events/OutEvents.h"
#include "GameRules/OutGameRules.h"
#include "Ideas/OutIdeas.h"
#include "Ideologies/OutIdeologies.h"
#include "IntelligenceAgencies/OutIntelligenceAgencies.h"
#include "Log.h"
#include "Map/OutBuildings.h"
#include "Map/OutStrategicRegions.h"
#include "Map/OutSupplyZones.h"
#include "Modifiers/OutDynamicModifiers.h"
#include "OSCompatibilityLayer.h"
#include "OccupationLaws/OutOccupationLaws.h"
#include "Operations/OutOperations.h"
#include "OperativeNames/OutOperativeNames.h"
#include "OutFocusTree.h"
#include "OutHoi4/Interface/OutMonarchsInterface.h"
#include "OutHoi4Country.h"
#include "OutLocalisation.h"
#include "OutOnActions.h"
#include "ScriptedEffects/OutScriptedEffects.h"
#include "ScriptedLocalisations/OutScriptedLocalisations.h"
#include "ScriptedTriggers/OutScriptedTriggers.h"
#include "Sounds/OutSounds.h"
#include "States/OutHoI4States.h"
#include "outDifficultySettings.h"
#include <fstream>
#include <iterator>
#include <optional>
#include "CountryCategories/OutCountryCategories.h"


namespace HoI4
{

void reportIndustryLevels(const World& world, const Configuration& theConfiguration);
void reportcountriesIndustry(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void reportDefaultIndustry(const World& world);
std::pair<std::string, std::array<int, 3>> getDefaultStateIndustry(const DefaultState& state);
void reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countriesIndustry);

void outputCommonCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName);
void outputColorsFile(const std::map<std::string, std::shared_ptr<Country>>& countries, const std::string& outputName);
void outputNames(const Names& names,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName);
void outputUnitNames(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const Configuration& theConfiguration);
void outputMap(const States& states, const StrategicRegions& strategicRegions, const std::string& outputName);
void outputGenericFocusTree(const HoI4FocusTree& genericFocusTree, const std::string& outputName);
void outputCountries(const std::set<Advisor>& activeIdeologicalAdvisors,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 const std::string& outputName,
	 const Configuration& theConfiguration);
void outputRelations(const std::string& outputName);
void outputLeaderTraits(const std::map<std::string, std::vector<std::string>>& ideologicalLeaderTraits,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName);
void outputBookmarks(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::optional<std::string> humanCountry,
	 const date& vic2Date,
	 const std::string& outputName);

} // namespace HoI4


void HoI4::reportIndustryLevels(const World& world, const Configuration& theConfiguration)
{
	if (theConfiguration.getDebug())
	{
		reportcountriesIndustry(world.getCountries());
		reportDefaultIndustry(world);
	}
}


void HoI4::reportcountriesIndustry(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	std::ofstream report("convertedIndustry.csv");
	if (report.is_open())
	{
		report << "tag,military factories,civilian factories,dockyards,total factories\n";
		for (const auto& country: countries)
		{
			reportIndustry(report, *country.second);
		}
	}
}


void HoI4::reportDefaultIndustry(const World& world)
{
	std::map<std::string, std::array<int, 3>> countriesIndustry;

	for (const auto& state: world.getTheStates().getDefaultStates())
	{
		auto stateData = getDefaultStateIndustry(state.second);
		if (auto countryIndustry = countriesIndustry.find(stateData.first); countryIndustry == countriesIndustry.end())
		{
			countriesIndustry.insert(make_pair(stateData.first, stateData.second));
		}
		else
		{
			countryIndustry->second[0] += stateData.second[0];
			countryIndustry->second[1] += stateData.second[1];
			countryIndustry->second[2] += stateData.second[2];
		}
	}

	reportDefaultIndustry(countriesIndustry);
}


void HoI4::reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countriesIndustry)
{
	std::ofstream report("defaultIndustry.csv");
	if (!report.is_open())
	{
		throw std::runtime_error("Could not open defaultIndustry.csv");
	}

	if (report.is_open())
	{
		report << "tag,military factories,civilian factories,dockyards,total factories\n";
		for (const auto& country: countriesIndustry)
		{
			report << country.first << ',';
			report << country.second[0] << ',';
			report << country.second[1] << ',';
			report << country.second[2] << ',';
			report << country.second[0] + country.second[1] + country.second[2] << '\n';
		}
	}
}


std::pair<std::string, std::array<int, 3>> HoI4::getDefaultStateIndustry(const DefaultState& state)
{
	const auto civilianFactories = state.getCivFactories();
	const auto militaryFactories = state.getMilFactories();
	const auto dockyards = state.getDockyards();

	auto owner = state.getOwner();

	std::array<int, 3> industry = {militaryFactories, civilianFactories, dockyards};
	auto stateData = std::make_pair(owner, industry);

	return stateData;
}


void HoI4::OutputWorld(const World& world,
	 const std::string& outputName,
	 const bool debugEnabled,
	 const Configuration& theConfiguration)
{
	reportIndustryLevels(world, theConfiguration);

	Log(LogLevel::Info) << "\tOutputting world";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/history"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history");
	}

	outputCommonCountries(world.getCountries(), outputName);
	outputColorsFile(world.getCountries(), outputName);
	outputNames(world.getNames(), world.getCountries(), outputName);
	outputUnitNames(world.getCountries(), theConfiguration);
	outputLocalisation(world.getLocalisation(), outputName);
	outputStates(world.getTheStates(), outputName, debugEnabled);
	outputMap(world.getTheStates(), world.getStrategicRegions(), outputName);
	outputSupplyZones(world.getSupplyZones(), outputName);
	outputRelations(outputName);
	outputGenericFocusTree(world.getGenericFocusTree(), outputName);
	outputCountries(world.getActiveIdeologicalAdvisors(),
		 world.getCountries(),
		 world.getMilitaryMappings(),
		 outputName,
		 theConfiguration);
	outputBuildings(world.getBuildings(), outputName);
	outputDecisions(world.getDecisions(), world.getMajorIdeologies(), outputName);
	outputEvents(world.getEvents(), outputName);
	outputOnActions(world.getOnActions(), world.getMajorIdeologies(), outputName);
	outAiPeaces(world.getPeaces(), world.getMajorIdeologies(), outputName);
	outputIdeologies(world.getIdeologies(), outputName);
	outputLeaderTraits(world.getIdeologicalLeaderTraits(), world.getMajorIdeologies(), outputName);
	outIdeas(world.getTheIdeas(), world.getMajorIdeologies(), world.getCountries(), outputName);
	outDynamicModifiers(world.getDynamicModifiers(), theConfiguration);
	outputBookmarks(world.getGreatPowers(), world.getCountries(), world.getHumanCountry(), world.getDate(), outputName);
	outputScriptedLocalisations(outputName, *world.getScriptedLocalisations());
	outputScriptedTriggers(world.getScriptedTriggers(), outputName);
	outputDifficultySettings(world.getGreatPowers(), outputName);
	outputGameRules(world.getGameRules(), outputName);
	outputOccupationLaws(world.getOccupationLaws(), theConfiguration);
	outputIntelligenceAgencies(*world.getIntelligenceAgencies(), outputName);
	outputOperativeNames(world.getOperativeNames(), outputName);
	outputOperations(world.getOperations(), outputName);
	outputScriptedEffects(world.getScriptedEffects(), world.getMajorIdeologies(), outputName);
	outCountryCategories(world.getCountryCategories(), outputName);
	outputSounds(outputName, world.getSoundEffects());
	outMonarchInterface(outputName, world.getCountries());
}


void HoI4::outputCommonCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tCreating country tags";
	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/country_tags"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/country_tags");
	}

	std::ofstream allCountriesFile("output/" + outputName + "/common/country_tags/00_countries.txt");
	if (!allCountriesFile.is_open())
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/country_tags/00_countries.txt");
	}

	for (const auto& country: countries)
	{
		if (country.second->isGreatPower() && country.second->getCapitalState())
		{
			outputToCommonCountriesFile(allCountriesFile, *country.second);
		}
	}

	for (const auto& country: countries)
	{
		if (!country.second->isGreatPower() && country.second->getCapitalState())
		{
			outputToCommonCountriesFile(allCountriesFile, *country.second);
		}
	}

	allCountriesFile << "\n";
	allCountriesFile.close();
}


void HoI4::outputColorsFile(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting country colors";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/countries"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/countries");
	}

	std::ofstream output("output/" + outputName + "/common/countries/colors.txt");
	if (!output.is_open())
	{
		throw std::runtime_error("Could not open output/" + outputName + "/common/countries/colors.txt");
	}

	output << "#reload countrycolors\n";
	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputColors(output, *country.second);
		}
	}

	output.close();
}


void HoI4::outputNames(const Names& names,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting names";

	std::ofstream namesFile("output/" + outputName + "/common/names/01_names.txt");
	if (!namesFile.is_open())
	{
		throw std::runtime_error("Could not open output/" + outputName + "/common/names/01_names.txt");
	}

	namesFile << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy

	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputToNamesFiles(namesFile, names, *country.second);
		}
	}
}


void HoI4::outputUnitNames(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\t\tWriting unit names";

	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputToUnitNamesFiles(*country.second, theConfiguration);
		}
	}
}


void HoI4::outputMap(const States& states, const StrategicRegions& strategicRegions, const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting map info";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/map"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/map");
	}

	std::ofstream rocketSitesFile("output/" + outputName + "/map/rocketsites.txt");
	if (!rocketSitesFile.is_open())
	{
		throw std::runtime_error("Could not create output/" + outputName + "/map/rocketsites.txt");
	}
	for (const auto& state: states.getStates())
	{
		if (auto provinces = state.second.getProvinces(); !provinces.empty())
		{
			rocketSitesFile << state.second.getID() << "={" << *provinces.cbegin() << " }\n";
		}
	}
	rocketSitesFile.close();

	outputStrategicRegions(strategicRegions, outputName);
}


void HoI4::outputGenericFocusTree(const HoI4FocusTree& genericFocusTree, const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting generic focus tree";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/national_focus"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/national_focus");
	}

	outputSharedFocuses(genericFocusTree, "output/" + outputName + "/common/national_focus/shared_focuses.txt");
}


void HoI4::outputCountries(const std::set<Advisor>& activeIdeologicalAdvisors,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 const std::string& outputName,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\t\tWriting countries";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/history"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history");
	}
	if (!commonItems::TryCreateFolder("output/" + outputName + "/history/countries"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history/countries");
	}
	if (!commonItems::TryCreateFolder("output/" + outputName + "/history/states"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history/states");
	}
	if (!commonItems::TryCreateFolder("output/" + outputName + "/history/units"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history/units");
	}

	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			const auto& specificMilitaryMappings = theMilitaryMappings.getMilitaryMappings(theConfiguration.getVic2Mods());
			outputCountry(activeIdeologicalAdvisors,
				 specificMilitaryMappings.getDivisionTemplates(),
				 *country.second,
				 theConfiguration);
		}
	}

	std::ofstream ideasFile("output/" + outputName + "/interface/converter_ideas.gfx");
	if (!ideasFile.is_open())
	{
		throw std::runtime_error("Could not open output/" + outputName + "/interface/converter_ideas.gfx");
	}

	ideasFile << "spriteTypes = {\n";
	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputIdeaGraphics(ideasFile, *country.second);
		}
	}
	ideasFile << "\n";
	ideasFile << "}\n";
	ideasFile.close();

	std::ofstream portraitsFile("output/" + outputName + "/portraits/conv_portraits.txt");
	if (!portraitsFile.is_open())
	{
		throw std::runtime_error("Could not open output/" + outputName + "/interface/conv_portraits.gfx");
	}
	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputPortraits(portraitsFile, *country.second);
		}
	}
	portraitsFile.close();
}


void HoI4::outputRelations(const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting opinion modifiers";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/opinion_modifiers"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/opinion_modifiers/");
	}
	std::ofstream out("output/" + outputName + "/common/opinion_modifiers/01_opinion_modifiers.txt");
	if (!out.is_open())
	{
		throw std::runtime_error(
			 "Could not create output/" + outputName + "/common/opinion_modifiers/01_opinion_modifiers.txt");
	}

	out << "opinion_modifiers = {\n";
	for (auto i = -200; i <= 200; i++)
	{
		if (i < 0)
		{
			out << "negative_";
		}
		else
		{
			out << "positive_";
		}
		out << std::abs(i) << " = {\n";
		out << "\tvalue = " << i << "\n";
		out << "\tdecay = 1\n";
		out << "}\n";
	}
	out << "private_channels_trade = {\n";
	out << "\ttrade = yes\n";
	out << "\tvalue = 15\n";
	out << "}\n";
	out << "absolutist_in_government = {\n";
	out << "\tvalue = 30\n";
	out << "}\n";
	out << "communism_in_government = {\n";
	out << "\tvalue = 30\n";
	out << "}\n";
	out << "fascism_in_government = {\n";
	out << "\tvalue = 30\n";
	out << "}\n";
	out << "radical_in_government = {\n";
	out << "\tvalue = 30\n";
	out << "}\n";

	out << "}\n";

	out.close();
}


void HoI4::outputLeaderTraits(const std::map<std::string, std::vector<std::string>>& ideologicalLeaderTraits,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting leader traits";

	std::ofstream traitsFile("output/" + outputName + "/common/country_leader/converterTraits.txt");
	if (!traitsFile.is_open())
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/country_leader/converterTraits.txt");
	}

	traitsFile << "leader_traits = {\n";
	for (const auto& majorIdeology: majorIdeologies)
	{
		if (auto ideologyTraits = ideologicalLeaderTraits.find(majorIdeology);
			 ideologyTraits != ideologicalLeaderTraits.end())
		{
			for (const auto& trait: ideologyTraits->second)
			{
				traitsFile << "\t";
				traitsFile << trait;
			}
		}
	}
	traitsFile << "}";
	traitsFile.close();
}


void HoI4::outputBookmarks(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::optional<std::string> humanCountry, 
	 const date& vic2Date,
	 const std::string& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting bookmarks";

	const auto outputBookmark = [&](date startDate, const std::string& bookmarkName) 
	{
		std::string uppercaseBookmarkName = bookmarkName;
		std::transform(uppercaseBookmarkName.begin(), uppercaseBookmarkName.end(), uppercaseBookmarkName.begin(), ::toupper);

		std::ofstream bookmarkFile("output/" + outputName + "/common/bookmarks/the_" + bookmarkName + ".txt");
		if (!bookmarkFile.is_open())
		{
			throw std::runtime_error(
				 "Could not create output/" + outputName + "/common/bookmarks/the_" + bookmarkName + ".txt");
		}

		bookmarkFile << "bookmarks = {\n";
		bookmarkFile << "\tbookmark = {\n";
		bookmarkFile << "\t\tname = " + uppercaseBookmarkName + "_NAME\n";
		bookmarkFile << "\t\tdesc = " + uppercaseBookmarkName + "_DESC\n";
		bookmarkFile << "\t\tdate = " + startDate.toString() + ".12\n";

		bookmarkFile << ((startDate.toString() == "1936.1.1") ? "\t\tpicture = GFX_select_date_1936\n" : "\t\tpicture = GFX_select_date_1939\n");


		if (humanCountry)
		{
			bookmarkFile << "\t\tdefault_country = \"" << *humanCountry << "\"\n";
		}
		else
		{
			bookmarkFile << "\t\tdefault_country = \"---\"\n";
		}

		for (const auto& greatPower: greatPowers)
		{
			// Vic2 Great powers become majors in bookmark
			bookmarkFile << "\t\t" + greatPower->getTag() + "= {\n";
			bookmarkFile << "\t\t\thistory = \"" + greatPower->getGovernmentIdeology() + "_GP_CONV_DESC\"\n";
			bookmarkFile << "\t\t\tideology = " + greatPower->getGovernmentIdeology() + "\n";
			bookmarkFile << "\t\t\tideas = { great_power ";
			for (const auto& idea: greatPower->getIdeas())
			{
				bookmarkFile << idea << " ";
			}
			bookmarkFile << "}\n";
			bookmarkFile << "\t\t}\n";
		}

		bookmarkFile << "\t\t\"---\"= {\n";
		bookmarkFile << "\t\t\thistory = \"OTHER_" + uppercaseBookmarkName + "_DESC\"\n";
		bookmarkFile << "\t\t}\n";

		// sort non-GP tags by strength
		std::vector<std::string> tags;
		for (const auto& [tag, country]: countries)
		{
			if (!country->isGreatPower())
			{
				tags.push_back(tag);
			}
		}
		std::sort(tags.begin(), tags.end(), [countries](const std::string& a, const std::string& b) {
			return countries.at(a)->getStrengthOverTime(1.0) > countries.at(b)->getStrengthOverTime(3.0);
		});

		// then remove all but the strongest 22
		auto trimHere = tags.begin();
		std::advance(trimHere, 23);
		tags.erase(trimHere, tags.end());

		// then alphabetize them
		std::sort(tags.begin(), tags.end());

		for (const auto& tag: tags)
		{
			const auto& country = countries.at(tag);

			// add minor countries to the bookmark, only those with custom focus trees are visible due to Hoi4
			// limitations Bookmark window has room for 22 minor countries, going over this seems to not cause any
			// issues however
			bookmarkFile << "\t\t" + country->getTag() + " = {\n";
			bookmarkFile << "\t\t\tminor = yes\n";
			bookmarkFile << "\t\t\thistory = \"" + country->getGovernmentIdeology() + "_SP_CONV_DESC\"\n";
			bookmarkFile << "\t\t\tideology = " + country->getGovernmentIdeology() + "\n";
			bookmarkFile << "\t\t\tideas = { ";
			for (const auto& idea: country->getIdeas())
			{
				bookmarkFile << idea << " ";
			}
			bookmarkFile << "}\n";
			bookmarkFile << "\t\t}\n";
		}

		bookmarkFile << "\t\teffect = {\n";
		bookmarkFile << "\t\t\trandomize_weather = 22345 # <-Obligatory in every bookmark !\n";
		bookmarkFile << "\t\t\t#123 = { rain_light = yes }\n";
		bookmarkFile << "\t\t}\n";
		bookmarkFile << "\t}\n";
		bookmarkFile << "}\n";
		bookmarkFile.close();
	};

	outputBookmark(vic2Date, "grand_campaign");
	outputBookmark(date("1936.1.1"), "gathering_storm");
}
