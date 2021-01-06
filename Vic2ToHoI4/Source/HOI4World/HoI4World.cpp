#include "HoI4World.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "Decisions/Decisions.h"
#include "Diplomacy/AiPeacesUpdater.h"
#include "Diplomacy/Faction.h"
#include "Events/Events.h"
#include "Events/GovernmentInExileEvent.h"
#include "HOI4World/ProvinceDefinitions.h"
#include "HoI4Country.h"
#include "HoI4FocusTree.h"
#include "HoI4Localisation.h"
#include "Ideas/Ideas.h"
#include "Leaders/Advisor.h"
#include "Leaders/CountryLeadersFactory.h"
#include "Leaders/IdeologicalAdvisors.h"
#include "Localisations/ArticleRules/ArticleRules.h"
#include "Localisations/ArticleRules/ArticleRulesFactory.h"
#include "Log.h"
#include "Map/Buildings.h"
#include "Map/HoI4Provinces.h"
#include "Map/StrategicRegion.h"
#include "Map/SupplyZones.h"
#include "Mappers/CountryMapping.h"
#include "Mappers/CountryName/CountryNameMapperFactory.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/Technology/TechMapper.h"
#include "Mappers/Technology/TechMapperFactory.h"
#include "MilitaryMappings/MilitaryMappingsFile.h"
#include "Names/Names.h"
#include "Operations/OperationsFactory.h"
#include "OperativeNames/OperativeNamesFactory.h"
#include "ParserHelpers.h"
#include "Regions/RegionsFactory.h"
#include "ScriptedLocalisations/ScriptedLocalisationsFactory.h"
#include "ScriptedTriggers/ScriptedTriggersUpdater.h"
#include "ShipTypes/PossibleShipVariants.h"
#include "Sounds/SoundEffectsFactory.h"
#include "States/HoI4State.h"
#include "V2World/Countries/Country.h"
#include "V2World/Diplomacy/Agreement.h"
#include "V2World/Diplomacy/Diplomacy.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/World/World.h"
#include "WarCreator/HoI4WarCreator.h"
using namespace std;



HoI4::World::World(const Vic2::World& sourceWorld,
	 const mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration):
	 countryMap(sourceWorld, theConfiguration.getDebug()),
	 theIdeas(std::make_unique<HoI4::Ideas>()), theDecisions(make_unique<HoI4::decisions>(theConfiguration)),
	 peaces(make_unique<HoI4::AiPeaces>()), events(make_unique<HoI4::Events>()),
	 onActions(make_unique<HoI4::OnActions>())
{
	Log(LogLevel::Progress) << "24%";
	Log(LogLevel::Info) << "Building HoI4 World";

	auto vic2Localisations = sourceWorld.getLocalisations();
	hoi4Localisations = Localisation::Importer{}.generateLocalisations(theConfiguration);

	ProvinceDefinitions provinceDefinitions =
		 ProvinceDefinitions::Importer{}.importProvinceDefinitions(theConfiguration);
	theMapData = std::make_unique<MapData>(provinceDefinitions, theConfiguration);
	const auto theProvinces = importProvinces(theConfiguration);
	theCoastalProvinces.init(*theMapData, theProvinces);
	strategicRegions = StrategicRegions::Factory{}.importStrategicRegions(theConfiguration);
	states = std::make_unique<States>(sourceWorld,
		 countryMap,
		 theProvinces,
		 theCoastalProvinces,
		 sourceWorld.getStateDefinitions(),
		 *strategicRegions,
		 vic2Localisations,
		 provinceDefinitions,
		 *theMapData,
		 *hoi4Localisations,
		 provinceMapper,
		 theConfiguration);
	supplyZones = new HoI4::SupplyZones(states->getDefaultStates(), theConfiguration);
	buildings = new Buildings(*states, theCoastalProvinces, *theMapData, provinceDefinitions, theConfiguration);
	names = Names::Factory{}.getNames(theConfiguration);
	theGraphics.init();
	governmentMap.init();
	countryNameMapper = mappers::CountryNameMapper::Factory{}.importCountryNameMapper();
	convertCountries(sourceWorld);
	addStatesToCountries(provinceMapper);
	states->addCapitalsToStates(countries);
	intelligenceAgencies = IntelligenceAgencies::Factory::createIntelligenceAgencies(countries, *names);
	hoi4Localisations->addStateLocalisations(*states, vic2Localisations, provinceMapper, theConfiguration);
	convertIndustry(theConfiguration);
	states->convertResources();
	supplyZones->convertSupplyZones(*states);
	strategicRegions->convert(*states);
	convertDiplomacy(sourceWorld);
	convertTechs();

	militaryMappingsFile importedMilitaryMappings;
	theMilitaryMappings = importedMilitaryMappings.takeAllMilitaryMappings();
	convertMilitaries(provinceDefinitions, provinceMapper, theConfiguration);

	determineGreatPowers(sourceWorld);

	scriptedEffects = std::make_unique<ScriptedEffects>(theConfiguration.getHoI4Path());
	scriptedLocalisations = ScriptedLocalisations::Factory{}.getScriptedLocalisations();
	setupNavalTreaty();

	importLeaderTraits();
	convertGovernments(sourceWorld, vic2Localisations, theConfiguration.getDebug());
	ideologies = std::make_unique<Ideologies>(theConfiguration);
	ideologies->identifyMajorIdeologies(greatPowers, countries, theConfiguration);
	convertCountryNames(vic2Localisations);
	scriptedEffects->updateOperationStratEffects(ideologies->getMajorIdeologies());
	scriptedLocalisations->updateIdeologyLocalisations(ideologies->getMajorIdeologies());
	scriptedLocalisations->filterIdeologyLocalisations(ideologies->getMajorIdeologies());
	genericFocusTree.addGenericFocusTree(ideologies->getMajorIdeologies());
	importIdeologicalMinisters();
	convertParties(vic2Localisations);
	events->createPoliticalEvents(ideologies->getMajorIdeologies(), *hoi4Localisations);
	events->createWarJustificationEvents(ideologies->getMajorIdeologies(), *hoi4Localisations);
	events->importElectionEvents(ideologies->getMajorIdeologies(), *onActions);
	events->importCapitulationEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->importLarOccupationEvents(theConfiguration, ideologies->getMajorIdeologies());
	addCountryElectionEvents(ideologies->getMajorIdeologies(), vic2Localisations);
	events->createStabilityEvents(ideologies->getMajorIdeologies(), theConfiguration);
	events->generateGenericEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->giveGovernmentInExileEvent(createGovernmentInExileEvent(ideologies->getMajorIdeologies()));
	theIdeas->updateIdeas(ideologies->getMajorIdeologies());
	theDecisions->updateDecisions(ideologies->getMajorIdeologies(),
		 states->getProvinceToStateIDMap(),
		 states->getDefaultStates(),
		 *events,
		 getSouthAsianCountries());
	updateAiPeaces(*peaces, ideologies->getMajorIdeologies());
	addNeutrality(theConfiguration.getDebug());
	addLeaders();
	convertIdeologySupport();
	states->convertCapitalVPs(countries, greatPowers, getStrongestCountryStrength());
	states->convertAirBases(countries, greatPowers);
	if (theConfiguration.getCreateFactions())
	{
		createFactions(theConfiguration);
	}

	HoI4WarCreator warCreator(this, *theMapData, provinceDefinitions, *hoi4Localisations, theConfiguration);

	addFocusTrees();
	adjustResearchFocuses();
	hoi4Localisations->generateCustomLocalisations(*scriptedLocalisations, ideologies->getMajorIdeologies());

	setSphereLeaders();
	processInfluence();
	determineSpherelings();
	calculateSpherelingAutonomy();
	scriptedTriggers.importScriptedTriggers(theConfiguration);
	updateScriptedTriggers(scriptedTriggers, ideologies->getMajorIdeologies());

	gameRules = std::make_unique<GameRules>(
		 GameRules::Parser{}.parseRulesFile(theConfiguration.getHoI4Path() + "/common/game_rules/00_game_rules.txt"));
	gameRules->updateRules();

	occupationLaws = OccupationLaws::Factory{}.getOccupationLaws(theConfiguration);
	occupationLaws->updateLaws(ideologies->getMajorIdeologies());

	operativeNames = OperativeNames::Factory::getOperativeNames(theConfiguration.getHoI4Path());
	operativeNames->addCountriesToNameSets(countries);

	operations = Operations::Factory{}.getOperations(theConfiguration.getHoI4Path());
	operations->updateOperations(ideologies->getMajorIdeologies());

	soundEffects = SoundEffectsFactory{}.createSoundEffects(countries);
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


void HoI4::World::convertCountries(const Vic2::World& sourceWorld)
{
	Log(LogLevel::Info) << "\tConverting countries";

	std::ifstream flagToIdeasMappingFile("Configurables/FlagsToIdeasMappings.txt");
	const mappers::FlagsToIdeasMapper flagsToIdeasMapper(flagToIdeasMappingFile);
	flagToIdeasMappingFile.close();

	for (const auto& [tag, country]: sourceWorld.getCountries())
	{
		convertCountry(tag, *country, flagsToIdeasMapper);
	}
}


void HoI4::World::convertCountry(const std::string& oldTag,
	 const Vic2::Country& oldCountry,
	 const mappers::FlagsToIdeasMapper& flagsToIdeasMapper)
{
	// don't convert rebels
	if (oldTag == "REB")
	{
		return;
	}

	HoI4::Country* destCountry = nullptr;
	auto possibleHoI4Tag = countryMap.getHoI4Tag(oldTag);
	if (!possibleHoI4Tag)
	{
		Log(LogLevel::Warning) << "Could not convert V2 tag " << oldTag << " to HoI4";
	}
	else
	{
		destCountry = new HoI4::Country(*possibleHoI4Tag,
			 oldCountry,
			 *names,
			 theGraphics,
			 countryMap,
			 flagsToIdeasMapper,
			 *hoi4Localisations);
		countries.insert(make_pair(*possibleHoI4Tag, destCountry));
	}
}


void HoI4::World::importLeaderTraits()
{
	Log(LogLevel::Info) << "\tImporting leader traits";

	clearRegisteredKeywords();
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideologyName, std::istream& theStream) {
		commonItems::stringsOfItems traits(theStream);
		ideologicalLeaderTraits.insert(make_pair(ideologyName, traits.getStrings()));
	});
	parseFile("Configurables/converterLeaderTraits.txt");
}


void HoI4::World::importIdeologicalMinisters()
{
	Log(LogLevel::Info) << "\tImporting ideological ministers";

	HoI4::IdeologicalAdvisors theAdvisors;
	auto theAcutalAdvisors = theAdvisors.getAdvisors();
	ideologicalAdvisors.swap(theAcutalAdvisors);
}


void HoI4::World::convertGovernments(const Vic2::World& sourceWorld,
	 const Vic2::Localisations& vic2Localisations,
	 bool debug)
{
	Log(LogLevel::Info) << "\tConverting governments";
	for (auto country: countries)
	{
		country.second->convertGovernment(sourceWorld, governmentMap, vic2Localisations, *hoi4Localisations, debug);
	}
}


void HoI4::World::convertCountryNames(const Vic2::Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tConverting country names";
	const auto articleRules = ArticleRules::Factory{}.getRules("Configurables/Localisations/ArticleRules.txt");
	for (const auto& [tag, country]: countries)
	{
		hoi4Localisations->createCountryLocalisations(std::make_pair(country->getOldTag(), tag),
			 *countryNameMapper,
			 ideologies->getMajorIdeologies(),
			 vic2Localisations,
			 *articleRules);
		hoi4Localisations->updateMainCountryLocalisation(tag + "_" + country->getGovernmentIdeology(),
			 country->getOldTag(),
			 country->getOldGovernment(),
			 vic2Localisations,
			 *articleRules);
	}

	hoi4Localisations->addNonenglishCountryLocalisations();
}


void HoI4::World::convertParties(const Vic2::Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tConverting political parties";

	for (auto country: countries)
	{
		country.second->convertParties(ideologies->getMajorIdeologies(),
			 governmentMap,
			 vic2Localisations,
			 *hoi4Localisations);
	}
}


void HoI4::World::addNeutrality(bool debug)
{
	Log(LogLevel::Info) << "\tAdding neutrality";
	for (auto country: countries)
	{
		if (!ideologies->getMajorIdeologies().contains(country.second->getGovernmentIdeology()))
		{
			country.second->setGovernmentToExistingIdeology(ideologies->getMajorIdeologies(),
				 *ideologies,
				 governmentMap,
				 debug);
		}
	}
}


void HoI4::World::addLeaders()
{
	Log(LogLevel::Info) << "\tAdding leaders";
	auto configurableLeaders = CountryLeadersFactory{}.importCountryLeaders();

	for (auto& [tag, country]: countries)
	{
		auto leaders = configurableLeaders.equal_range(tag);
		for (auto i = leaders.first; i != leaders.second; ++i)
		{
			country->addLeader(i->second);
		}

		country->createLeader(*names, theGraphics);
	}
}


void HoI4::World::convertIdeologySupport()
{
	Log(LogLevel::Info) << "\tConverting ideology support";
	for (auto country: countries)
	{
		country.second->convertIdeologySupport(ideologies->getMajorIdeologies(), governmentMap);
	}
}


void HoI4::World::convertIndustry(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tConverting industry";

	map<string, double> factoryWorkerRatios = calculateFactoryWorkerRatios(theConfiguration);
	states->putIndustryInStates(factoryWorkerRatios, theCoastalProvinces, theConfiguration);

	calculateIndustryInCountries();
	reportIndustryLevels();
}


void HoI4::World::addStatesToCountries(const mappers::ProvinceMapper& provinceMapper)
{
	Log(LogLevel::Info) << "\tAdding states to countries";
	for (auto state: states->getStates())
	{
		auto owner = countries.find(state.second.getOwner());
		if (owner != countries.end())
		{
			owner->second->addState(state.second);
		}
	}

	const auto theRegions = Regions::Factory{}.getRegions();
	for (auto country: countries)
	{
		if (country.second->getStates().size() > 0)
		{
			landedCountries.insert(country);
		}
		country.second->determineCapitalFromVic2(provinceMapper, states->getProvinceToStateIDMap(), states->getStates());
		country.second->setCapitalRegionFlag(*theRegions);
	}
}


map<string, double> HoI4::World::calculateFactoryWorkerRatios(const Configuration& theConfiguration)
{
	map<string, double> industrialWorkersPerCountry = getIndustrialWorkersPerCountry();
	double totalWorldWorkers = getTotalWorldWorkers(industrialWorkersPerCountry);
	map<string, double> adjustedWorkersPerCountry =
		 adjustWorkers(industrialWorkersPerCountry, totalWorldWorkers, theConfiguration);
	double acutalWorkerFactoryRatio =
		 getWorldwideWorkerFactoryRatio(adjustedWorkersPerCountry, totalWorldWorkers, theConfiguration);

	map<string, double> factoryWorkerRatios;
	for (auto country: landedCountries)
	{
		auto adjustedWorkers = adjustedWorkersPerCountry.find(country.first);
		double factories = adjustedWorkers->second * acutalWorkerFactoryRatio;

		const auto& actualWorkers = country.second->getEmployedWorkers();
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
		const auto& employedWorkers = country.second->getEmployedWorkers();
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
	 double totalWorldWorkers,
	 const Configuration& theConfiguration)
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
	 double totalWorldWorkers,
	 const Configuration& theConfiguration)
{
	double baseIndustry = 0.0;
	for (auto countryWorkers: workersInCountries)
	{
		baseIndustry += countryWorkers.second * 0.000019;
	}

	int defaultFactories = 1201;
	double deltaIndustry = baseIndustry - defaultFactories;
	deltaIndustry -= landedCountries.size();
	double newIndustry = baseIndustry - theConfiguration.getFactoryFactor() * deltaIndustry;
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

	Log(LogLevel::Info) << "\tTotal factories: " << militaryFactories + civilianFactories + dockyards;
	Log(LogLevel::Info) << "\t\t" << militaryFactories << " military factories";
	Log(LogLevel::Info) << "\t\t" << civilianFactories << " civilian factories";
	Log(LogLevel::Info) << "\t\t" << dockyards << " dockyards";
}


void HoI4::World::convertDiplomacy(const Vic2::World& sourceWorld)
{
	Log(LogLevel::Info) << "\tConverting diplomacy";
	convertAgreements(sourceWorld);
}


void HoI4::World::convertAgreements(const Vic2::World& sourceWorld)
{
	const auto& diplomacy = sourceWorld.getDiplomacy();
	for (auto agreement: diplomacy.getAgreements())
	{
		auto possibleHoI4Tag1 = countryMap.getHoI4Tag(agreement.getCountry1());
		if (!possibleHoI4Tag1)
		{
			continue;
		}
		auto possibleHoI4Tag2 = countryMap.getHoI4Tag(agreement.getCountry2());
		if (!possibleHoI4Tag2)
		{
			continue;
		}

		auto HoI4Country1 = countries.find(*possibleHoI4Tag1);
		auto HoI4Country2 = countries.find(*possibleHoI4Tag2);
		if (HoI4Country1 == countries.end())
		{
			Log(LogLevel::Warning) << "HoI4 country " << *possibleHoI4Tag1
										  << " used in diplomatic agreement doesn't exist";
			continue;
		}
		if (HoI4Country2 == countries.end())
		{
			Log(LogLevel::Warning) << "HoI4 country " << *possibleHoI4Tag2
										  << " used in diplomatic agreement doesn't exist";
			continue;
		}

		if (agreement.getType() == "alliance")
		{
			HoI4Country1->second->editAllies().insert(*possibleHoI4Tag2);
			HoI4Country2->second->editAllies().insert(*possibleHoI4Tag1);
		}

		if (agreement.getType() == "vassal")
		{
			HoI4Country1->second->addPuppet(*possibleHoI4Tag2);
			HoI4Country2->second->setPuppetMaster(*possibleHoI4Tag1);
		}
	}
}


void HoI4::World::convertTechs()
{
	Log(LogLevel::Info) << "\tConverting techs and research bonuses";

	const auto techMapper = Mappers::TechMapper::Factory{}.importTechMapper();

	mappers::techMapperFile file;
	unique_ptr<mappers::techMapper> techMap = file.takeTechMapper();

	for (auto country: countries)
	{
		country.second->convertTechnology(*techMapper, *techMap);
	}
}


void HoI4::World::convertMilitaries(const ProvinceDefinitions& provinceDefinitions,
	 const mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tConverting militaries";
	const HoI4::militaryMappings& specificMappings =
		 theMilitaryMappings->getMilitaryMappings(theConfiguration.getVic2Mods());

	convertArmies(specificMappings, provinceMapper, theConfiguration);
	convertNavies(specificMappings.getUnitMappings(),
		 specificMappings.getMtgUnitMappings(),
		 provinceDefinitions,
		 provinceMapper);
	convertAirforces(specificMappings.getUnitMappings());
}


void HoI4::World::convertArmies(const militaryMappings& localMilitaryMappings,
	 const mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\t\tConverting armies";

	for (auto& [tag, country]: countries)
	{
		country->convertArmies(localMilitaryMappings, *states, provinceMapper, theConfiguration);
		for (const auto& divisionLocation: country->getDivisionLocations())
		{
			states->giveProvinceControlToCountry(divisionLocation, tag);
		}
	}
}


void HoI4::World::convertNavies(const UnitMappings& unitMap,
	 const MtgUnitMappings& mtgUnitMap,
	 const ProvinceDefinitions& provinceDefinitions,
	 const mappers::ProvinceMapper& provinceMapper)
{
	Log(LogLevel::Info) << "\t\tConverting navies";

	ifstream variantsFile("Configurables/shipTypes.txt");
	if (!variantsFile.is_open())
	{
		std::runtime_error e("Could not open Configurables/shipTypes.txt. Double-check your converter installation");
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
			 provinceDefinitions,
			 provinceMapper);
		country.second->convertConvoys(unitMap);
	}
}


void HoI4::World::convertAirforces(const UnitMappings& unitMap)
{
	Log(LogLevel::Info) << "\t\tConverting air forces";

	for (auto country: countries)
	{
		country.second->convertAirForce(unitMap);
	}
}


void HoI4::World::determineGreatPowers(const Vic2::World& sourceWorld)
{
	Log(LogLevel::Info) << "\tDetermining great powers";
	for (auto greatPowerVic2Tag: sourceWorld.getGreatPowers())
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
	Log(LogLevel::Info) << "\tCreating naval treaty";
	std::optional<std::pair<std::string, std::string>> strongestGpNavies = getStrongestNavyGps();
	if (strongestGpNavies)
	{
		scriptedLocalisations->addNavyScriptedLocalisations(strongestGpNavies->first, strongestGpNavies->second);
		hoi4Localisations->addDecisionLocalisation(strongestGpNavies->first + "_Naval_treaty_nation",
			 "@" + strongestGpNavies->first + " [" + strongestGpNavies->first + ".GetName]");
		hoi4Localisations->addDecisionLocalisation(strongestGpNavies->second + "_Naval_treaty_nation",
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


void HoI4::World::createFactions(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tCreating Factions";

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
	auto possibleName = member->getName();
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
		Log(LogLevel::Warning) << "Could not get name when logging faction member";
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
	Log(LogLevel::Info) << "\tAdding focus trees";
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
	Log(LogLevel::Info) << "\tAdjusting research focuses";
	for (auto country: countries)
	{
		country.second->adjustResearchFocuses();
	}
}


void HoI4::World::addCountryElectionEvents(const std::set<string>& theMajorIdeologies,
	 const Vic2::Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tAdding country election events";

	for (auto country: countries)
	{
		events->addPartyChoiceEvent(country.first,
			 country.second->getParties(),
			 *onActions,
			 theMajorIdeologies,
			 vic2Localisations,
			 *hoi4Localisations);
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
	Log(LogLevel::Info) << "\tSetting sphere leaders";
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
	Log(LogLevel::Info) << "\tAdding influence";
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
	Log(LogLevel::Info) << "\tDetermining spherelings";
	for (auto& GP: greatPowers)
	{
		for (auto relationItr: GP->getRelations())
		{
			bool isInSphere = relationItr.second.getSphereLeader();
			bool notPuppet = !GP->getPuppets().contains(relationItr.first);
			auto allies = GP->getAllies();
			bool isAlly = allies.contains(relationItr.first);

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
	Log(LogLevel::Info) << "\tCalculating sphereling autonomy";
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


std::set<std::string> HoI4::World::getSouthAsianCountries() const
{
	std::set<std::string> southAsianCountries;
	for (const auto country: countries)
	{
		if (country.second->getFlags().contains("conv_south_asia"))
		{
			southAsianCountries.insert(country.first);
		}
	}

	return southAsianCountries;
}