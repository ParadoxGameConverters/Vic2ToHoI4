#include "Diplomacy/AiPeacesUpdater.h"
#include "Diplomacy/Faction.h"
#include "HoI4World.h"
#include "WarCreator/HoI4WarCreator.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "../Configuration.h"
#include "../V2World/Diplomacy.h"
#include "../V2World/Party.h"
#include "HoI4Country.h"
#include "Decisions/Decisions.h"
#include "Events/Events.h"
#include "Events/GovernmentInExileEvent.h"
#include "HoI4FocusTree.h"
#include "Ideologies/Ideology.h"
#include "HoI4Localisation.h"
#include "Ideas/Ideas.h"
#include "Ideologies/IdeologyFile.h"
#include "Leaders/Advisor.h"
#include "Leaders/IdeologicalAdvisors.h"
#include "Names.h"
#include "Map/Buildings.h"
#include "Map/StrategicRegion.h"
#include "Map/SupplyZones.h"
#include "MilitaryMappings/MilitaryMappingsFile.h"
#include "ScriptedTriggers/ScriptedTriggersUpdater.h"
#include "ShipTypes/PossibleShipVariants.h"
#include "States/DefaultState.h"
#include "States/HoI4State.h"
#include "States/StateCategories.h"
#include "../V2World/Agreement.h"
#include "../V2World/Country.h"
#include "../V2World/World.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/TechMapper.h"
#include "../Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "ParserHelpers.h"
#include "../Hoi4Outputter/Hoi4CountryOutputter.h"
#include "../Hoi4Outputter/Decisions/DecisionsOutputter.h"
#include "../Hoi4Outputter/Diplomacy/OutAiPeaces.h"
#include "../Hoi4Outputter/Events/EventsOutputter.h"
#include "../Hoi4Outputter/Ideas/OutIdeas.h"
#include "../Hoi4Outputter/Map/OutBuildings.h"
#include "../Hoi4Outputter/Map/OutStrategicRegion.h"
#include "../Hoi4Outputter/Map/OutSupplyZones.h"
#include "../Hoi4Outputter/ScriptedLocalisations/ScriptedLocalisationsOutputter.h"
#include "../Hoi4Outputter/ScriptedTriggers/OutScriptedTriggers.h"
#include "../Hoi4Outputter/States/HoI4StatesOutputter.h"
#include <fstream>
#include "../Hoi4Outputter/outDifficultySettings.h"
#include "../Hoi4Outputter/Ideologies/OutIdeologies.h"
using namespace std;



HoI4::World::World(const Vic2::World* _sourceWorld):
	 sourceWorld(_sourceWorld), countryMap(_sourceWorld), theIdeas(std::make_unique<HoI4::Ideas>()),
	 decisions(make_unique<HoI4::decisions>(theConfiguration)), peaces(make_unique<HoI4::AiPeaces>()),
	 events(new HoI4::Events), onActions(make_unique<HoI4::OnActions>())
{
	LOG(LogLevel::Info) << "Parsing HoI4 data";

	theCoastalProvinces.init(theMapData);
	states = std::make_unique<States>(sourceWorld, countryMap, theCoastalProvinces);
	supplyZones = new HoI4::SupplyZones(states->getDefaultStates());
	buildings = new Buildings(*states, theCoastalProvinces, theMapData), theNames.init();
	theGraphics.init();
	governmentMap.init();
	convertCountries();
	addStatesToCountries();
	states->addCapitalsToStates(countries);
	HoI4Localisation::addStateLocalisations(*states);
	convertIndustry();
	states->convertResources();
	supplyZones->convertSupplyZones(*states);
	convertStrategicRegions();
	convertDiplomacy();
	convertTechs();

	militaryMappingsFile importedMilitaryMappings;
	theMilitaryMappings = importedMilitaryMappings.takeAllMilitaryMappings();
	convertMilitaries();

	determineGreatPowers();

	setupNavalTreaty();

	importLeaderTraits();
	convertGovernments();
	ideologies = std::make_unique<Ideologies>(theConfiguration);
	ideologies->identifyMajorIdeologies(greatPowers, countries);
	importIdeologicalMinisters();
	convertParties();
	events->createPoliticalEvents(ideologies->getMajorIdeologies());
	events->createWarJustificationEvents(ideologies->getMajorIdeologies());
	events->importElectionEvents(ideologies->getMajorIdeologies(), *onActions);
	addCountryElectionEvents(ideologies->getMajorIdeologies());
	events->createStabilityEvents(ideologies->getMajorIdeologies());
	events->generateGenericEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->giveGovernmentInExileEvent(createGovernmentInExileEvent(ideologies->getMajorIdeologies()));
	theIdeas->updateIdeas(ideologies->getMajorIdeologies());
	decisions->updateDecisions(ideologies->getMajorIdeologies(),
		 states->getProvinceToStateIDMap(),
		 states->getDefaultStates(),
		 *events);
	updateAiPeaces(*peaces, ideologies->getMajorIdeologies());
	addNeutrality();
	convertIdeologySupport();
	states->convertCapitalVPs(countries, greatPowers, getStrongestCountryStrength());
	states->convertAirBases(countries, greatPowers);
	if (theConfiguration.getCreateFactions())
	{
		createFactions();
	}

	HoI4WarCreator warCreator(this, theMapData);

	addFocusTrees();
	adjustResearchFocuses();
	HoI4Localisation::generateCustomLocalisations(scriptedLocalisations, ideologies->getMajorIdeologies());

	setSphereLeaders();
	processInfluence();
	determineSpherelings();
	calculateSpherelingAutonomy();
	scriptedTriggers.importScriptedTriggers(theConfiguration);
	updateScriptedTriggers(scriptedTriggers, ideologies->getMajorIdeologies());
}


shared_ptr<HoI4::Country> HoI4::World::findCountry(const string& countryTag)
{
	auto country = countries.find(countryTag);
	if (country == countries.end())
	{
		return {};
	}

	return country->second;
}


void HoI4::World::convertCountries()
{
	LOG(LogLevel::Info) << "Converting countries";

	std::ifstream flagToIdeasMappingFile("DataFiles/FlagsToIdeasMappings.txt");
	mappers::FlagsToIdeasMapper flagsToIdeasMapper(flagToIdeasMappingFile);
	flagToIdeasMappingFile.close();

	for (auto sourceItr: sourceWorld->getCountries())
	{
		convertCountry(sourceItr, flagsToIdeasMapper);
	}

	HoI4Localisation::addNonenglishCountryLocalisations();
}


void HoI4::World::convertCountry(
	std::pair<std::string, Vic2::Country*> country,
	const mappers::FlagsToIdeasMapper& flagsToIdeasMapper
) {
	// don't convert rebels
	if (country.first == "REB")
	{
		return;
	}

	HoI4::Country* destCountry = nullptr;
	auto possibleHoI4Tag = countryMap.getHoI4Tag(country.first);
	if (!possibleHoI4Tag)
	{
		LOG(LogLevel::Warning) << "Could not convert V2 tag " << country.first << " to HoI4";
	}
	else
	{
		destCountry = new HoI4::Country(
			*possibleHoI4Tag,
			country.second,
			theNames,
			theGraphics,
			countryMap,
			flagsToIdeasMapper
		);
		countries.insert(make_pair(*possibleHoI4Tag, destCountry));
		HoI4Localisation::createCountryLocalisations(make_pair(country.first, *possibleHoI4Tag), governmentMap);
		HoI4Localisation::updateMainCountryLocalisation(destCountry->getTag() + "_" + destCountry->getGovernmentIdeology(), country.first, country.second->getGovernment());
	}
}


void HoI4::World::importLeaderTraits()
{
	clearRegisteredKeywords();
	registerKeyword(std::regex("[a-z]+"), [this](const std::string& ideologyName, std::istream& theStream){
		commonItems::stringsOfItems traits(theStream);
		ideologicalLeaderTraits.insert(make_pair(ideologyName, traits.getStrings()));
	});
	parseFile("converterLeaderTraits.txt");
}


void HoI4::World::importIdeologicalMinisters()
{
	HoI4::IdeologicalAdvisors theAdvisors;
	auto theAcutalAdvisors = theAdvisors.getAdvisors();
	ideologicalAdvisors.swap(theAcutalAdvisors);
}


void HoI4::World::convertGovernments()
{
	for (auto country: countries)
	{
		country.second->convertGovernment(*sourceWorld, governmentMap);
	}
}


void HoI4::World::convertParties()
{
	for (auto country: countries)
	{
		country.second->convertParties(ideologies->getMajorIdeologies(), governmentMap);
	}
}


void HoI4::World::addNeutrality()
{
	for (auto country: countries)
	{
		if (ideologies->getMajorIdeologies().count(country.second->getGovernmentIdeology()) == 0)
		{
			country.second->setGovernmentToExistingIdeology(ideologies->getMajorIdeologies(), *ideologies, governmentMap);
		}
	}
}


void HoI4::World::convertIdeologySupport()
{
	for (auto country: countries)
	{
		country.second->convertIdeologySupport(ideologies->getMajorIdeologies(), governmentMap);
	}
}


void HoI4::World::convertIndustry()
{
	LOG(LogLevel::Info) << "Converting industry";

	map<string, double> factoryWorkerRatios = calculateFactoryWorkerRatios();
	states->putIndustryInStates(factoryWorkerRatios, theCoastalProvinces);

	calculateIndustryInCountries();
	reportIndustryLevels();
}


void HoI4::World::addStatesToCountries()
{
	for (auto state: states->getStates())
	{
		auto owner = countries.find(state.second.getOwner());
		if (owner != countries.end())
		{
			owner->second->addState(state.second);
		}
	}

	for (auto country: countries)
	{
		if (country.second->getStates().size() > 0)
		{
			landedCountries.insert(country);
		}
		country.second->determineCapitalFromVic2(
			theProvinceMapper,
			states->getProvinceToStateIDMap(),
			states->getStates()
		);
	}
}


map<string, double> HoI4::World::calculateFactoryWorkerRatios()
{
	map<string, double> industrialWorkersPerCountry = getIndustrialWorkersPerCountry();
	double totalWorldWorkers = getTotalWorldWorkers(industrialWorkersPerCountry);
	map<string, double> adjustedWorkersPerCountry = adjustWorkers(industrialWorkersPerCountry, totalWorldWorkers);
	double acutalWorkerFactoryRatio = getWorldwideWorkerFactoryRatio(adjustedWorkersPerCountry, totalWorldWorkers);

	map<string, double> factoryWorkerRatios;
	for (auto country: landedCountries)
	{
		auto adjustedWorkers = adjustedWorkersPerCountry.find(country.first);
		double factories = adjustedWorkers->second * acutalWorkerFactoryRatio;

		auto& Vic2Country = country.second->getSourceCountry();
		long actualWorkers = Vic2Country.getEmployedWorkers();

		if (actualWorkers > 0)
		{
			factoryWorkerRatios.insert(make_pair(country.first, factories / actualWorkers));
		}
	}

	return factoryWorkerRatios;
}


map<string, double> HoI4::World::getIndustrialWorkersPerCountry()
{
	map<string, double> industrialWorkersPerCountry;
	for (auto country: landedCountries)
	{
		auto& Vic2Country = country.second->getSourceCountry();
		long employedWorkers = Vic2Country.getEmployedWorkers();
		if (employedWorkers > 0)
		{
			industrialWorkersPerCountry.insert(make_pair(country.first, employedWorkers));
		}
	}

	return industrialWorkersPerCountry;
}


double HoI4::World::getTotalWorldWorkers(const map<string, double>& industrialWorkersPerCountry)
{
	double totalWorldWorkers = 0.0;
	for (auto countryWorkers: industrialWorkersPerCountry)
	{
		totalWorldWorkers += countryWorkers.second;
	}

	return totalWorldWorkers;
}


map<string, double> HoI4::World::adjustWorkers(const map<string, double>& industrialWorkersPerCountry, double totalWorldWorkers)
{
	double meanWorkersPerCountry = totalWorldWorkers / industrialWorkersPerCountry.size();

	map<string, double> workersDelta;
	for (auto countryWorkers: industrialWorkersPerCountry)
	{
		double delta = countryWorkers.second - meanWorkersPerCountry;
		workersDelta.insert(make_pair(countryWorkers.first, delta));
	}

	map<string, double> adjustedWorkers;
	for (auto countryWorkers: industrialWorkersPerCountry)
	{
		double delta = workersDelta.find(countryWorkers.first)->second;
		double newWorkers = countryWorkers.second - theConfiguration.getIndustrialShapeFactor() * delta;
		adjustedWorkers.insert(make_pair(countryWorkers.first, newWorkers));
	}

	return adjustedWorkers;
}


double HoI4::World::getWorldwideWorkerFactoryRatio(const map<string, double>& workersInCountries, double totalWorldWorkers)
{
	double baseIndustry = 0.0;
	for (auto countryWorkers: workersInCountries)
	{
		baseIndustry += countryWorkers.second * 0.000019;
	}

	int defaultFactories = 1189;
	HoI4::Version onePointFour("1.4.0");
	if (theConfiguration.getHOI4Version() >= onePointFour)
	{
		defaultFactories = 1201;
	}
	double deltaIndustry = baseIndustry - defaultFactories;
	deltaIndustry -= landedCountries.size();
	double newIndustry = baseIndustry - theConfiguration.getIcFactor() * deltaIndustry;
	double acutalWorkerFactoryRatio = newIndustry / totalWorldWorkers;

	return acutalWorkerFactoryRatio;
}


void HoI4::World::calculateIndustryInCountries()
{
	for (auto country: countries)
	{
		country.second->calculateIndustry(states->getStates());
	}
}


void HoI4::World::reportIndustryLevels()
{
	int militaryFactories = 0;
	int civilialFactories = 0;
	int dockyards = 0;
	for (auto state: states->getStates())
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
		reportCountryIndustry();
		reportDefaultIndustry();
	}
}


void HoI4::World::reportCountryIndustry()
{
	ofstream report("convertedIndustry.csv");
	report << "tag,military factories,civilian factories,dockyards,total factories\n";
	if (report.is_open())
	{
		for (auto country: countries)
		{
			reportIndustry(report, *country.second);
		}
	}
}


void HoI4::World::reportDefaultIndustry()
{
	map<string, array<int, 3>> countryIndustry;

	for (auto state: states->getDefaultStates())
	{
		pair<string, array<int, 3>> stateData = getDefaultStateIndustry(state.second);

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


std::pair<std::string, std::array<int, 3>> HoI4::World::getDefaultStateIndustry(const HoI4::DefaultState& state)
{
	int civilianFactories = state.getCivFactories();
	int militaryFactories = state.getMilFactories();
	int dockyards = state.getDockyards();

	std::string owner = state.getOwner();

	std::array<int, 3> industry = { militaryFactories, civilianFactories, dockyards };
	std::pair<std::string, array<int, 3>> stateData = std::make_pair(owner, industry);

	return stateData;
}


void HoI4::World::reportDefaultIndustry(const map<string, array<int, 3>>& countryIndustry)
{
	ofstream report("defaultIndustry.csv");
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


void HoI4::World::convertStrategicRegions()
{
	map<int, int> provinceToStrategicRegionMap = importStrategicRegions();

	for (auto state : states->getStates())
	{
		map<int, int> usedRegions = determineUsedRegions(state.second, provinceToStrategicRegionMap);
		auto bestRegion = determineMostUsedRegion(usedRegions);
		if (bestRegion)
		{
			addProvincesToRegion(state.second, *bestRegion);
		}
	}
	addLeftoverProvincesToRegions(provinceToStrategicRegionMap);
}


map<int, int> HoI4::World::importStrategicRegions()
{
	map<int, int> provinceToStrategicRegionMap;

	set<string> filenames;
	Utils::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/map/strategicregions/", filenames);
	for (auto filename: filenames)
	{
		HoI4::StrategicRegion* newRegion = new HoI4::StrategicRegion(filename);
		strategicRegions.insert(make_pair(newRegion->getID(), newRegion));

		for (auto province: newRegion->getOldProvinces())
		{
			provinceToStrategicRegionMap.insert(make_pair(province, newRegion->getID()));
		}
	}

	return provinceToStrategicRegionMap;
}


map<int, int> HoI4::World::determineUsedRegions(const HoI4::State& state, map<int, int>& provinceToStrategicRegionMap)
{
	map<int, int> usedRegions;	// region ID -> number of provinces in that region

	for (auto province: state.getProvinces())
	{
		auto mapping = provinceToStrategicRegionMap.find(province);
		if (mapping == provinceToStrategicRegionMap.end())
		{
			LOG(LogLevel::Warning) << "Province " << province << " had no original strategic region";
			continue;
		}

		auto usedRegion = usedRegions.find(mapping->second);
		if (usedRegion == usedRegions.end())
		{
			usedRegions.insert(make_pair(mapping->second, 1));
		}
		else
		{
			usedRegion->second++;
		}

		provinceToStrategicRegionMap.erase(mapping);
	}

	return usedRegions;
}


optional<int> HoI4::World::determineMostUsedRegion(const map<int, int>& usedRegions) const
{
	int mostProvinces = 0;
	optional<int> bestRegion;
	for (auto region: usedRegions)
	{
		if (region.second > mostProvinces)
		{
			bestRegion = region.first;
			mostProvinces = region.second;
		}
	}

	return bestRegion;
}


void HoI4::World::addProvincesToRegion(const HoI4::State& state, int regionNum)
{
	auto region = strategicRegions.find(regionNum);
	if (region == strategicRegions.end())
	{
		LOG(LogLevel::Warning) << "Strategic region " << regionNum << " was not in the list of regions.";
		return;
	}

	for (auto province : state.getProvinces())
	{
		region->second->addNewProvince(province);
	}
}


void HoI4::World::addLeftoverProvincesToRegions(const map<int, int>& provinceToStrategicRegionMap)
{
	for (auto mapping: provinceToStrategicRegionMap)
	{
		auto region = strategicRegions.find(mapping.second);
		if (region == strategicRegions.end())
		{
			LOG(LogLevel::Warning) << "Strategic region " << mapping.second << " was not in the list of regions.";
			continue;
		}
		region->second->addNewProvince(mapping.first);
	}
}


void HoI4::World::convertDiplomacy()
{
	LOG(LogLevel::Info) << "Converting diplomacy";
	convertAgreements();
}


void HoI4::World::convertAgreements()
{
	for (auto agreement: sourceWorld->getDiplomacy()->getAgreements())
	{
		auto possibleHoI4Tag1 = countryMap.getHoI4Tag(agreement->getCountry1());
		if (!possibleHoI4Tag1)
		{
			continue;
		}
		auto possibleHoI4Tag2 = countryMap.getHoI4Tag(agreement->getCountry2());
		if (!possibleHoI4Tag2)
		{
			continue;
		}

		auto HoI4Country1 = countries.find(*possibleHoI4Tag1);
		auto HoI4Country2 = countries.find(*possibleHoI4Tag2);
		if (HoI4Country1 == countries.end())
		{
			LOG(LogLevel::Warning) << "HoI4 country " << *possibleHoI4Tag1 << " used in diplomatic agreement doesn't exist";
			continue;
		}
		if (HoI4Country2 == countries.end())
		{
			LOG(LogLevel::Warning) << "HoI4 country " << *possibleHoI4Tag2 << " used in diplomatic agreement doesn't exist";
			continue;
		}

		if (agreement->getType() == "alliance")
		{
			HoI4Country1->second->editAllies().insert(*possibleHoI4Tag2);
			HoI4Country2->second->editAllies().insert(*possibleHoI4Tag1);
		}

		if (agreement->getType() == "vassal")
		{
			HoI4Country1->second->addPuppet(*possibleHoI4Tag2);
			HoI4Country2->second->setPuppetMaster(*possibleHoI4Tag1);
		}
	}
}


void HoI4::World::convertTechs()
{
	LOG(LogLevel::Info) << "Converting techs and research bonuses";

	mappers::techMapperFile file;
	unique_ptr<mappers::techMapper> techMap = file.takeTechMapper();

	for (auto country: countries)
	{
		country.second->convertTechnology(*techMap);
	}
}


void HoI4::World::convertMilitaries()
{
	const HoI4::militaryMappings& specificMappings = theMilitaryMappings->getMilitaryMappings(theConfiguration.getVic2Mods());

	convertArmies(specificMappings);
	convertNavies(specificMappings.getUnitMappings(), specificMappings.getMtgUnitMappings());
	convertAirforces(specificMappings.getUnitMappings());
}


void HoI4::World::convertArmies(const militaryMappings& localMilitaryMappings)
{
	LOG(LogLevel::Info) << "Converting armies";

	for (auto country: countries)
	{
		country.second->convertArmies(localMilitaryMappings, *states);
	}
}


void HoI4::World::convertNavies(
	const UnitMappings& unitMap,
	const MtgUnitMappings& mtgUnitMap)
{
	LOG(LogLevel::Info) << "Converting navies";

	ifstream variantsFile("DataFiles/shipTypes.txt");
	if (!variantsFile.is_open())
	{
		std::runtime_error e("Could not open DataFiles/shipTypes.txt. Double-check your converter installation");
		throw e;
	}
	PossibleShipVariants possibleVariants(variantsFile);
	variantsFile.close();

	for (auto country : countries)
	{
		country.second->determineShipVariants(possibleVariants);
		country.second->convertNavies(
			unitMap,
			mtgUnitMap,
			states->getProvinceToStateIDMap(),
			states->getStates()
		);
		country.second->convertConvoys(unitMap);
	}
}


void HoI4::World::convertAirforces(const UnitMappings& unitMap)
{
	LOG(LogLevel::Info) << "Converting air forces";

	for (auto country : countries)
	{
		country.second->convertAirForce(unitMap);
	}
}


void HoI4::World::determineGreatPowers()
{
	for (auto greatPowerVic2Tag: sourceWorld->getGreatPowers())
	{
		auto possibleGreatPowerTag = countryMap.getHoI4Tag(greatPowerVic2Tag);
		if (possibleGreatPowerTag)
		{
			auto greatPower = countries.find(*possibleGreatPowerTag);
			if (greatPower != countries.end())
			{
				greatPowers.push_back(greatPower->second);
				greatPower->second->setGreatPower();
			}
		}
	}
}


void HoI4::World::setupNavalTreaty()
{
	std::optional<std::pair<std::string, std::string>> strongestGpNavies = getStrongestNavyGps();
	if (strongestGpNavies)
	{
		scriptedLocalisations.initialize(strongestGpNavies->first, strongestGpNavies->second);
		HoI4Localisation::addDecisionLocalisation(
			strongestGpNavies->first + "_Naval_treaty_nation",
			"@" + strongestGpNavies->first + " [" + strongestGpNavies->first + ".GetName]"
		); HoI4Localisation::addDecisionLocalisation(
			strongestGpNavies->second + "_Naval_treaty_nation",
			"@" + strongestGpNavies->second + " [" + strongestGpNavies->second + ".GetName]"
		);
	}
}


double HoI4::World::getStrongestCountryStrength() const
{
	double greatestStrength = 0.0;
	for (auto country: countries)
	{
		double currentStrength = country.second->getStrengthOverTime(1.0);
		if (currentStrength > greatestStrength)
		{
			greatestStrength = currentStrength;
		}
	}

	return greatestStrength;
}


void HoI4::World::createFactions()
{
	LOG(LogLevel::Info) << "Creating Factions";

	ofstream factionsLog;
	if (theConfiguration.getDebug())
	{
		factionsLog.open("factions-logs.csv");
		factionsLog << "name,government,initial strength,factory strength per year,factory strength by 1939\n";
	}

	for (auto leader : greatPowers)
	{
		if (leader->isInFaction())
		{
			continue;
		}
		if (theConfiguration.getDebug())
		{
			factionsLog << "\n";
		}

		vector<shared_ptr<HoI4::Country>> factionMembers;
		factionMembers.push_back(leader);

		string leaderIdeology = leader->getGovernmentIdeology();
		if (theConfiguration.getDebug())
		{
			logFactionMember(factionsLog, leader);
		}
		double factionMilStrength = leader->getStrengthOverTime(3.0);

		std::set<std::string> alliesAndPuppets = leader->getAllies();
		for (auto puppetTag : leader->getPuppets())
		{
			alliesAndPuppets.insert(puppetTag);
		}

		for (auto allyTag : alliesAndPuppets)
		{
			auto allycountry = findCountry(allyTag);
			if (!allycountry)
			{
				continue;
			}
			string allygovernment = allycountry->getGovernmentIdeology();
			auto possibleSphereLeader = returnSphereLeader(allycountry);

			if (
					((possibleSphereLeader) && (*possibleSphereLeader == leader->getTag())) ||
					((!possibleSphereLeader) && governmentsAllowFaction(leaderIdeology, allygovernment))
				)
			{
				if (theConfiguration.getDebug())
				{
					logFactionMember(factionsLog, allycountry);
				}
				factionMembers.push_back(allycountry);

				factionMilStrength += (allycountry)->getStrengthOverTime(1.0);
				//also add the allies' puppets to the faction
				for (auto puppetTag : (allycountry)->getPuppets())
				{
					auto puppetcountry = findCountry(puppetTag);
					if (!puppetcountry)
					{
						continue;
					}
					logFactionMember(factionsLog, puppetcountry);
					factionMembers.push_back(puppetcountry);

					factionMilStrength += (puppetcountry)->getStrengthOverTime(1.0);
				}
			}
		}

		if (factionMembers.size() > 1)
		{
			auto newFaction = make_shared<HoI4::Faction>(leader, factionMembers);
			for (auto member : factionMembers)
			{
				member->setFaction(newFaction);
			}
			factions.push_back(newFaction);

			if (theConfiguration.getDebug())
			{
				factionsLog << "Faction Strength in 1939," << factionMilStrength << "\n";
			}
		}
	}

	if (theConfiguration.getDebug())
	{
		factionsLog.close();
	}
}


void HoI4::World::logFactionMember(ofstream& factionsLog, shared_ptr<HoI4::Country> member) const
{
	auto possibleName = member->getSourceCountry().getName("english");
	if (possibleName)
	{
		factionsLog << *possibleName << ",";
		factionsLog << member->getGovernmentIdeology() << ",";
		factionsLog << member->getMilitaryStrength() << ",";
		factionsLog << member->getEconomicStrength(1.0) << ",";
		factionsLog << member->getEconomicStrength(3.0) << "\n";
	}
	else
	{
		LOG(LogLevel::Warning) << "Could not get name when logging faction member";
	}
}


optional<string> HoI4::World::returnSphereLeader(shared_ptr<HoI4::Country> possibleSphereling) const
{
	for (auto greatPower: greatPowers)
	{
		auto relations = greatPower->getRelations();
		auto relation = relations.find(possibleSphereling->getTag());
		if (relation != relations.end())
		{
			if (relation->second.getSphereLeader())
			{
				return greatPower->getTag();
			}
		}
	}

	return {};
}


bool HoI4::World::governmentsAllowFaction(const string& leaderIdeology, const string& allyGovernment) const
{
	if (leaderIdeology == allyGovernment)
	{
		return true;
	}
	else if (leaderIdeology == "absolutist" && allyGovernment == "fascism")
	{
		return true;
	}
	else if (leaderIdeology == "democratic" && allyGovernment == "absolutist")
	{
		return true;
	}
	else if (leaderIdeology == "communism" && allyGovernment == "fascism")
	{
		return true;
	}
	else if (leaderIdeology == "fascism" && (allyGovernment == "communism" || allyGovernment == "absolutist"))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void HoI4::World::addFocusTrees()
{
	for (auto country: countries)
	{
		if (country.second->isGreatPower() || (country.second->getStrengthOverTime(3) > 4500))
		{
			country.second->addGenericFocusTree(ideologies->getMajorIdeologies());
		}
	}
}


void HoI4::World::adjustResearchFocuses()
{
	for (auto country: countries)
	{
		country.second->adjustResearchFocuses();
	}
}


void HoI4::World::addCountryElectionEvents(const std::set<string>&theMajorIdeologies)
{
	for (auto country: countries)
	{
		events->addPartyChoiceEvent(country.first, country.second->getParties(), *onActions, theMajorIdeologies);
	}
}


void HoI4::World::output()
{
	LOG(LogLevel::Info) << "Outputting world";

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history";
		exit(-1);
	}

	outputCommonCountries();
	outputColorsfile();
	outputNames();
	outputUnitNames();
	HoI4Localisation::output();
	outputStates(*states, theConfiguration);
	outputMap();
	outputSupplyZones(*supplyZones, theConfiguration);
	outputRelations();
	outputGenericFocusTree();
	outputCountries();
	outputBuildings(*buildings, theConfiguration);
	outputDecisions(*decisions, ideologies->getMajorIdeologies(), theConfiguration);
	outputEvents(*events, theConfiguration);
	onActions->output(ideologies->getMajorIdeologies());
	outAiPeaces(*peaces, ideologies->getMajorIdeologies(), theConfiguration);
	outputIdeologies(*ideologies);
	outputLeaderTraits();
	outIdeas(*theIdeas, ideologies->getMajorIdeologies(), theConfiguration);
	outputBookmarks();
	outputScriptedLocalisations(theConfiguration, scriptedLocalisations);
	outputScriptedTriggers(scriptedTriggers, theConfiguration);
	outputDifficultySettings(greatPowers, theConfiguration);
}


void HoI4::World::outputCommonCountries() const
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/country_tags"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/common/country_tags\"";
		exit(-1);
	}

	LOG(LogLevel::Debug) << "Writing countries file";
	ofstream allCountriesFile("output/" + theConfiguration.getOutputName() + "/common/country_tags/00_countries.txt");
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


void HoI4::World::outputColorsfile() const
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/countries"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/common/countries\"";
		exit(-1);
	}

	ofstream output("output/" + theConfiguration.getOutputName() + "/common/countries/colors.txt");
	if (!output.is_open())
	{
		Log(LogLevel::Error) << "Could not open output/" << theConfiguration.getOutputName() << "/common/countries/colors.txt";
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


void HoI4::World::outputNames() const
{
	ofstream namesFile("output/" + theConfiguration.getOutputName() + "/common/names/01_names.txt");
	namesFile << "\xEF\xBB\xBF";    // add the BOM to make HoI4 happy

	if (!namesFile.is_open())
	{
		Log(LogLevel::Error) << "Could not open output/" << theConfiguration.getOutputName() << "/common/names/01_names.txt";
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

void HoI4::World::outputUnitNames() const
{
	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			outputToUnitNamesFiles(*country.second);
		}
	}
}


void HoI4::World::outputMap() const
{
	LOG(LogLevel::Debug) << "Writing Map Info";

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/map"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/map";
		exit(-1);
	}

	ofstream rocketSitesFile("output/" + theConfiguration.getOutputName() + "/map/rocketsites.txt");
	if (!rocketSitesFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create output/" << theConfiguration.getOutputName() << "/map/rocketsites.txt";
		exit(-1);
	}
	for (auto state: states->getStates())
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
		outputStrategicRegion(*strategicRegion.second, "output/" + theConfiguration.getOutputName() + "/map/strategicregions/");
	}
}


void HoI4::World::outputGenericFocusTree() const
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/national_focus"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/common/national_focus\"";
		exit(-1);
	}

	HoI4FocusTree genericFocusTree;
	genericFocusTree.addGenericFocusTree(ideologies->getMajorIdeologies());
	genericFocusTree.generateSharedFocuses("output/" + theConfiguration.getOutputName() + "/common/national_focus/shared_focuses.txt");
}


void HoI4::World::outputCountries()
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

	auto activeIdeologicalAdvisors = getActiveIdeologicalAdvisors();
	for (auto country: countries)
	{
		if (country.second->getCapitalState())
		{
			const HoI4::militaryMappings& specificMilitaryMappings = theMilitaryMappings->getMilitaryMappings(theConfiguration.getVic2Mods());
			HoI4::outputCountry(
				activeIdeologicalAdvisors,
				specificMilitaryMappings.getDivisionTemplates(),
				theNames,
				theGraphics,
				*country.second
			);
		}
	}

	ofstream ideasFile("output/" + theConfiguration.getOutputName() + "/interface/converter_ideas.gfx");
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


std::set<HoI4::Advisor> HoI4::World::getActiveIdeologicalAdvisors() const
{
	std::set<HoI4::Advisor> theAdvisors;
	for (const auto& majorIdeology : ideologies->getMajorIdeologies())
	{
		auto ideologicalAdvisor = ideologicalAdvisors.find(majorIdeology);
		if (ideologicalAdvisor != ideologicalAdvisors.end())
		{
			theAdvisors.insert(ideologicalAdvisor->second);
		}
	}

	return theAdvisors;
}


void HoI4::World::outputRelations() const
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/opinion_modifiers"))
	{
		Log(LogLevel::Error) << "Could not create output/" + theConfiguration.getOutputName() + "/common/opinion_modifiers/";
		exit(-1);
	}

	ofstream out("output/" + theConfiguration.getOutputName() + "/common/opinion_modifiers/01_opinion_modifiers.txt");
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


void HoI4::World::outputLeaderTraits() const
{
	ofstream traitsFile("output/" + theConfiguration.getOutputName() + "/common/country_leader/converterTraits.txt");
	traitsFile << "leader_traits = {\n";
	for (const auto& majorIdeology: ideologies->getMajorIdeologies())
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


void HoI4::World::outputBookmarks() const
{
	ofstream bookmarkFile("output/" + theConfiguration.getOutputName() + "/common/bookmarks/the_gathering_storm.txt");

	bookmarkFile << "bookmarks = {\n";
	bookmarkFile << "	bookmark = {\n";
	bookmarkFile << "		name = ""GATHERING_STORM_NAME""\n";
	bookmarkFile << "		desc = ""GATHERING_STORM_DESC""\n";
	bookmarkFile << "		date = 1936.1.1.12\n";
	bookmarkFile << "		picture = ""GFX_select_date_1936""\n";
	bookmarkFile << "		default_country = \"---\"\n";
	bookmarkFile << "		default = yes\n";

	for (auto greatPower : greatPowers)
	{
		//Vic2 Great powers become majors in bookmark
		bookmarkFile << "		" + greatPower->getTag() + "= {\n";
		bookmarkFile << "			history = \"OTHER_GATHERING_STORM_DESC\"\n";
		bookmarkFile << "			ideology = " + greatPower->getGovernmentIdeology() + "\n";
		bookmarkFile << "			ideas = { great_power }\n";
		bookmarkFile << "		}\n";
	}
	
	bookmarkFile << "		\"---\"= {\n";
	bookmarkFile << "			history = \"OTHER_GATHERING_STORM_DESC\"\n";
	bookmarkFile << "		}\n";

	for (auto country : countries)
	{
		if (country.second->isGreatPower() != true)
		{
			if (country.second->getStrengthOverTime(3) > 4500)
			{
				//add minor countries to the bookmark, only those with custom focustree are visible due to Hoi4 limitations
				//Bookmark window has room for 22 minor countries, going over this seems to not cause any issues however
				bookmarkFile << "		" + country.second->getTag() + " = {\n";
				bookmarkFile << "			minor = yes\n";
				bookmarkFile << "			history = \"OTHER_GATHERING_STORM_DESC\"\n";
				bookmarkFile << "			ideology = " + country.second->getGovernmentIdeology() + "\n";
				bookmarkFile << "			ideas = { }\n";
				bookmarkFile << "		}\n";
			}
		}
	}

	bookmarkFile << "effect = {\n";
	bookmarkFile << "randomize_weather = 22345 # <-Obligatory in every bookmark !\n";
	bookmarkFile << "#123 = { rain_light = yes }\n";
	bookmarkFile << "	}\n";
	bookmarkFile << "}\n";
	bookmarkFile.close();
}


std::optional<std::pair<std::string, std::string>> HoI4::World::getStrongestNavyGps()
{
	std::pair<std::string, std::string> strongestNavies;
	float strongestNavy = 0;
	float secondStrongestNavy = 0;

	for (auto greatPower: greatPowers)
	{
		float navyStrength = greatPower->getNavalStrength();
		if (navyStrength > strongestNavy)
		{
			strongestNavies.second = strongestNavies.first;
			secondStrongestNavy = strongestNavy;
			strongestNavies.first = greatPower->getTag();
			strongestNavy = navyStrength;
		}
		else if (navyStrength > secondStrongestNavy)
		{
			strongestNavies.second = greatPower->getTag();
			secondStrongestNavy = navyStrength;
		}
	}

	if ((strongestNavy > 0) && (secondStrongestNavy > 0))
	{
		return strongestNavies;
	}
	else
	{
		return std::nullopt;
	}
}


/*vector<int> HoI4::World::getPortLocationCandidates(const vector<int>& locationCandidates, const HoI4AdjacencyMapping& HoI4AdjacencyMap)
{
vector<int> portLocationCandidates = getPortProvinces(locationCandidates);
if (portLocationCandidates.size() == 0)
{
// if none of the mapped provinces are ports, try to push the navy out to sea
for (auto candidate : locationCandidates)
{
if (HoI4AdjacencyMap.size() > static_cast<unsigned int>(candidate))
{
auto newCandidates = HoI4AdjacencyMap[candidate];
for (auto newCandidate : newCandidates)
{
auto candidateProvince = provinces.find(newCandidate.to);
if (candidateProvince == provinces.end())	// if this was not an imported province but has an adjacency, we can assume it's a sea province
{
portLocationCandidates.push_back(newCandidate.to);
}
}
}
}
}
return portLocationCandidates;
}*/

void HoI4::World::setSphereLeaders()
{
	for (auto GP: greatPowers)
	{
		for (auto& relationItr: GP->getRelations())
		{
			if (relationItr.second.getSphereLeader())
			{
				auto sphereling = findCountry(relationItr.first);
				sphereling->setSphereLeader(GP->getTag());
			}
		}
	}
}

void HoI4::World::processInfluence()
{
	for (auto GP: greatPowers)
	{
		for (auto& relationItr: GP->getRelations())
		{
			auto influencedCountry = findCountry(relationItr.first);
			bool isFriendlyCountry = relationItr.second.getGuarantee();
			auto influenceValue = relationItr.second.getInfluenceValue();

			if (isFriendlyCountry)
			{
				influencedCountry->addGPInfluence(GP->getTag(), influenceValue);
			}
		}
	}
}

void HoI4::World::determineSpherelings()
{
	for (auto& GP: greatPowers)
	{
		for (auto relationItr: GP->getRelations())
		{
			bool isInSphere = relationItr.second.getSphereLeader();
			bool notPuppet = (GP->getPuppets().find(relationItr.first) == GP->getPuppets().end());
			auto allies = GP->getAllies();
			bool isAlly = allies.count(relationItr.first);
			
			if (isInSphere && notPuppet && isAlly)
			{
				GP->addSphereling(relationItr.first);
			}
			if (isInSphere && notPuppet && !isAlly)
			{
				GP->addGuaranteed(relationItr.first);
			}
		}
	}
}

void HoI4::World::calculateSpherelingAutonomy()
{
	for (auto& GP: greatPowers)
	{
		for (auto& sphereling: GP->getSpherelings())
		{
			auto spherelingCountry = findCountry(sphereling.first);
			double influenceFactor = spherelingCountry->calculateInfluenceFactor();

			double spherelingAutonomy = 3.6 * influenceFactor / 400;
			
			GP->setSpherelingAutonomy(sphereling.first, spherelingAutonomy);
		}
	}
}