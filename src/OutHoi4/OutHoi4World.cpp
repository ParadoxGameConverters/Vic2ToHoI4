#include "src/OutHoi4/OutHoi4World.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Collections/OutCollections.h"
#include "src/OutHoi4/Countries/OutUnionCountry.h"
#include "src/OutHoi4/CountryCategories/OutCountryCategories.h"
#include "src/OutHoi4/Decisions/OutDecisions.h"
#include "src/OutHoi4/Events/OutEvents.h"
#include "src/OutHoi4/Factions/OutFactionGoals.h"
#include "src/OutHoi4/Factions/OutFactionRuleGroups.h"
#include "src/OutHoi4/Factions/OutFactionRules.h"
#include "src/OutHoi4/Factions/OutFactionTemplates.h"
#include "src/OutHoi4/GameRules/OutGameRules.h"
#include "src/OutHoi4/Ideas/OutIdeas.h"
#include "src/OutHoi4/Ideologies/OutIdeologies.h"
#include "src/OutHoi4/IntelligenceAgencies/OutIntelligenceAgencies.h"
#include "src/OutHoi4/Interface/OutMonarchsInterface.h"
#include "src/OutHoi4/Landmarks/OutLandmarkBuildings.h"
#include "src/OutHoi4/Leaders/OutAdvisor.h"
#include "src/OutHoi4/Map/OutBuildings.h"
#include "src/OutHoi4/Map/OutRailways.h"
#include "src/OutHoi4/Map/OutStrategicRegions.h"
#include "src/OutHoi4/Map/OutSupplyNodes.h"
#include "src/OutHoi4/Map/OutSupplyZones.h"
#include "src/OutHoi4/Modifiers/OutDynamicModifiers.h"
#include "src/OutHoi4/OccupationLaws/OutOccupationLaws.h"
#include "src/OutHoi4/Operations/OutOperations.h"
#include "src/OutHoi4/OperativeNames/OutOperativeNames.h"
#include "src/OutHoi4/OutFocusTree.h"
#include "src/OutHoi4/OutHoi4Country.h"
#include "src/OutHoi4/OutLocalisation.h"
#include "src/OutHoi4/OutOnActions.h"
#include "src/OutHoi4/PeaceConference/OutAiPeace.h"
#include "src/OutHoi4/PeaceConference/OutCostModifiers.h"
#include "src/OutHoi4/Scorers/OutScorers.h"
#include "src/OutHoi4/ScriptedEffects/OutScriptedEffects.h"
#include "src/OutHoi4/ScriptedLocalisations/OutScriptedLocalisations.h"
#include "src/OutHoi4/ScriptedTriggers/OutScriptedTriggers.h"
#include "src/OutHoi4/Sounds/OutSounds.h"
#include "src/OutHoi4/States/OutHoI4States.h"
#include "src/OutHoi4/UnitMedals/OutUnitMedals.h"
#include "src/OutHoi4/outDifficultySettings.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <optional>
#include <ranges>



namespace HoI4
{

void reportIndustryLevels(const World& world, const Configuration& theConfiguration);
void reportcountriesIndustry(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void reportDefaultIndustry(const World& world);
std::pair<std::string, std::array<int, 3>> getDefaultStateIndustry(const DefaultState& state);
void reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countriesIndustry);

void outputCommonCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName);
void outputColorsFile(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName);
void outputNames(const Names& names,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName);
void outputUnitNames(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const Configuration& theConfiguration);
void outputMap(const States& states, const StrategicRegions& strategicRegions, const std::filesystem::path& outputName);
void outputGenericFocusTree(const HoI4FocusTree& genericFocusTree, const std::filesystem::path& outputName);
void outputCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::vector<UnionCountry>& union_countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 const std::filesystem::path& outputName,
	 const Configuration& theConfiguration);
void outputRelations(const std::filesystem::path& outputName, const std::set<std::string>& majorIdeologies);
void outputLeaderTraits(const std::map<std::string, std::vector<std::string>>& ideologicalLeaderTraits,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName);
void outputBookmarks(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::optional<std::string> humanCountry,
	 const date& vic2Date,
	 const std::filesystem::path& outputName);
void copyAdjustedFocusFiles(const std::filesystem::path& outputName,
	 const std::vector<std::shared_ptr<AdjustedBranch>>& addedBranches);
void outputAdjacencyRules(const std::filesystem::path& outputName,
	 const std::map<std::string, std::shared_ptr<AdjacencyRule>>& rules);

} // namespace HoI4


namespace
{

void outputGenericAdvisors(const std::set<HoI4::Advisor>& advisors, const std::filesystem::path& outputName)
{
	const std::filesystem::path advisors_path = "output" / outputName / "history/general/convertedAdvisors.txt";
	std::ofstream advisorsFile(advisors_path);
	if (!advisorsFile.is_open())
	{
		throw std::runtime_error("Could not create " + advisors_path.string());
	}

	for (const auto& advisor: advisors)
	{
		HoI4::outputAdvisor(advisorsFile, advisor);
		advisorsFile << '\n';
	}

	advisorsFile.close();
}

} // namespace


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
		for (const auto& county: countries | std::views::values)
		{
			reportIndustry(report, *county);
		}
	}
}


void HoI4::reportDefaultIndustry(const World& world)
{
	std::map<std::string, std::array<int, 3>> countriesIndustry;

	for (const auto& state: world.getTheStates().getDefaultStates() | std::views::values)
	{
		auto stateData = getDefaultStateIndustry(state);
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
	 const std::filesystem::path& outputName,
	 const bool debugEnabled,
	 const Configuration& theConfiguration)
{
	reportIndustryLevels(world, theConfiguration);

	Log(LogLevel::Info) << "\tOutputting world";

	const std::filesystem::path history_folder = "output" / outputName / "history";
	if (!commonItems::DoesFolderExist(history_folder) && !std::filesystem::create_directories(history_folder))
	{
		throw std::runtime_error("Could not create " + history_folder.string());
	}

	outputCommonCountries(world.getCountries(), outputName);
	outputColorsFile(world.getCountries(), outputName);
	outputNames(world.getNames(), world.getCountries(), outputName);
	outputUnitNames(world.getCountries(), theConfiguration);
	outputLocalisation(world.getLocalisation(), outputName);
	outputStates(world.getTheStates(), outputName, debugEnabled);
	outputMap(world.getTheStates(), world.getStrategicRegions(), outputName);
	outputSupplyZones(world.getSupplyZones(), outputName);
	outputRelations(outputName, world.getMajorIdeologies());
	outputGenericFocusTree(world.getGenericFocusTree(), outputName);
	outputCountries(world.getCountries(),
		 world.GetUnionCountries(),
		 world.getMilitaryMappings(),
		 outputName,
		 theConfiguration);
	outputBuildings(world.getBuildings(), outputName);
	outputLandmarkBuildings(world.getLandmarkBuildings(), outputName);
	outputSupplyNodes("output" / outputName, world.getSupplyNodes());
	outputRailways("output" / outputName, world.getRailways()->GetRailways());
	outputDecisions(world.getDecisions(), world.getMajorIdeologies(), outputName);
	outputEvents(world.getEvents(), outputName);
	outputOnActions(world.getOnActions(), world.getMajorIdeologies(), outputName);
	outputIdeologies(world.getIdeologies(), outputName);
	outputLeaderTraits(world.getIdeologicalLeaderTraits(), world.getMajorIdeologies(), outputName);
	outputGenericAdvisors(world.getActiveIdeologicalAdvisors(), outputName);
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
	outputScorers(world.getScorers(), theConfiguration);
	outCountryCategories(world.getCountryCategories(), outputName);
	outputSounds(outputName, world.getSoundEffects());
	outMonarchInterface(outputName, world.getCountries());
	copyAdjustedFocusFiles(outputName, world.getAdjustedFocusBranches());
	OutputCostModifiers(outputName, world.getMajorIdeologies(), world.GetIdeologicalCostModifiers());
	OutputAiPeace(outputName, world.getMajorIdeologies(), world.GetIdeologicalAiPeace(), world.GetDynamicAiPeace());
	OutputUnitMedals(outputName, world.getMajorIdeologies(), world.GetUnitMedals());
	outputAdjacencyRules(outputName, world.getAdjacencyRules());
	outputFactionGoals("output" / outputName, world.getIdeologicalFactionGoals(), world.getManifestsVariables());
	outputFactionRules("output" / outputName, world.getIdeologicalFactionRules());
	outputFactionRuleGroups("output" / outputName, world.getIdeologicalFactionRuleGroups());
	outputFactionTemplates("output" / outputName, world.getIdeologicalFactionTemplates());
	outputCollections("output" / outputName, world.getIdeologicalCollections());
}


void HoI4::outputCommonCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tCreating country tags";
	const std::filesystem::path folder = "output" / outputName / "common/country_tags";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path allCountriesFilename = "output" / outputName / "common/country_tags/00_countries.txt";
	std::ofstream allCountriesFile(allCountriesFilename);
	if (!allCountriesFile.is_open())
	{
		throw std::runtime_error("Could not create " + allCountriesFilename.string());
	}

	for (const auto& country: countries | std::views::values)
	{
		if (country->isGreatPower() && country->getCapitalState())
		{
			outputToCommonCountriesFile(allCountriesFile, *country);
		}
	}

	for (const auto& country: countries | std::views::values)
	{
		if (!country->isGreatPower() && country->getCapitalState())
		{
			outputToCommonCountriesFile(allCountriesFile, *country);
		}
	}

	allCountriesFile << "\n";
	allCountriesFile.close();
}


void HoI4::outputColorsFile(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting country colors";

	const std::filesystem::path folder = "output" / outputName / "common/countries";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = "output" / outputName / "common/countries/colors.txt";
	std::ofstream output(file);
	if (!output.is_open())
	{
		throw std::runtime_error("Could not open " + file.string());
	}

	output << "#reload countrycolors\n";
	for (const auto& country: countries | std::views::values)
	{
		if (country->getCapitalState())
		{
			outputColors(output, *country);
		}
	}

	output.close();
}


void HoI4::outputNames(const Names& names,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting names";

	const std::filesystem::path namesFilename = "output" / outputName / "common/names/01_names.txt";
	std::ofstream namesFile(namesFilename);
	if (!namesFile.is_open())
	{
		throw std::runtime_error("Could not open " + namesFilename.string());
	}

	namesFile << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy

	for (const auto& country: countries | std::views::values)
	{
		if (country->getCapitalState())
		{
			outputToNamesFiles(namesFile, names, *country);
		}
	}
}


void HoI4::outputUnitNames(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\t\tWriting unit names";

	for (const auto& country: countries | std::views::values)
	{
		if (country->getCapitalState())
		{
			outputToUnitNamesFiles(*country, theConfiguration);
		}
	}
}


void HoI4::outputMap(const States& states,
	 const StrategicRegions& strategicRegions,
	 const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting map info";

	const std::filesystem::path folder = "output" / outputName / "map";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	outputStrategicRegions(strategicRegions, outputName);
}


void HoI4::outputGenericFocusTree(const HoI4FocusTree& genericFocusTree, const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting generic focus tree";

	const std::filesystem::path folder = "output" / outputName / "common/national_focus";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	outputSharedFocuses(genericFocusTree, folder / "shared_focuses.txt");
}


void HoI4::outputCountries(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::vector<UnionCountry>& union_countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 const std::filesystem::path& outputName,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\t\tWriting countries";

	std::filesystem::path countries_folder = "output" / outputName / "history/countries";
	if (!commonItems::DoesFolderExist(countries_folder) && !std::filesystem::create_directories(countries_folder))
	{
		throw std::runtime_error("Could not create " + countries_folder.string());
	}
	std::filesystem::path states_folder = "output" / outputName / "history/states";
	if (!commonItems::DoesFolderExist(states_folder) && !std::filesystem::create_directories(states_folder))
	{
		throw std::runtime_error("Could not create " + states_folder.string());
	}
	std::filesystem::path units_folder = "output" / outputName / "history/units";
	if (!commonItems::DoesFolderExist(units_folder) && !std::filesystem::create_directories(units_folder))
	{
		throw std::runtime_error("Could not create " + units_folder.string());
	}

	for (const auto& country: countries | std::views::values)
	{
		if (country->getCapitalState())
		{
			const auto& specificMilitaryMappings = theMilitaryMappings.getMilitaryMappings(theConfiguration.getVic2Mods());
			outputCountry(specificMilitaryMappings.getDivisionTemplates(), *country, theConfiguration);
		}
	}

	const std::filesystem::path union_countries_filename = "output" / outputName / "common/countries/cosmetic.txt";
	std::ofstream union_countries_file(union_countries_filename, std::ios::app);
	if (!union_countries_file.is_open())
	{
		throw std::runtime_error("Could not open " + union_countries_filename.string());
	}
	for (const auto& union_country: union_countries)
	{
		union_countries_file << union_country;
	}

	const std::filesystem::path portraitsFilename = "output" / outputName / "portraits/conv_portraits.txt";
	std::ofstream portraitsFile(portraitsFilename);
	if (!portraitsFile.is_open())
	{
		throw std::runtime_error("Could not open " + portraitsFilename.string());
	}
	for (const auto& country: countries | std::views::values)
	{
		if (country->getCapitalState())
		{
			outputPortraits(portraitsFile, *country);
		}
	}
	portraitsFile.close();
}


void HoI4::outputRelations(const std::filesystem::path& outputName, const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\t\tWriting opinion modifiers";

	std::filesystem::path folder = "output" / outputName / "common/opinion_modifiers";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}
	const std::filesystem::path file = folder / "01_opinion_modifiers.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
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
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality" || ideology == "democratic")
		{
			continue;
		}
		out << ideology << "_in_government = {\n";
		out << "\tvalue = 30\n";
		out << "}\n";
	}

	out << "}\n";

	out.close();
}


void HoI4::outputLeaderTraits(const std::map<std::string, std::vector<std::string>>& ideologicalLeaderTraits,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting leader traits";

	const std::filesystem::path file = "output" / outputName / "common/country_leader/converterTraits.txt";
	std::ofstream traitsFile(file);
	if (!traitsFile.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
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
	 const std::filesystem::path& outputName)
{
	Log(LogLevel::Info) << "\t\tWriting bookmarks";

	const auto outputBookmark = [&](date startDate, const std::string& bookmarkName, bool defaultBookmark) {
		std::string uppercaseBookmarkName = bookmarkName;
		std::ranges::transform(uppercaseBookmarkName, uppercaseBookmarkName.begin(), ::toupper);

		std::filesystem::path bookmarkFilename = "output" / outputName / "common/bookmarks/the_";
		bookmarkFilename += bookmarkName;
		bookmarkFilename += ".txt";
		std::ofstream bookmarkFile(bookmarkFilename);
		if (!bookmarkFile.is_open())
		{
			throw std::runtime_error("Could not create " + bookmarkFilename.string());
		}

		bookmarkFile << "bookmarks = {\n";
		bookmarkFile << "\tbookmark = {\n";
		bookmarkFile << "\t\tname = " + uppercaseBookmarkName + "_NAME\n";
		bookmarkFile << "\t\tdesc = " + uppercaseBookmarkName + "_DESC\n";
		bookmarkFile << "\t\tdate = " + startDate.toString() + ".12\n";

		bookmarkFile << ((startDate.toString() == "1936.1.1") ? "\t\tpicture = GFX_select_date_1936\n"
																				: "\t\tpicture = GFX_select_date_1939\n");


		if (humanCountry)
		{
			bookmarkFile << "\t\tdefault_country = \"" << *humanCountry << "\"\n";
		}
		else
		{
			bookmarkFile << "\t\tdefault_country = \"---\"\n";
		}
		if (defaultBookmark)
		{
			bookmarkFile << "\t\tdefault = yes\n";
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
		std::ranges::sort(tags, [countries](const std::string& a, const std::string& b) {
			return countries.at(a)->getStrengthOverTime(1.0) > countries.at(b)->getStrengthOverTime(3.0);
		});

		// then remove all but the strongest 22
		if (tags.size() > 23)
		{
			auto trimHere = tags.begin();
			std::advance(trimHere, 23);
			tags.erase(trimHere, tags.end());
		}

		// then alphabetize them
		std::ranges::sort(tags);

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

	outputBookmark(vic2Date, "grand_campaign", true);

	// Vic2 end dates within diffInDays of 1936.1.1 are considered too close to create another bookmark
	constexpr unsigned int diffInDays = 1;
	if (static_cast<unsigned long>(std::abs(365 * vic2Date.diffInYears(date("1936.1.1")))) > diffInDays)
	{
		outputBookmark(date("1936.1.1"), "gathering_storm", false);
	}
}

void HoI4::copyAdjustedFocusFiles(const std::filesystem::path& outputName,
	 const std::vector<std::shared_ptr<AdjustedBranch>>& addedBranches)
{
	for (const auto& branch: addedBranches)
	{
		std::filesystem::copy(branch->getPath(), "output" / outputName, std::filesystem::copy_options::recursive);
	}
}

void HoI4::outputAdjacencyRules(const std::filesystem::path& outputName,
	 const std::map<std::string, std::shared_ptr<AdjacencyRule>>& adjacencyRules)
{
	const std::filesystem::path folder = "output" / outputName / "map";
	std::filesystem::create_directories(folder);

	const std::filesystem::path filename = "output" / outputName / "map/adjacency_rules.txt";
	std::ofstream outputFile(filename);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Could not create " + filename.string());
	}

	for (const auto& rule: adjacencyRules | std::views::values)
	{
		outputFile << *rule;
	}
	outputFile.close();
}
