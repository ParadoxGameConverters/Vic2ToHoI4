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
#include "Mappers/CasusBelli/CasusBellisFactory.h"
#include "Mappers/Country/CountryMapperFactory.h"
#include "Mappers/CountryName/CountryNameMapperFactory.h"
#include "Mappers/FactionName/FactionNameMapperFactory.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapperFactory.h"
#include "Mappers/Government/GovernmentMapperFactory.h"
#include "Mappers/Graphics/GraphicsMapperFactory.h"
#include "Mappers/Ideology/IdeologyMapperFactory.h"
#include "Mappers/Technology/ResearchBonusMapper.h"
#include "Mappers/Technology/ResearchBonusMapperFactory.h"
#include "Mappers/Technology/TechMapper.h"
#include "Mappers/Technology/TechMapperFactory.h"
#include "MilitaryMappings/MilitaryMappingsFile.h"
#include "Modifiers/DynamicModifiers.h"
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
#include <numeric>
#include <ranges>
using namespace std;



namespace
{

void checkAllProvincesAssignedToRegion(const HoI4::Regions& theRegions,
	 const std::map<int, HoI4::Province>& theProvinces)
{
	for (const auto& [provinceNumber, province]: theProvinces)
	{
		if (!province.isLandProvince())
		{
			continue;
		}

		if (const auto region = theRegions.getRegion(provinceNumber); !region.has_value())
		{
			Log(LogLevel::Warning) << "Province " << provinceNumber << " was not assigned to a region.";
		}
	}
}

} // namespace



HoI4::World::World(const Vic2::World& sourceWorld,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration):
	 theIdeas(std::make_unique<HoI4::Ideas>()),
	 theDecisions(make_unique<HoI4::decisions>(theConfiguration)), peaces(make_unique<HoI4::AiPeaces>()),
	 events(make_unique<HoI4::Events>()), onActions(make_unique<HoI4::OnActions>())
{
	Log(LogLevel::Progress) << "24%";
	Log(LogLevel::Info) << "Building HoI4 World";

	Mappers::CountryMapper::Factory countryMapperFactory;
	countryMap = countryMapperFactory.importCountryMapper(sourceWorld, theConfiguration.getDebug());

	auto vic2Localisations = sourceWorld.getLocalisations();
	hoi4Localisations = Localisation::Importer().generateLocalisations(theConfiguration);
	Log(LogLevel::Progress) << "28%";

	theDate = std::make_unique<date>(sourceWorld.getDate());

	ProvinceDefinitions provinceDefinitions =
		 ProvinceDefinitions::Importer().importProvinceDefinitions(theConfiguration);
	theMapData = std::make_unique<MapData>(provinceDefinitions, theConfiguration);
	const auto theProvinces = importProvinces(theConfiguration);
	theCoastalProvinces.init(*theMapData, theProvinces);
	strategicRegions = StrategicRegions::Factory().importStrategicRegions(theConfiguration);
	states = std::make_unique<States>(sourceWorld,
		 *countryMap,
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
	Log(LogLevel::Progress) << "32%";
	names = Names::Factory().getNames(theConfiguration);
	graphicsMapper = Mappers::GraphicsMapper::Factory().importGraphicsMapper();
	graphicsMapper->debugPortraits(theConfiguration);
	countryNameMapper = Mappers::CountryNameMapper::Factory().importCountryNameMapper();
	casusBellis = Mappers::CasusBellisFactory{}.importCasusBellis();
	Log(LogLevel::Progress) << "36%";
	convertCountries(sourceWorld, provinceMapper);
	determineGreatPowers(sourceWorld);
	governmentMapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();
	ideologyMapper = Mappers::IdeologyMapper::Factory().importIdeologyMapper();
	convertGovernments(sourceWorld, vic2Localisations, theConfiguration.getDebug());
	ideologies = std::make_unique<Ideologies>(theConfiguration);
	ideologies->identifyMajorIdeologies(greatPowers, countries, theConfiguration);
	Log(LogLevel::Progress) << "40%";
	convertWars(sourceWorld, provinceMapper);
	supplyZones = new HoI4::SupplyZones(states->getDefaultStates(), theConfiguration);
	buildings = new Buildings(*states, theCoastalProvinces, *theMapData, provinceDefinitions, theConfiguration);
	theRegions = Regions::Factory().getRegions();
	Log(LogLevel::Progress) << "44%";
	if (theConfiguration.getDebug())
	{
		checkAllProvincesAssignedToRegion(*theRegions, theProvinces);
	}

	addStatesToCountries(provinceMapper);
	states->addCapitalsToStates(countries);
	intelligenceAgencies = IntelligenceAgencies::Factory::createIntelligenceAgencies(countries, *names);
	hoi4Localisations->addStateLocalisations(*states, vic2Localisations, provinceMapper, theConfiguration);
	Log(LogLevel::Progress) << "48%";
	convertIndustry(theConfiguration);
	addProvincesToHomeAreas();
	addDominions(countryMapperFactory);
	addUnrecognizedNations(countryMapperFactory);
	states->addCoresToCorelessStates(sourceWorld.getCountries(),
		 provinceMapper,
		 sourceWorld.getProvinces(),
		 theConfiguration.getDebug());
	determineCoresAndClaims();
	Log(LogLevel::Progress) << "52%";
	states->convertResources();
	supplyZones->convertSupplyZones(*states);
	strategicRegions->convert(*states);
	convertDiplomacy(sourceWorld);
	convertStrategies(sourceWorld);
	convertTechs();
	Log(LogLevel::Progress) << "56%";

	convertCountryNames(vic2Localisations);
	scriptedLocalisations = ScriptedLocalisations::Factory().getScriptedLocalisations();
	scriptedLocalisations->updateIdeologyLocalisations(ideologies->getMajorIdeologies());
	scriptedLocalisations->filterIdeologyLocalisations(ideologies->getMajorIdeologies());
	hoi4Localisations->generateCustomLocalisations(*scriptedLocalisations, ideologies->getMajorIdeologies());
	Log(LogLevel::Progress) << "60%";

	militaryMappingsFile importedMilitaryMappings;
	theMilitaryMappings = importedMilitaryMappings.takeAllMilitaryMappings();
	convertMilitaries(provinceDefinitions, provinceMapper, theConfiguration);

	scriptedEffects = std::make_unique<ScriptedEffects>(theConfiguration.getHoI4Path());
	setupNavalTreaty();
	Log(LogLevel::Progress) << "64%";

	importLeaderTraits();

	scriptedEffects->updateOperationStratEffects(ideologies->getMajorIdeologies());

	genericFocusTree.addGenericFocusTree(ideologies->getMajorIdeologies());
	importIdeologicalMinisters();
	convertParties(vic2Localisations);
	events->createPoliticalEvents(ideologies->getMajorIdeologies(), *hoi4Localisations);
	events->createWarJustificationEvents(ideologies->getMajorIdeologies(), *hoi4Localisations);
	events->importElectionEvents(ideologies->getMajorIdeologies(), *onActions);
	events->importCapitulationEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->importMtgNavalTreatyEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->importLarOccupationEvents(theConfiguration, ideologies->getMajorIdeologies());
	addCountryElectionEvents(ideologies->getMajorIdeologies(), vic2Localisations);
	events->createStabilityEvents(ideologies->getMajorIdeologies(), theConfiguration);
	events->generateGenericEvents(theConfiguration, ideologies->getMajorIdeologies());
	events->giveGovernmentInExileEvent(createGovernmentInExileEvent(ideologies->getMajorIdeologies()));
	theIdeas->updateIdeas(ideologies->getMajorIdeologies());
	Log(LogLevel::Progress) << "68%";
	theDecisions->updateDecisions(ideologies->getMajorIdeologies(),
		 states->getProvinceToStateIDMap(),
		 states->getDefaultStates(),
		 *events,
		 getSouthAsianCountries(),
		 strongestGpNavies);
	updateAiPeaces(*peaces, ideologies->getMajorIdeologies());
	addNeutrality(theConfiguration.getDebug());
	addLeaders();
	convertIdeologySupport();
	Log(LogLevel::Progress) << "72%";
	states->convertCapitalVPs(countries, greatPowers);
	states->convertAirBases(countries, greatPowers);
	factionNameMapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();
	if (theConfiguration.getCreateFactions())
	{
		createFactions(theConfiguration);
	}

	HoI4WarCreator warCreator(this, *theMapData, provinceDefinitions, *hoi4Localisations, theConfiguration);

	transferPuppetsToDominions();

	addFocusTrees();
	adjustResearchFocuses();

	dynamicModifiers.updateDynamicModifiers(ideologies->getMajorIdeologies());
	scriptedTriggers.importScriptedTriggers(theConfiguration);
	updateScriptedTriggers(scriptedTriggers, ideologies->getMajorIdeologies());
	Log(LogLevel::Progress) << "76%";

	countryCategories =
		 createCountryCategories(*countryMap, countries, ideologies->getMajorIdeologies(), theConfiguration.getDebug());

	gameRules = std::make_unique<GameRules>(
		 GameRules::Parser().parseRulesFile(theConfiguration.getHoI4Path() + "/common/game_rules/00_game_rules.txt"));
	gameRules->updateRules();

	occupationLaws = OccupationLaws::Factory().getOccupationLaws(theConfiguration);
	occupationLaws->updateLaws(ideologies->getMajorIdeologies());

	operativeNames = OperativeNames::Factory::getOperativeNames(theConfiguration.getHoI4Path());
	operativeNames->addCountriesToNameSets(countries);

	operations = Operations::Factory().getOperations(theConfiguration.getHoI4Path());
	operations->updateOperations(ideologies->getMajorIdeologies());

	soundEffects = SoundEffectsFactory().createSoundEffects(countries);

	recordUnbuiltCanals(sourceWorld);
}


shared_ptr<HoI4::Country> HoI4::World::findCountry(const string& countryTag) const
{
	auto country = countries.find(countryTag);
	if (country == countries.end())
	{
		return {};
	}

	return country->second;
}


void HoI4::World::convertCountries(const Vic2::World& sourceWorld, const Mappers::ProvinceMapper& provinceMapper)
{
	Log(LogLevel::Info) << "\tConverting countries";

	const auto flagsToIdeasMapper = Mappers::FlagsToIdeasMapper::Factory().importFlagsToIdeaMapper();

	for (const auto& [tag, country]: sourceWorld.getCountries())
	{
		convertCountry(tag, country, *flagsToIdeasMapper, provinceMapper);
	}

	int numHumanCountries = 0;
	for (const auto& [tag, country]: countries)
	{
		if (country->isHuman())
		{
			humanCountry = tag;
			numHumanCountries++;
		}
	}
	if (numHumanCountries > 1)
	{
		humanCountry = std::nullopt;
	}
}


void HoI4::World::convertCountry(const std::string& oldTag,
	 const Vic2::Country& oldCountry,
	 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	// don't convert rebels
	if (oldTag == "REB")
	{
		return;
	}

	HoI4::Country* destCountry = nullptr;
	auto possibleHoI4Tag = countryMap->getHoI4Tag(oldTag);
	if (!possibleHoI4Tag)
	{
		Log(LogLevel::Warning) << "Could not convert V2 tag " << oldTag << " to HoI4";
	}
	else
	{
		destCountry = new HoI4::Country(*possibleHoI4Tag,
			 oldCountry,
			 *names,
			 *graphicsMapper,
			 *countryMap,
			 flagsToIdeasMapper,
			 *hoi4Localisations,
			 *theDate,
			 provinceMapper,
			 *states);
		if (destCountry->getCapitalState())
		{
			countries.insert(make_pair(*possibleHoI4Tag, destCountry));
		}
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
	std::mt19937 femaleChanceGenerator;
	for (auto& country: countries | std::views::values)
	{
		country->convertGovernment(sourceWorld,
			 *governmentMapper,
			 vic2Localisations,
			 *hoi4Localisations,
			 *graphicsMapper,
			 *names,
			 femaleChanceGenerator,
			 debug);
	}
}


void HoI4::World::convertCountryNames(const Vic2::Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tConverting country names";
	const auto articleRules = ArticleRules::Factory().getRules("Configurables/Localisations/ArticleRules.txt");
	for (const auto& [tag, country]: countries)
	{
		if (country->isGeneratedDominion())
		{
			const auto& ownerOldTag = country->getPuppetMasterOldTag();
			hoi4Localisations->createGeneratedDominionLocalisations(tag,
				 *country,
				 vic2Localisations,
				 ideologies->getMajorIdeologies(),
				 *articleRules);
		}
		else if (country->isUnrecognizedNation())
		{
			hoi4Localisations->createUnrecognizedNationLocalisations(tag,
				 *country,
				 vic2Localisations,
				 *countryNameMapper,
				 ideologies->getMajorIdeologies(),
				 *articleRules);
		}
		else
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
	}

	hoi4Localisations->addNonenglishCountryLocalisations();
}


void HoI4::World::convertParties(const Vic2::Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tConverting political parties";

	for (auto country: countries)
	{
		country.second->convertParties(ideologies->getMajorIdeologies(),
			 *ideologyMapper,
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
				 *governmentMapper,
				 debug);
		}
	}
}


void HoI4::World::addLeaders()
{
	Log(LogLevel::Info) << "\tAdding leaders";
	auto configurableLeaders = CountryLeadersFactory().importCountryLeaders();

	for (auto& [tag, country]: countries)
	{
		auto leaders = configurableLeaders.equal_range(tag);
		for (auto i = leaders.first; i != leaders.second; ++i)
		{
			country->addLeader(i->second);
		}

		country->createLeader(*names, *graphicsMapper);
	}
}


void HoI4::World::convertIdeologySupport()
{
	Log(LogLevel::Info) << "\tConverting ideology support";
	for (auto country: countries)
	{
		country.second->convertIdeologySupport(ideologies->getMajorIdeologies(), *ideologyMapper);
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


void HoI4::World::addStatesToCountries(const Mappers::ProvinceMapper& provinceMapper)
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

	for (auto& country: countries)
	{
		if (country.second->getStates().size() > 0)
		{
			landedCountries.insert(country);
		}
		country.second->determineCapitalFromVic2(provinceMapper, states->getProvinceToStateIDMap(), states->getStates());
		country.second->setCapitalRegionFlag(*theRegions);

		auto possibleCapitalState = country.second->getCapitalState();
		if (!possibleCapitalState)
		{
			return;
		}
		auto& modifiableStates = states->getModifiableStates();
		if (auto capital = modifiableStates.find(*possibleCapitalState); capital != modifiableStates.end())
		{
			capital->second.addCores({country.first});
		}
	}
}


void HoI4::World::addDominions(Mappers::CountryMapper::Factory& countryMapperFactory)
{
	for (auto& [stateId, state]: states->getModifiableStates())
	{
		const auto& provinces = state.getProvinces();
		if (provinces.empty())
		{
			continue;
		}
		const auto& stateRegion = theRegions->getRegion(*provinces.begin());

		const auto& ownerTag = state.getOwner();
		if (ownerTag == "UCV")
		{
			continue;
		}
		const auto& owner = countries.find(ownerTag);
		if (owner == countries.end())
		{
			continue;
		}
		if (owner->second->isProvinceInHomeArea(*provinces.begin()))
		{
			continue;
		}
		if (owner->second->getPrimaryCulture() == "alien" || owner->second->getPrimaryCulture() == "undead")
		{
			continue;
		}
		const auto& ownerCapitalProvince = owner->second->getCapitalProvince();
		if (!ownerCapitalProvince)
		{
			continue;
		}
		const auto& ownerRegion = theRegions->getRegion(*ownerCapitalProvince);

		const bool differentRegions =
			 ((stateRegion && !ownerRegion) || (stateRegion && ownerRegion && *stateRegion != *ownerRegion));
		if (!differentRegions)
		{
			continue;
		}

		if (state.getCores().contains(owner->first))
		{
			continue;
		}

		auto dominion = getDominion(owner->first, owner->second, *stateRegion, *theRegions, *graphicsMapper, *names);
		dominion->addCoreState(stateId);
	}

	auto& modifiableStates = states->getModifiableStates();
	for (auto& dominion: dominions | std::views::values)
	{
		const auto overlord = dominion->getPuppetMaster();
		if (!overlord)
		{
			continue;
		}
		if (!dominionIsReleasable(*dominion))
		{
			continue;
		}

		const auto dominionTag = countryMapperFactory.generateNewHoI4Tag();
		dominion->addTag(dominionTag, *names, *hoi4Localisations);
		dominion->addMonarchIdea(*overlord);
		countries.emplace(dominionTag, dominion);

		if (const auto& dominionLevel = theRegions->getRegionLevel(dominion->getRegion()); dominionLevel)
		{
			overlord->addPuppet(dominionTag, *dominionLevel);
		}
		else
		{
			overlord->addPuppet(dominionTag, "autonomy_dominion");
		}
		overlord->addGeneratedDominion(dominion->getRegion(), dominionTag);

		for (const auto& stateId: dominion->getCoreStates())
		{
			if (auto state = modifiableStates.find(stateId); state != modifiableStates.end())
			{
				state->second.addCores({dominionTag});
				state->second.setOwner(dominionTag);
				dominion->addState(state->second);
			}
		}

		dominion->determineBestCapital(states->getStates());
		dominion->setCapitalRegionFlag(*theRegions);

		auto possibleCapitalState = dominion->getCapitalState();
		if (!possibleCapitalState)
		{
			return;
		}
		auto& modifiableStates = states->getModifiableStates();
		if (auto capital = modifiableStates.find(*possibleCapitalState); capital != modifiableStates.end())
		{
			capital->second.addCores({dominionTag});
		}
	}
}


std::shared_ptr<HoI4::Country> HoI4::World::getDominion(const std::string& ownerTag,
	 const std::shared_ptr<Country>& owner,
	 const std::string& region,
	 const Regions& regions,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names)
{
	if (const auto& dominionItr = dominions.find(std::make_pair(ownerTag, region)); dominionItr != dominions.end())
	{
		return dominionItr->second;
	}

	auto dominion = std::make_shared<Country>(owner, region, regions, graphicsMapper, names);
	dominions.emplace(std::make_pair(ownerTag, region), dominion);

	return dominion;
}


bool HoI4::World::dominionIsReleasable(const Country& dominion)
{
	return dominion.getCoreStates().size() > 1;
}


void HoI4::World::transferPuppetsToDominions()
{
	for (auto& country: countries | std::views::values)
	{
		std::map<std::string, std::set<std::string>> regionalPuppets; // <region, puppets>
		for (const auto& puppetTag: country->getPuppets() | std::views::keys)
		{
			const auto& puppetItr = countries.find(puppetTag);
			if (puppetItr == countries.end())
			{
				continue;
			}
			const auto& puppet = puppetItr->second;
			if (puppet->isGeneratedDominion())
			{
				continue;
			}
			const auto& capital = puppet->getCapitalProvince();
			if (!capital)
			{
				continue;
			}
			const auto& region = theRegions->getRegion(*capital);
			if (region)
			{
				regionalPuppets[*region].insert(puppetTag);
			}
		}

		for (const auto& [region, puppets]: regionalPuppets)
		{
			const auto& dominionTag = country->getDominionTag(region);
			if (!dominionTag)
			{
				continue;
			}
			auto dominion = countries.find(*dominionTag);
			if (dominion != countries.end())
			{
				country->transferPuppets(puppets, dominion->second);
			}
		}
	}
}


void HoI4::World::addUnrecognizedNations(Mappers::CountryMapper::Factory& countryMapperFactory)
{
	for (auto& [stateId, state]: states->getModifiableStates())
	{
		const auto& provinces = state.getProvinces();
		if (provinces.empty())
		{
			continue;
		}
		const auto& stateRegion = theRegions->getRegion(*provinces.begin());

		const auto& ownerTag = state.getOwner();
		if (!ownerTag.empty())
		{
			continue;
		}

		auto nation = getUnrecognizedNation(*stateRegion, *theRegions, *graphicsMapper, *names);
		nation->addCoreState(stateId);
		state.smashNavalBases();
	}

	auto& modifiableStates = states->getModifiableStates();
	for (auto& nation: unrecognizedNations | std::views::values)
	{
		const auto nationTag = countryMapperFactory.generateNewHoI4Tag();
		nation->addTag(nationTag, *names, *hoi4Localisations);
		countries.emplace(nationTag, nation);

		for (const auto& stateId: nation->getCoreStates())
		{
			if (auto state = modifiableStates.find(stateId); state != modifiableStates.end())
			{
				state->second.addCores({nationTag});
				state->second.setOwner(nationTag);
				nation->addState(state->second);
			}
		}

		nation->determineBestCapital(states->getStates());
		nation->setCapitalRegionFlag(*theRegions);

		auto possibleCapitalState = nation->getCapitalState();
		if (!possibleCapitalState)
		{
			return;
		}
		auto& modifiableStates = states->getModifiableStates();
		if (auto capital = modifiableStates.find(*possibleCapitalState); capital != modifiableStates.end())
		{
			capital->second.addCores({nationTag});
		}
	}
}


std::shared_ptr<HoI4::Country> HoI4::World::getUnrecognizedNation(const std::string& region,
	 const Regions& regions,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names)
{
	if (const auto& unrecognizedItr = unrecognizedNations.find(region); unrecognizedItr != unrecognizedNations.end())
	{
		return unrecognizedItr->second;
	}

	auto nation = std::make_shared<Country>(region, regions, graphicsMapper, names);
	unrecognizedNations.emplace(region, nation);

	return nation;
}


void HoI4::World::determineCoresAndClaims()
{
	for (const auto& [id, state]: states->getStates())
	{
		for (const auto& coreTag: state.getCores())
		{
			if (const auto& coreCountry = findCountry(coreTag); coreCountry)
			{
				coreCountry->addCoreState(id);
			}
		}
		for (const auto& claimTag: state.getClaims())
		{
			if (const auto& claimCountry = findCountry(claimTag); claimCountry)
			{
				claimCountry->addClaimedState(id);
			}
		}
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
	const auto& diplomacy = sourceWorld.getDiplomacy();
	for (auto agreement: diplomacy.getAgreements())
	{
		auto possibleHoI4Tag1 = countryMap->getHoI4Tag(agreement.getCountry1());
		if (!possibleHoI4Tag1)
		{
			continue;
		}
		auto possibleHoI4Tag2 = countryMap->getHoI4Tag(agreement.getCountry2());
		if (!possibleHoI4Tag2)
		{
			continue;
		}

		auto HoI4Country1 = countries.find(*possibleHoI4Tag1);
		auto HoI4Country2 = countries.find(*possibleHoI4Tag2);
		if (HoI4Country1 == countries.end())
		{
			continue;
		}
		if (HoI4Country2 == countries.end())
		{
			continue;
		}

		if (agreement.getType() == "alliance")
		{
			HoI4Country1->second->editAllies().insert(*possibleHoI4Tag2);
			HoI4Country2->second->editAllies().insert(*possibleHoI4Tag1);
		}

		if (agreement.getType() == "vassal")
		{
			HoI4Country1->second->addPuppet(*possibleHoI4Tag2, "autonomy_dominion");
			HoI4Country2->second->setPuppetMaster(HoI4Country1->second);
		}
	}
}


void HoI4::World::convertStrategies(const Vic2::World& sourceWorld)
{
	Log(LogLevel::Info) << "\tConverting strategies";
	for (const auto& country: countries | std::views::values)
	{
		if (const auto& sourceCountries = sourceWorld.getCountries(); sourceCountries.contains(country->getOldTag()))
		{
			country->convertStrategies(*countryMap, sourceCountries.at(country->getOldTag()), countries);
		}
	}
}


void HoI4::World::convertWars(const Vic2::World& sourceWorld, const Mappers::ProvinceMapper& provinceMapper)
{
	for (const auto& [sourceTag, sourceCountry]: sourceWorld.getCountries())
	{
		auto possibleHoI4Tag = countryMap->getHoI4Tag(sourceTag);
		if (!possibleHoI4Tag)
		{
			continue;
		}

		auto country = countries.find(*possibleHoI4Tag);
		if (country == countries.end())
		{
			continue;
		}

		country->second->convertWars(sourceCountry,
			 *countryMap,
			 *casusBellis,
			 provinceMapper,
			 states->getProvinceToStateIDMap());
	}
}


void HoI4::World::convertTechs()
{
	Log(LogLevel::Info) << "\tConverting techs and research bonuses";

	const auto techMapper = Mappers::TechMapper::Factory().importTechMapper();
	const auto researchBonusMapper = Mappers::ResearchBonusMapper::Factory().importResearchBonusMapper();

	for (const auto& [unused, country]: countries)
	{
		country->convertTechnology(*techMapper, *researchBonusMapper);
	}
}


void HoI4::World::convertMilitaries(const ProvinceDefinitions& provinceDefinitions,
	 const Mappers::ProvinceMapper& provinceMapper,
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
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\t\tConverting armies";

	for (auto& [tag, country]: countries)
	{
		std::set<std::string> ownersToSkip;
		for (const auto& puppetTag: country->getPuppets() | std::views::keys)
		{
			ownersToSkip.insert(puppetTag);
		}
		for (const auto& [tag, relation]: country->getRelations())
		{
			if (relation.hasMilitaryAccess())
			{
				ownersToSkip.insert(tag);
			}
		}

		country->convertArmies(localMilitaryMappings, *states, provinceMapper, theConfiguration);
		if (!country->getProvinces().empty())
		{
			for (const auto& divisionLocation: country->getDivisionLocations())
			{
				states->giveProvinceControlToCountry(divisionLocation, tag, ownersToSkip);
			}
		}
	}
}


void HoI4::World::convertNavies(const UnitMappings& unitMap,
	 const MtgUnitMappings& mtgUnitMap,
	 const ProvinceDefinitions& provinceDefinitions,
	 const Mappers::ProvinceMapper& provinceMapper)
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
		auto possibleGreatPowerTag = countryMap->getHoI4Tag(greatPowerVic2Tag);
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
	strongestGpNavies = getStrongestNavyGps();
	if (!strongestGpNavies.empty())
	{
		scriptedLocalisations->addNavyScriptedLocalisations(strongestGpNavies);
		for (const auto& strongestGpNavy: strongestGpNavies)
		{
			hoi4Localisations->addDecisionLocalisation(strongestGpNavy + "_Naval_treaty_nation",
				 "@" + strongestGpNavy + " [" + strongestGpNavy + ".GetName]");
		}

		auto numAdherents = 0;
		for (const auto& greatPower: greatPowers)
		{
			if (greatPower->getNavalStrength() > 0)
			{
				greatPower->makeNavalTreatyAdherent();
				numAdherents++;
			}
		}

		(*greatPowers.begin())->makeGreatestNavalPower();
		(*greatPowers.begin())->setNumberOfAdherents(numAdherents);
	}
}


void HoI4::World::createFactions(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tCreating Factions";

	ofstream factionsLog;
	if (theConfiguration.getDebug())
	{
		factionsLog.open("factions-logs.csv");
		factionsLog << "name,government,initial military strength,strength per year,strength by 1939\n";
	}

	for (const auto& leader: greatPowers)
	{
		if (leader->isInFaction())
		{
			continue;
		}

		std::vector<std::shared_ptr<Country>> factionMembers;
		factionMembers.push_back(leader);

		std::string leaderIdeology = leader->getGovernmentIdeology();

		for (const auto& allyTag: leader->getAllies())
		{
			auto allyCountry = findCountry(allyTag);
			if (!allyCountry || !allyCountry->isGreatPower() || allyCountry->isInFaction())
			{
				continue;
			}

			if (governmentsAllowFaction(leaderIdeology, allyCountry->getGovernmentIdeology()))
			{
				factionMembers.push_back(allyCountry);
			}
		}

		if (factionMembers.size() > 1)
		{
			if (theConfiguration.getDebug())
			{
				factionsLog << "\n";
			}

			double factionStrength = 0.0;

			auto newFaction = make_shared<Faction>(leader,
				 factionMembers,
				 factionNameMapper->getFactionName(leader->getGovernmentIdeology(),
					  leader->getPrimaryCulture(),
					  leader->getPrimaryCultureGroup()));
			for (const auto& member: factionMembers)
			{
				if (theConfiguration.getDebug())
				{
					logFactionMember(factionsLog, *member);
					factionStrength += member->getStrengthOverTime(3.0);
				}
				member->setFaction(newFaction);
			}

			factions.push_back(newFaction);

			if (theConfiguration.getDebug())
			{
				factionsLog << "Faction Strength in 1939," << factionStrength << "\n";
			}
		}
	}

	if (theConfiguration.getDebug())
	{
		factionsLog.close();
	}
}


void HoI4::World::logFactionMember(std::ofstream& factionsLog, const Country& member) const
{
	factionsLog << member.getTag() << ",";
	factionsLog << member.getGovernmentIdeology() << ",";
	factionsLog << member.getMilitaryStrength() << ",";
	factionsLog << member.getEconomicStrength(1.0) << ",";
	factionsLog << member.getEconomicStrength(3.0) << "\n";
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
	for (auto [tag, country]: countries)
	{
		if (tag == "UCV" || country->isUnrecognizedNation())
		{
			country->addEmptyFocusTree();
			continue;
		}

		if (country->isGreatPower() || (country->getStrengthOverTime(3) > 4500))
		{
			country->addGenericFocusTree(ideologies->getMajorIdeologies());
		}
		if (country->isGeneratedDominion() && !country->getPuppets().empty())
		{
			country->addGenericFocusTree(ideologies->getMajorIdeologies());
			country->addPuppetsIntegrationTree(*hoi4Localisations);
		}
		if (genericFocusTree.getBranches().contains("uk_colonial_focus") && country->isGreatPower() &&
			 country->getDominionTag("south_asia"))
		{
			country->addGlobalEventTarget("uk_colonial_focus_ENG");
			country->addFocusTreeBranch("uk_colonial_focus", *onActions);
			genericFocusTree.eraseBranch("uk_colonial_focus");
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

	for (auto& [tag, country]: countries)
	{
		if (country->isUnrecognizedNation())
		{
			continue;
		}
		events->addPartyChoiceEvent(tag,
			 country->getParties(),
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


struct gpStrengthStruct
{
	std::string tag;
	float strength;
	int meansIndex;
};

struct meansStruct
{
	float value;
	std::vector<float> strengthAssignments;
	std::vector<std::string> tags;
	bool operator<(const meansStruct& rhs) const { return value < rhs.value; }
};

struct modelStruct
{
	std::vector<gpStrengthStruct> gpStrengths;
	std::vector<meansStruct> means;
	float score;
};


// Initialize a k-means model.
// The great powers hold their tag and naval strength and are assigned the the first means
// The means are distributed evenly across the range of naval strengths
modelStruct initializeModel(int numMeans,
	 float strongestNavy,
	 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers)
{
	modelStruct model;

	for (const auto& greatPower: greatPowers)
	{
		model.gpStrengths.push_back(
			 {.tag = greatPower->getTag(), .strength = greatPower->getNavalStrength(), .meansIndex = 0});
	}
	for (auto i = 0; i < numMeans; i++)
	{
		model.means.push_back({.value = i * strongestNavy / (numMeans - 1)});
	}

	return model;
}


// run the naive k-means algorithm as described here:
// https://en.wikipedia.org/wiki/K-means_clustering#Standard_algorithm_(naive_k-means)
void runKMeans(modelStruct& model)
{
	bool assignmentsChanged;
	do
	{
		assignmentsChanged = false;
		for (auto& mean: model.means)
		{
			mean.tags.clear();
		}

		// assignment
		for (auto& gpStrength: model.gpStrengths)
		{
			auto leastDistance = std::abs(model.means[gpStrength.meansIndex].value - gpStrength.strength);
			for (auto i = 0; i < model.means.size(); i++)
			{
				if (std::abs(model.means[i].value - gpStrength.strength) < leastDistance)
				{
					leastDistance = std::abs(model.means[i].value - gpStrength.strength);
					gpStrength.meansIndex = i;
					assignmentsChanged = true;
				}
			}
			model.means[gpStrength.meansIndex].strengthAssignments.push_back(gpStrength.strength);
			model.means[gpStrength.meansIndex].tags.push_back(gpStrength.tag);
		}

		// adjustment
		for (auto& mean: model.means)
		{
			if (!mean.strengthAssignments.empty())
			{
				mean.value = std::accumulate(mean.strengthAssignments.begin(), mean.strengthAssignments.end(), 0.0F) /
								 mean.strengthAssignments.size();
				mean.strengthAssignments.clear();
			}
		}
	} while (assignmentsChanged);
}


// find sum of the deviations between each strength and the mean it's associated with. Lower is better.
float rateModel(const modelStruct& model)
{
	float score = 0.0F;
	for (const auto& gpStrength: model.gpStrengths)
	{
		const auto difference = gpStrength.strength - model.means[gpStrength.meansIndex].value;
		score += difference * difference;
	}

	return score;
}


// Identify the countries with the strongest navies by examining Great Power naval strengths, finding the clusters of
// similar strength, and returning the strongest cluster Clusters are found using the naive k-means clustering algorithm
// To identify the number of clusters, run k-means assuming two clusters, then run repeated k-means clustering with
// increasing numbers of clusters until this gives no improvement When there is no improvement, use the previous run for
// analysis
std::vector<std::string> HoI4::World::getStrongestNavyGps()
{
	float strongestNavy = 0.0;
	for (const auto& greatPower: greatPowers)
	{
		const auto strength = greatPower->getNavalStrength();
		if (strength > strongestNavy)
		{
			strongestNavy = strength;
		}
	}

	modelStruct model = initializeModel(1, strongestNavy, greatPowers);
	runKMeans(model);
	model.score = rateModel(model);
	for (int i = 2; i <= greatPowers.size(); i++)
	{
		modelStruct newModel = initializeModel(i, strongestNavy, greatPowers);
		runKMeans(newModel);
		newModel.score = rateModel(newModel);
		if (newModel.score >= model.score)
		{
			break;
		}
		model = newModel;
	}

	return std::max_element(model.means.begin(), model.means.end())->tags;
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


void HoI4::World::addProvincesToHomeAreas()
{
	Log(LogLevel::Info) << "Adding provinces to home areas";
	for (const auto& country: landedCountries | std::views::values)
	{
		const auto& capital = country->getCapitalProvince();
		if (!capital)
		{
			continue;
		}
		country->addProvincesToHomeArea(*capital, theMapData, states->getStates(), states->getProvinceToStateIDMap());
	}
}


void HoI4::World::recordUnbuiltCanals(const Vic2::World& sourceWorld)
{
	auto greatestCountry = greatPowers.front();

	bool kielCanalBuilt = false;
	bool panamaCanalBuilt = false;
	bool suezCanalBuilt = false;
	for (const auto& province: sourceWorld.getProvinces() | std::views::values)
	{
		const auto& flags = province->getFlags();
		if (flags.contains("kiel_canal"))
		{
			kielCanalBuilt = true;
		}
		else if (flags.contains("panama_canal"))
		{
			panamaCanalBuilt = true;
		}
		else if (flags.contains("suez_canal"))
		{
			suezCanalBuilt = true;
		}
	}

	if (!kielCanalBuilt)
	{
		greatestCountry->addUnbuiltCanal("KIEL_CANAL_UNBUILT");
	}
	if (!panamaCanalBuilt)
	{
		greatestCountry->addUnbuiltCanal("PANAMA_CANAL_UNBUILT");
	}
	if (!suezCanalBuilt)
	{
		greatestCountry->addUnbuiltCanal("SUEZ_CANAL_UNBUILT");
	}
}