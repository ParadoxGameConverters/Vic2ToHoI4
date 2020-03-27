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
void reportCountryIndustry(const World& world);
void reportDefaultIndustry(const World& world);
std::pair<std::string, std::array<int, 3>> getDefaultStateIndustry(const HoI4::DefaultState& state);
void reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countryIndustry);

void outputCommonCountries(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void outputColorsFile(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void outputNames(const HoI4::namesMapper& theNames,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void outputUnitNames(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
void outputMap(const States& states, const std::map<int, HoI4::StrategicRegion*>& strategicRegions);
void outputGenericFocusTree(const std::set<std::string>& majorIdeologies);
void outputCountries(const std::set<HoI4::Advisor>& activeIdeologicalAdvisors,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 HoI4::namesMapper& theNames,
	 graphicsMapper& theGraphics);
void outputRelations();
void outputLeaderTraits(const std::map<std::string, std::vector<std::string>>& ideologicalLeaderTraits,
	 const std::set<std::string>& majorIdeologies);
void outputBookmarks(const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);

} // namespace HoI4


void HoI4::reportIndustryLevels(const World& world)
{
	int militaryFactories = 0;
	int civilialFactories = 0;
	int dockyards = 0;
	for (auto state: world.getStates())
	{
		militaryFactories += state.second.getMilFactories();
		civilialFactories += state.second.getCivFactories();
		dockyards += state.second.getDockyards();
	}

	LOG(LogLevel::Debug) << "Total factories: " << (militaryFactories + civilialFactories + dockyards);
	LOG(LogLevel::Debug) << "\t" << militaryFactories << " military factories";
	LOG(LogLevel::Debug) << "\t" << civilialFactories << " civilian factories";
	LOG(LogLevel::Debug) << "\t" << dockyards << " dockyards";

	if (theConfiguration.getDebug())
	{
		reportCountryIndustry(world);
		reportDefaultIndustry(world);
	}
}


void HoI4::reportCountryIndustry(const World& world)
{
	std::ofstream report("convertedIndustry.csv");
	report << "tag,military factories,civilian factories,dockyards,total factories\n";
	if (report.is_open())
	{
		for (auto country: world.getCountries())
		{
			reportIndustry(report, *country.second);
		}
	}
}


void HoI4::reportDefaultIndustry(const World& world)
{
	std::map<std::string, std::array<int, 3>> countryIndustry;

	for (auto state: world.getTheStates().getDefaultStates())
	{
		std::pair<std::string, std::array<int, 3>> stateData = getDefaultStateIndustry(state.second);

		auto country = countryIndustry.find(stateData.first);
		if (country == countryIndustry.end())
		{
			countryIndustry.insert(make_pair(stateData.first, stateData.second));
		}
		else
		{
			country->second[0] += stateData.second[0];
			country->second[1] += stateData.second[1];
			country->second[2] += stateData.second[2];
		}
	}

	reportDefaultIndustry(countryIndustry);
}


void HoI4::reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countryIndustry)
{
	std::ofstream report("defaultIndustry.csv");
	report << "tag,military factories,civilian factories,dockyards,total factories\n";
	if (report.is_open())
	{
		for (auto country: countryIndustry)
		{
			report << country.first << ',';
			report << country.second[0] << ',';
			report << country.second[1] << ',';
			report << country.second[2] << ',';
			report << country.second[0] + country.second[1] + country.second[2] << '\n';
		}
	}
}


std::pair<std::string, std::array<int, 3>> HoI4::getDefaultStateIndustry(const HoI4::DefaultState& state)
{
	int civilianFactories = state.getCivFactories();
	int militaryFactories = state.getMilFactories();
	int dockyards = state.getDockyards();

	std::string owner = state.getOwner();

	std::array<int, 3> industry = {militaryFactories, civilianFactories, dockyards};
	std::pair<std::string, std::array<int, 3>> stateData = std::make_pair(owner, industry);

	return stateData;
}


void HoI4::OutputWorld(World& world)
{
	reportIndustryLevels(world);

	LOG(LogLevel::Info) << "Outputting world";

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history";
		exit(-1);
	}

	outputCommonCountries(world.getCountries());
	outputColorsFile(world.getCountries());
	outputNames(world.getNames(), world.getCountries());
	outputUnitNames(world.getCountries());
	outputLocalisation(*HoI4Localisation::getInstance(), theConfiguration);
	outputStates(world.getTheStates(), theConfiguration);
	outputMap(world.getTheStates(), world.getStrategicRegions());
	outputSupplyZones(world.getSupplyZones(), theConfiguration);
	outputRelations();
	outputGenericFocusTree(world.getMajorIdeologies());
	outputCountries(world.getActiveIdeologicalAdvisors(),
		 world.getCountries(),
		 world.getMilitaryMappings(),
		 world.getNames(),
		 world.getGraphics());
	outputBuildings(world.getBuildings(), theConfiguration);
	outputDecisions(world.getDecisions(), world.getMajorIdeologies(), theConfiguration);
	outputEvents(world.getEvents(), theConfiguration);
	outputOnActions(world.getOnActions(), world.getMajorIdeologies(), theConfiguration);
	outAiPeaces(world.getPeaces(), world.getMajorIdeologies(), theConfiguration);
	outputIdeologies(world.getIdeologies());
	outputLeaderTraits(world.getIdeologicalLeaderTraits(), world.getMajorIdeologies());
	outIdeas(world.getTheIdeas(), world.getMajorIdeologies(), theConfiguration);
	outputBookmarks(world.getGreatPowers(), world.getCountries());
	outputScriptedLocalisations(theConfiguration, world.getScriptedLocalisations());
	outputScriptedTriggers(world.getScriptedTriggers(), theConfiguration);
	outputDifficultySettings(world.getGreatPowers(), theConfiguration);
	outputGameRules(world.getGameRules(), theConfiguration);
}


void HoI4::outputCommonCountries(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/country_tags"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() +
											 "/common/country_tags\"";
		exit(-1);
	}

	LOG(LogLevel::Debug) << "Writing countries file";
	std::ofstream allCountriesFile(
		 "output/" + theConfiguration.getOutputName() + "/common/country_tags/00_countries.txt");
	if (!allCountriesFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create countries file";
		exit(-1);
	}

	for (auto country: countries)
	{
		if (country.second->isGreatPower() && country.second->getCapitalState())
		{
			outputToCommonCountriesFile(allCountriesFile, *country.second);
		}
	}

	for (auto country: countries)
	{
		if (!country.second->isGreatPower() && country.second->getCapitalState())
		{
			outputToCommonCountriesFile(allCountriesFile, *country.second);
		}
	}

	allCountriesFile << "\n";
	allCountriesFile.close();
}


void HoI4::outputColorsFile(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/countries"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/common/countries\"";
		exit(-1);
	}

	std::ofstream output("output/" + theConfiguration.getOutputName() + "/common/countries/colors.txt");
	if (!output.is_open())
	{
		Log(LogLevel::Error) << "Could not open output/" << theConfiguration.getOutputName()
									<< "/common/countries/colors.txt";
		exit(-1);
	}

	output << "#reload countrycolors\n";
	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputColors(output, *country.second);
		}
	}

	output.close();
}


void HoI4::outputNames(const HoI4::namesMapper& theNames,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	std::ofstream namesFile("output/" + theConfiguration.getOutputName() + "/common/names/01_names.txt");
	namesFile << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy

	if (!namesFile.is_open())
	{
		Log(LogLevel::Error) << "Could not open output/" << theConfiguration.getOutputName()
									<< "/common/names/01_names.txt";
		exit(-1);
	}

	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputToNamesFiles(namesFile, theNames, *country.second);
		}
	}
}


void HoI4::outputUnitNames(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputToUnitNamesFiles(*country.second);
		}
	}
}


void HoI4::outputMap(const States& states, const std::map<int, HoI4::StrategicRegion*>& strategicRegions)
{
	LOG(LogLevel::Debug) << "Writing Map Info";

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/map"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/map";
		exit(-1);
	}

	std::ofstream rocketSitesFile("output/" + theConfiguration.getOutputName() + "/map/rocketsites.txt");
	if (!rocketSitesFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create output/" << theConfiguration.getOutputName() << "/map/rocketsites.txt";
		exit(-1);
	}
	for (auto state: states.getStates())
	{
		auto provinces = state.second.getProvinces();
		rocketSitesFile << state.second.getID() << "={" << *provinces.begin() << " }\n";
	}
	rocketSitesFile.close();

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/map/strategicregions"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/map/strategicregions";
		exit(-1);
	}
	for (auto strategicRegion: strategicRegions)
	{
		outputStrategicRegion(*strategicRegion.second,
			 "output/" + theConfiguration.getOutputName() + "/map/strategicregions/");
	}
}


void HoI4::outputGenericFocusTree(const std::set<std::string>& majorIdeologies)
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/national_focus"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() +
											 "/common/national_focus\"";
		exit(-1);
	}

	HoI4FocusTree genericFocusTree;
	genericFocusTree.addGenericFocusTree(majorIdeologies);
	outputSharedFocuses(genericFocusTree,
		 "output/" + theConfiguration.getOutputName() + "/common/national_focus/shared_focuses.txt");
}


void HoI4::outputCountries(const std::set<HoI4::Advisor>& activeIdeologicalAdvisors,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const allMilitaryMappings& theMilitaryMappings,
	 HoI4::namesMapper& theNames,
	 graphicsMapper& theGraphics)
{
	LOG(LogLevel::Debug) << "Writing countries";
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history";
		exit(-1);
	}
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history/countries"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history";
		exit(-1);
	}
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history/states"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history/states";
		exit(-1);
	}
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history/units"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history/units";
		exit(-1);
	}

	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			const HoI4::militaryMappings& specificMilitaryMappings =
				 theMilitaryMappings.getMilitaryMappings(theConfiguration.getVic2Mods());
			HoI4::outputCountry(activeIdeologicalAdvisors,
				 specificMilitaryMappings.getDivisionTemplates(),
				 theNames,
				 theGraphics,
				 *country.second);
		}
	}

	std::ofstream ideasFile("output/" + theConfiguration.getOutputName() + "/interface/converter_ideas.gfx");
	if (!ideasFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not open output/" << theConfiguration.getOutputName() << "/interface/ideas.gfx";
		exit(-1);
	}

	ideasFile << "spriteTypes = {\n";
	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputIdeaGraphics(ideasFile, theGraphics, *country.second);
		}
	}
	ideasFile << "\n";
	ideasFile << "}\n";
}


void HoI4::outputRelations()
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/opinion_modifiers"))
	{
		Log(LogLevel::Error) << "Could not create output/" + theConfiguration.getOutputName() +
											 "/common/opinion_modifiers/";
		exit(-1);
	}

	std::ofstream out(
		 "output/" + theConfiguration.getOutputName() + "/common/opinion_modifiers/01_opinion_modifiers.txt");
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not create 01_opinion_modifiers.txt.";
		exit(-1);
	}

	out << "opinion_modifiers = {\n";
	for (int i = -200; i <= 200; i++)
	{
		if (i < 0)
		{
			out << "negative_";
		}
		else
		{
			out << "positive_";
		}
		out << abs(i) << " = {\n";
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
	 const std::set<std::string>& majorIdeologies)
{
	std::ofstream traitsFile(
		 "output/" + theConfiguration.getOutputName() + "/common/country_leader/converterTraits.txt");
	traitsFile << "leader_traits = {\n";
	for (const auto& majorIdeology: majorIdeologies)
	{
		auto ideologyTraits = ideologicalLeaderTraits.find(majorIdeology);
		if (ideologyTraits != ideologicalLeaderTraits.end())
		{
			for (auto trait: ideologyTraits->second)
			{
				traitsFile << "\t";
				traitsFile << trait;
			}
		}
	}
	traitsFile << "}";
	traitsFile.close();
}


void HoI4::outputBookmarks(const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	std::ofstream bookmarkFile(
		 "output/" + theConfiguration.getOutputName() + "/common/bookmarks/the_gathering_storm.txt");

	bookmarkFile << "bookmarks = {\n";
	bookmarkFile << "	bookmark = {\n";
	bookmarkFile << "		name = "
						 "GATHERING_STORM_NAME"
						 "\n";
	bookmarkFile << "		desc = "
						 "GATHERING_STORM_DESC"
						 "\n";
	bookmarkFile << "		date = 1936.1.1.12\n";
	bookmarkFile << "		picture = "
						 "GFX_select_date_1936"
						 "\n";
	bookmarkFile << "		default_country = \"---\"\n";
	bookmarkFile << "		default = yes\n";

	for (auto greatPower: greatPowers)
	{
		// Vic2 Great powers become majors in bookmark
		bookmarkFile << "		" + greatPower->getTag() + "= {\n";
		bookmarkFile << "			history = \"OTHER_GATHERING_STORM_DESC\"\n";
		bookmarkFile << "			ideology = " + greatPower->getGovernmentIdeology() + "\n";
		bookmarkFile << "			ideas = { great_power }\n";
		bookmarkFile << "		}\n";
	}

	bookmarkFile << "		\"---\"= {\n";
	bookmarkFile << "			history = \"OTHER_GATHERING_STORM_DESC\"\n";
	bookmarkFile << "		}\n";

	for (auto country: countries)
	{
		if (country.second->isGreatPower() != true)
		{
			if (country.second->getStrengthOverTime(3) > 4500)
			{
				// add minor countries to the bookmark, only those with custom focustree are visible due to Hoi4 limitations
				// Bookmark window has room for 22 minor countries, going over this seems to not cause any issues however
				bookmarkFile << "		" + country.second->getTag() + " = {\n";
				bookmarkFile << "			minor = yes\n";
				bookmarkFile << "			history = \"OTHER_GATHERING_STORM_DESC\"\n";
				bookmarkFile << "			ideology = " + country.second->getGovernmentIdeology() + "\n";
				bookmarkFile << "			ideas = { }\n";
				bookmarkFile << "		}\n";
			}
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