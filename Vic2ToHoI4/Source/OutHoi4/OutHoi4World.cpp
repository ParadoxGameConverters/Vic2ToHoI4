#include "OutHoi4World.h"
#include "../OutHoi4/Decisions/OutDecisions.h"
#include "../OutHoi4/Diplomacy/OutAiPeaces.h"
#include "../OutHoi4/Events/OutEvents.h"
#include "../OutHoi4/GameRules/OutGameRules.h"
#include "../OutHoi4/Ideas/OutIdeas.h"
#include "../OutHoi4/Ideologies/OutIdeologies.h"
#include "../OutHoi4/Map/OutBuildings.h"
#include "../OutHoi4/Map/OutStrategicRegion.h"
#include "../OutHoi4/Map/OutSupplyZones.h"
#include "../OutHoi4/OutFocusTree.h"
#include "../OutHoi4/OutHoi4Country.h"
#include "../OutHoi4/OutLocalisation.h"
#include "../OutHoi4/OutOnActions.h"
#include "../OutHoi4/ScriptedLocalisations/OutScriptedLocalisations.h"
#include "../OutHoi4/ScriptedTriggers/OutScriptedTriggers.h"
#include "../OutHoi4/States/OutHoI4States.h"
#include "../OutHoi4/outDifficultySettings.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



namespace HoI4
{

void reportIndustryLevels(const World& world);
void reportcountriesIndustry(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void reportDefaultIndustry(const World& world);
std::pair<std::string, std::array<int, 3>> getDefaultStateIndustry(const DefaultState& state);
void reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countriesIndustry);

void outputCommonCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName);
void outputColorsFile(const std::map<std::string, std::shared_ptr<Country>>& countries, const std::string& outputName);
void outputNames(const namesMapper& theNames,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName);
void outputUnitNames(const std::map<std::string, std::shared_ptr<Country>>& countries);
void outputMap(const States& states,
	 const std::map<int, StrategicRegion*>& strategicRegions,
	 const std::string& outputName);
void outputGenericFocusTree(const HoI4FocusTree& genericFocusTree, const std::string& outputName);
void outputCountries(const std::set<Advisor>& activeIdeologicalAdvisors,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 const std::string& outputName);
void outputRelations(const std::string& outputName);
void outputLeaderTraits(const std::map<std::string, std::vector<std::string>>& ideologicalLeaderTraits,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName);
void outputBookmarks(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName);

} // namespace HoI4


void HoI4::reportIndustryLevels(const World& world)
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


void HoI4::OutputWorld(const World& world, const std::string& outputName, const bool debugEnabled)
{
	reportIndustryLevels(world);

	LOG(LogLevel::Info) << "\tOutputting world";

	if (!Utils::TryCreateFolder("output/" + outputName + "/history"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history");
	}

	outputCommonCountries(world.getCountries(), outputName);
	outputColorsFile(world.getCountries(), outputName);
	outputNames(world.getNames(), world.getCountries(), outputName);
	outputUnitNames(world.getCountries());
	outputLocalisation(*HoI4Localisation::getInstance(), outputName);
	outputStates(world.getTheStates(), outputName, debugEnabled);
	outputMap(world.getTheStates(), world.getStrategicRegions(), outputName);
	outputSupplyZones(world.getSupplyZones(), outputName);
	outputRelations(outputName);
	outputGenericFocusTree(world.getGenericFocusTree(), outputName);
	outputCountries(world.getActiveIdeologicalAdvisors(), world.getCountries(), world.getMilitaryMappings(), outputName);
	outputBuildings(world.getBuildings(), outputName);
	outputDecisions(world.getDecisions(), world.getMajorIdeologies(), outputName);
	outputEvents(world.getEvents(), outputName);
	outputOnActions(world.getOnActions(), world.getMajorIdeologies(), outputName);
	outAiPeaces(world.getPeaces(), world.getMajorIdeologies(), outputName);
	outputIdeologies(world.getIdeologies(), outputName);
	outputLeaderTraits(world.getIdeologicalLeaderTraits(), world.getMajorIdeologies(), outputName);
	outIdeas(world.getTheIdeas(), world.getMajorIdeologies(), outputName);
	outputBookmarks(world.getGreatPowers(), world.getCountries(), outputName);
	outputScriptedLocalisations(outputName, world.getScriptedLocalisations());
	outputScriptedTriggers(world.getScriptedTriggers(), outputName);
	outputDifficultySettings(world.getGreatPowers(), outputName);
	outputGameRules(world.getGameRules(), outputName);
}


void HoI4::outputCommonCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tCreating country tags";
	if (!Utils::TryCreateFolder("output/" + outputName + "/common/country_tags"))
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
	LOG(LogLevel::Info) << "\t\tWriting country colors";

	if (!Utils::TryCreateFolder("output/" + outputName + "/common/countries"))
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


void HoI4::outputNames(const namesMapper& theNames,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tWriting names";

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
			outputToNamesFiles(namesFile, theNames, *country.second);
		}
	}
}


void HoI4::outputUnitNames(const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	LOG(LogLevel::Info) << "\t\tWriting unit names";

	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputToUnitNamesFiles(*country.second);
		}
	}
}


void HoI4::outputMap(const States& states,
	 const std::map<int, StrategicRegion*>& strategicRegions,
	 const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tWriting map info";

	if (!Utils::TryCreateFolder("output/" + outputName + "/map"))
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

	if (!Utils::TryCreateFolder("output/" + outputName + "/map/strategicregions"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/map/strategicregions");
	}
	for (const auto& strategicRegion: strategicRegions)
	{
		outputStrategicRegion(*strategicRegion.second, "output/" + outputName + "/map/strategicregions/");
	}
}


void HoI4::outputGenericFocusTree(const HoI4FocusTree& genericFocusTree, const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tWriting generic focus tree";

	if (!Utils::TryCreateFolder("output/" + outputName + "/common/national_focus"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/national_focus");
	}

	outputSharedFocuses(genericFocusTree, "output/" + outputName + "/common/national_focus/shared_focuses.txt");
}


void HoI4::outputCountries(const std::set<Advisor>& activeIdeologicalAdvisors,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tWriting countries";

	if (!Utils::TryCreateFolder("output/" + outputName + "/history"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history");
	}
	if (!Utils::TryCreateFolder("output/" + outputName + "/history/countries"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history/countries");
	}
	if (!Utils::TryCreateFolder("output/" + outputName + "/history/states"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history/states");
	}
	if (!Utils::TryCreateFolder("output/" + outputName + "/history/units"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/history/units");
	}

	for (const auto& country: countries)
	{
		if (country.second->getCapitalState())
		{
			const auto& specificMilitaryMappings = theMilitaryMappings.getMilitaryMappings(theConfiguration.getVic2Mods());
			outputCountry(activeIdeologicalAdvisors, specificMilitaryMappings.getDivisionTemplates(), *country.second);
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
}


void HoI4::outputRelations(const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tWriting opinion modifiers";

	if (!Utils::TryCreateFolder("output/" + outputName + "/common/opinion_modifiers"))
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
	LOG(LogLevel::Info) << "\t\tWriting leader traits";

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
	 const std::string& outputName)
{
	LOG(LogLevel::Info) << "\t\tWriting bookmarks";

	std::ofstream bookmarkFile("output/" + outputName + "/common/bookmarks/the_gathering_storm.txt");
	if (!bookmarkFile.is_open())
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/bookmarks/the_gathering_storm.txt");
	}

	bookmarkFile << "bookmarks = {\n";
	bookmarkFile << "\tbookmark = {\n";
	bookmarkFile << "\t\tname = GATHERING_STORM_NAME\n";
	bookmarkFile << "\t\tdesc = GATHERING_STORM_DESC\n";
	bookmarkFile << "\t\tdate = 1936.1.1.12\n";
	bookmarkFile << "\t\tpicture = GFX_select_date_1936\n";
	bookmarkFile << "\t\tdefault_country = \"---\"\n";
	bookmarkFile << "\t\tdefault = yes\n";

	for (const auto& greatPower: greatPowers)
	{
		// Vic2 Great powers become majors in bookmark
		bookmarkFile << "\t\t" + greatPower->getTag() + "= {\n";
		bookmarkFile << "\t\t\thistory = \"" + greatPower->getGovernmentIdeology() + "_GP_CONV_DESC\"\n";
		bookmarkFile << "\t\t\tideology = " + greatPower->getGovernmentIdeology() + "\n";
		bookmarkFile << "\t\t\tideas = { great_power }\n";
		bookmarkFile << "\t\t}\n";
	}

	bookmarkFile << "\t\t\"---\"= {\n";
	bookmarkFile << "\t\t\thistory = \"OTHER_GATHERING_STORM_DESC\"\n";
	bookmarkFile << "\t\t}\n";

	for (const auto& country: countries)
	{
		if (!country.second->isGreatPower() && (country.second->getStrengthOverTime(3) > 4500))
		{
			// add minor countries to the bookmark, only those with custom focus trees are visible due to Hoi4
			// limitations Bookmark window has room for 22 minor countries, going over this seems to not cause any
			// issues however
			bookmarkFile << "\t\t" + country.second->getTag() + " = {\n";
			bookmarkFile << "\t\t\tminor = yes\n";
			bookmarkFile << "\t\t\thistory = \"" + country.second->getGovernmentIdeology() + "_SP_CONV_DESC\"\n";
			bookmarkFile << "\t\t\tideology = " + country.second->getGovernmentIdeology() + "\n";
			bookmarkFile << "\t\t\tideas = { }\n";
			bookmarkFile << "\t\t}\n";
		}
	}

	bookmarkFile << "\t\teffect = {\n";
	bookmarkFile << "\t\t\trandomize_weather = 22345 # <-Obligatory in every bookmark !\n";
	bookmarkFile << "\t\t\t#123 = { rain_light = yes }\n";
	bookmarkFile << "\t\t}\n";
	bookmarkFile << "\t}\n";
	bookmarkFile << "}\n";
	bookmarkFile.close();
}
