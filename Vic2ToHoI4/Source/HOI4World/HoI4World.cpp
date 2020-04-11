#include "HoI4World.h"
#include "../Configuration.h"
#include "../HOI4World/ProvinceDefinitions.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Mappers/TechMapper.h"
#include "../V2World/Agreement.h"
#include "../V2World/Country.h"
#include "../V2World/Diplomacy.h"
#include "../V2World/Party.h"
#include "../V2World/Vic2Localisations.h"
#include "../V2World/World.h"
#include "Decisions/Decisions.h"
#include "Diplomacy/AiPeacesUpdater.h"
#include "Diplomacy/Faction.h"
#include "Events/Events.h"
#include "Events/GovernmentInExileEvent.h"
#include "HoI4Country.h"
#include "HoI4FocusTree.h"
#include "HoI4Localisation.h"
#include "Ideas/Ideas.h"
#include "Ideologies/Ideology.h"
#include "Ideologies/IdeologyFile.h"
#include "Leaders/Advisor.h"
#include "Leaders/IdeologicalAdvisors.h"
#include "Log.h"
#include "Map/Buildings.h"
#include "Map/StrategicRegion.h"
#include "Map/SupplyZones.h"
#include "MilitaryMappings/MilitaryMappingsFile.h"
#include "Names.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "ScriptedTriggers/ScriptedTriggersUpdater.h"
#include "ShipTypes/PossibleShipVariants.h"
#include "States/DefaultState.h"
#include "States/HoI4State.h"
#include "States/StateCategories.h"
#include "WarCreator/HoI4WarCreator.h"
using namespace std;



HoI4::World::World(const Vic2::World* _sourceWorld):
	 sourceWorld(_sourceWorld), countryMap(_sourceWorld), theIdeas(std::make_unique<HoI4::Ideas>()),
	 theDecisions(make_unique<HoI4::decisions>(theConfiguration)), peaces(make_unique<HoI4::AiPeaces>()),
	 events(make_unique<HoI4::Events>()), onActions(make_unique<HoI4::OnActions>())
{
	LOG(LogLevel::Info) << "Building HoI4 World";

	auto vic2Localisations = sourceWorld->getLocalisations();

	ProvinceDefinitions provinceDefinitions =
		 ProvinceDefinitions::Importer{}.importProvinceDefinitions(theConfiguration);
	theMapData = std::make_unique<MapData>(provinceDefinitions);
	theCoastalProvinces.init(*theMapData);
	states = std::make_unique<States>(sourceWorld,
		 countryMap,
		 theCoastalProvinces,
		 sourceWorld->getStateDefinitions(),
		 vic2Localisations,
		 provinceDefinitions,
		 hoi4Localisations);
	supplyZones = new HoI4::SupplyZones(states->getDefaultStates());
	buildings = new Buildings(*states, theCoastalProvinces, *theMapData, provinceDefinitions);
	theNames.init();
	theGraphics.init();
	governmentMap.init();
	convertCountries(vic2Localisations);
	addStatesToCountries();
	states->addCapitalsToStates(countries);
	hoi4Localisations.addStateLocalisations(*states, vic2Localisations);
	convertIndustry();
	states->convertResources();
	supplyZones->convertSupplyZones(*states);
	convertStrategicRegions();
	convertDiplomacy();
	convertTechs();

	militaryMappingsFile importedMilitaryMappings;
	theMilitaryMappings = importedMilitaryMappings.takeAllMilitaryMappings();
	convertMilitaries(provinceDefinitions);

	determineGreatPowers();

	setupNavalTreaty();

	importLeaderTraits();
	convertGovernments(vic2Localisations);
	ideologies = std::make_unique<Ideologies>(theConfiguration);
	ideologies->identifyMajorIdeologies(greatPowers, countries);
	genericFocusTree.addGenericFocusTree(ideologies->getMajorIdeologies());
	importIdeologicalMinisters();
	convertParties(vic2Localisations);
	events->createPoliticalEvents(ideologies->getMajorIdeologies(), hoi4Localisations);
	events->createWarJustificationEvents(ideologies->getMajorIdeologies(), hoi4Localisations);
	events->importElectionEvents(ideologies->getMajorIdeologies(), *onActions);
	addCountryElectionEvents(ideologies->getMajorIdeologies(), vic2Localisations);
	events->createStabilityEvents(ideologies->getMajorIdeologies());
	events->generateGenericEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->giveGovernmentInExileEvent(createGovernmentInExileEvent(ideologies->getMajorIdeologies()));
	theIdeas->updateIdeas(ideologies->getMajorIdeologies());
	theDecisions->updateDecisions(ideologies->getMajorIdeologies(),
		 states->getProvinceToStateIDMap(),
		 states->getDefaultStates(),
		 *events);
	updateAiPeaces(*peaces, ideologies->getMajorIdeologies());
	addNeutrality();
	addLeaders();
	convertIdeologySupport();
	states->convertCapitalVPs(countries, greatPowers, getStrongestCountryStrength());
	states->convertAirBases(countries, greatPowers);
	if (theConfiguration.getCreateFactions())
	{
		createFactions();
	}

	HoI4WarCreator warCreator(this, *theMapData, provinceDefinitions, hoi4Localisations);

	addFocusTrees();
	adjustResearchFocuses();
	hoi4Localisations.generateCustomLocalisations(scriptedLocalisations, ideologies->getMajorIdeologies());

	setSphereLeaders();
	processInfluence();
	determineSpherelings();
	calculateSpherelingAutonomy();
	scriptedTriggers.importScriptedTriggers(theConfiguration);
	updateScriptedTriggers(scriptedTriggers, ideologies->getMajorIdeologies());

	gameRules = std::make_unique<GameRules>(
		 GameRules::Parser{}.parseRulesFile(theConfiguration.getHoI4Path() + "/common/game_rules/00_game_rules.txt"));
	gameRules->updateRules();
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


void HoI4::World::convertCountries(const Vic2::Localisations& vic2Localisations)
{
	LOG(LogLevel::Info) << "\tConverting countries";

	std::ifstream flagToIdeasMappingFile("DataFiles/FlagsToIdeasMappings.txt");
	mappers::FlagsToIdeasMapper flagsToIdeasMapper(flagToIdeasMappingFile);
	flagToIdeasMappingFile.close();

	for (auto sourceItr: sourceWorld->getCountries())
	{
		convertCountry(sourceItr, flagsToIdeasMapper, vic2Localisations);
	}

	hoi4Localisations.addNonenglishCountryLocalisations();
}


void HoI4::World::convertCountry(std::pair<std::string, Vic2::Country*> country,
	 const mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
	 const Vic2::Localisations& vic2Localisations)
{
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
		destCountry = new HoI4::Country(*possibleHoI4Tag,
			 country.second,
			 theNames,
			 theGraphics,
			 countryMap,
			 flagsToIdeasMapper,
			 hoi4Localisations);
		countries.insert(make_pair(*possibleHoI4Tag, destCountry));
		hoi4Localisations.createCountryLocalisations(make_pair(country.first, *possibleHoI4Tag),
			 governmentMap,
			 vic2Localisations);
		hoi4Localisations.updateMainCountryLocalisation(
			 destCountry->getTag() + "_" + destCountry->getGovernmentIdeology(),
			 country.first,
			 country.second->getGovernment(),
			 vic2Localisations);
	}
}


void HoI4::World::importLeaderTraits()
{
	LOG(LogLevel::Info) << "\tImporting leader traits";

	clearRegisteredKeywords();
	registerKeyword(std::regex("[a-z]+"), [this](const std::string& ideologyName, std::istream& theStream) {
		commonItems::stringsOfItems traits(theStream);
		ideologicalLeaderTraits.insert(make_pair(ideologyName, traits.getStrings()));
	});
	parseFile("converterLeaderTraits.txt");
}


void HoI4::World::importIdeologicalMinisters()
{
	LOG(LogLevel::Info) << "\tImporting ideological ministers";

	HoI4::IdeologicalAdvisors theAdvisors;
	auto theAcutalAdvisors = theAdvisors.getAdvisors();
	ideologicalAdvisors.swap(theAcutalAdvisors);
}


void HoI4::World::convertGovernments(const Vic2::Localisations& vic2Localisations)
{
	LOG(LogLevel::Info) << "\tConverting governments";
	for (auto country: countries)
	{
		country.second->convertGovernment(*sourceWorld, governmentMap, vic2Localisations, hoi4Localisations);
	}
}


void HoI4::World::convertParties(const Vic2::Localisations& vic2Localisations)
{
	LOG(LogLevel::Info) << "\tConverting political parties";

	for (auto country: countries)
	{
		country.second->convertParties(ideologies->getMajorIdeologies(),
			 governmentMap,
			 vic2Localisations,
			 hoi4Localisations);
	}
}


void HoI4::World::addNeutrality()
{
	LOG(LogLevel::Info) << "\tAdding neutrality";
	for (auto country: countries)
	{
		if (ideologies->getMajorIdeologies().count(country.second->getGovernmentIdeology()) == 0)
		{
			country.second->setGovernmentToExistingIdeology(ideologies->getMajorIdeologies(), *ideologies, governmentMap);
		}
	}
}


void HoI4::World::addLeaders()
{
	LOG(LogLevel::Info) << "\tAdding leaders";
	for (auto& country: countries)
	{
		country.second->addLeader(theNames, theGraphics);
	}
}


void HoI4::World::convertIdeologySupport()
{
	LOG(LogLevel::Info) << "\tConverting ideology support";
	for (auto country: countries)
	{
		country.second->convertIdeologySupport(ideologies->getMajorIdeologies(), governmentMap);
	}
}


void HoI4::World::convertIndustry()
{
	LOG(LogLevel::Info) << "\tConverting industry";

	map<string, double> factoryWorkerRatios = calculateFactoryWorkerRatios();
	states->putIndustryInStates(factoryWorkerRatios, theCoastalProvinces);

	calculateIndustryInCountries();
	reportIndustryLevels();
}


void HoI4::World::addStatesToCountries()
{
	LOG(LogLevel::Info) << "\tAdding states to countries";
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
		country.second->determineCapitalFromVic2(theProvinceMapper,
			 states->getProvinceToStateIDMap(),
			 states->getStates());
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


map<string, double> HoI4::World::adjustWorkers(const map<string, double>& industrialWorkersPerCountry,
	 double totalWorldWorkers)
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


double HoI4::World::getWorldwideWorkerFactoryRatio(const map<string, double>& workersInCountries,
	 double totalWorldWorkers)
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


void HoI4::World::reportIndustryLevels() const
{
	auto militaryFactories = 0;
	auto civilianFactories = 0;
	auto dockyards = 0;
	for (const auto& state: states->getStates())
	{
		militaryFactories += state.second.getMilFactories();
		civilianFactories += state.second.getCivFactories();
		dockyards += state.second.getDockyards();
	}

	LOG(LogLevel::Info) << "\tTotal factories: " << militaryFactories + civilianFactories + dockyards;
	LOG(LogLevel::Info) << "\t\t" << militaryFactories << " military factories";
	LOG(LogLevel::Info) << "\t\t" << civilianFactories << " civilian factories";
	LOG(LogLevel::Info) << "\t\t" << dockyards << " dockyards";
}


void HoI4::World::convertStrategicRegions()
{
	LOG(LogLevel::Info) << "\tConverting strategic regions";
	map<int, int> provinceToStrategicRegionMap = importStrategicRegions();

	for (auto state: states->getStates())
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
	map<int, int> usedRegions; // region ID -> number of provinces in that region

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

	for (auto province: state.getProvinces())
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
	LOG(LogLevel::Info) << "\tConverting diplomacy";
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
			LOG(LogLevel::Warning) << "HoI4 country " << *possibleHoI4Tag1
										  << " used in diplomatic agreement doesn't exist";
			continue;
		}
		if (HoI4Country2 == countries.end())
		{
			LOG(LogLevel::Warning) << "HoI4 country " << *possibleHoI4Tag2
										  << " used in diplomatic agreement doesn't exist";
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
	LOG(LogLevel::Info) << "\tConverting techs and research bonuses";

	mappers::techMapperFile file;
	unique_ptr<mappers::techMapper> techMap = file.takeTechMapper();

	for (auto country: countries)
	{
		country.second->convertTechnology(*techMap);
	}
}


void HoI4::World::convertMilitaries(const ProvinceDefinitions& provinceDefinitions)
{
	LOG(LogLevel::Info) << "\tConverting militaries";
	const HoI4::militaryMappings& specificMappings =
		 theMilitaryMappings->getMilitaryMappings(theConfiguration.getVic2Mods());

	convertArmies(specificMappings);
	convertNavies(specificMappings.getUnitMappings(), specificMappings.getMtgUnitMappings(), provinceDefinitions);
	convertAirforces(specificMappings.getUnitMappings());
}


void HoI4::World::convertArmies(const militaryMappings& localMilitaryMappings)
{
	LOG(LogLevel::Info) << "\t\tConverting armies";

	for (auto country: countries)
	{
		country.second->convertArmies(localMilitaryMappings, *states);
	}
}


void HoI4::World::convertNavies(const UnitMappings& unitMap,
	 const MtgUnitMappings& mtgUnitMap,
	 const ProvinceDefinitions& provinceDefinitions)
{
	LOG(LogLevel::Info) << "\t\tConverting navies";

	ifstream variantsFile("DataFiles/shipTypes.txt");
	if (!variantsFile.is_open())
	{
		std::runtime_error e("Could not open DataFiles/shipTypes.txt. Double-check your converter installation");
		throw e;
	}
	PossibleShipVariants possibleVariants(variantsFile);
	variantsFile.close();

	for (auto country: countries)
	{
		country.second->determineShipVariants(possibleVariants);
		country.second->convertNavies(unitMap,
			 mtgUnitMap,
			 states->getProvinceToStateIDMap(),
			 states->getStates(),
			 provinceDefinitions);
		country.second->convertConvoys(unitMap);
	}
}


void HoI4::World::convertAirforces(const UnitMappings& unitMap)
{
	LOG(LogLevel::Info) << "\t\tConverting air forces";

	for (auto country: countries)
	{
		country.second->convertAirForce(unitMap);
	}
}


void HoI4::World::determineGreatPowers()
{
	LOG(LogLevel::Info) << "\tDetermining great powers";
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
	LOG(LogLevel::Info) << "\tCreating naval treaty";
	std::optional<std::pair<std::string, std::string>> strongestGpNavies = getStrongestNavyGps();
	if (strongestGpNavies)
	{
		scriptedLocalisations.initialize(strongestGpNavies->first, strongestGpNavies->second);
		hoi4Localisations.addDecisionLocalisation(strongestGpNavies->first + "_Naval_treaty_nation",
			 "@" + strongestGpNavies->first + " [" + strongestGpNavies->first + ".GetName]");
		hoi4Localisations.addDecisionLocalisation(strongestGpNavies->second + "_Naval_treaty_nation",
			 "@" + strongestGpNavies->second + " [" + strongestGpNavies->second + ".GetName]");
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
	LOG(LogLevel::Info) << "\tCreating Factions";

	ofstream factionsLog;
	if (theConfiguration.getDebug())
	{
		factionsLog.open("factions-logs.csv");
		factionsLog << "name,government,initial strength,factory strength per year,factory strength by 1939\n";
	}

	for (auto leader: greatPowers)
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
		for (auto puppetTag: leader->getPuppets())
		{
			alliesAndPuppets.insert(puppetTag);
		}

		for (auto allyTag: alliesAndPuppets)
		{
			auto allycountry = findCountry(allyTag);
			if (!allycountry)
			{
				continue;
			}
			string allygovernment = allycountry->getGovernmentIdeology();
			auto possibleSphereLeader = returnSphereLeader(allycountry);

			if (((possibleSphereLeader) && (*possibleSphereLeader == leader->getTag())) ||
				 ((!possibleSphereLeader) && governmentsAllowFaction(leaderIdeology, allygovernment)))
			{
				if (theConfiguration.getDebug())
				{
					logFactionMember(factionsLog, allycountry);
				}
				factionMembers.push_back(allycountry);

				factionMilStrength += (allycountry)->getStrengthOverTime(1.0);
				// also add the allies' puppets to the faction
				for (auto puppetTag: (allycountry)->getPuppets())
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
			for (auto member: factionMembers)
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
	LOG(LogLevel::Info) << "\tAdding focus trees";
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
	LOG(LogLevel::Info) << "\tAdjusting research focuses";
	for (auto country: countries)
	{
		country.second->adjustResearchFocuses();
	}
}


void HoI4::World::addCountryElectionEvents(const std::set<string>& theMajorIdeologies,
	 const Vic2::Localisations& vic2Localisations)
{
	LOG(LogLevel::Info) << "\tAdding country election events";

	for (auto country: countries)
	{
		events->addPartyChoiceEvent(country.first,
			 country.second->getParties(),
			 *onActions,
			 theMajorIdeologies,
			 vic2Localisations,
			 hoi4Localisations);
	}
}


std::set<HoI4::Advisor> HoI4::World::getActiveIdeologicalAdvisors() const
{
	std::set<HoI4::Advisor> theAdvisors;
	for (const auto& majorIdeology: ideologies->getMajorIdeologies())
	{
		auto ideologicalAdvisor = ideologicalAdvisors.find(majorIdeology);
		if (ideologicalAdvisor != ideologicalAdvisors.end())
		{
			theAdvisors.insert(ideologicalAdvisor->second);
		}
	}

	return theAdvisors;
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


/*vector<int> HoI4::World::getPortLocationCandidates(const vector<int>& locationCandidates, const HoI4AdjacencyMapping&
HoI4AdjacencyMap)
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
if (candidateProvince == provinces.end())	// if this was not an imported province but has an adjacency, we can assume
it's a sea province
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
	LOG(LogLevel::Info) << "\tSetting sphere leaders";
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
	LOG(LogLevel::Info) << "\tAdding influence";
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
	LOG(LogLevel::Info) << "\tDetermining spherelings";
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
	LOG(LogLevel::Info) << "\tCalculating sphereling autonomy";
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