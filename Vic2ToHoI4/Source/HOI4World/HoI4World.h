#ifndef HOI4_WORLD_H_
#define HOI4_WORLD_H_



#include "CountryCategories/CountryCategories.h"
#include "Decisions/Decisions.h"
#include "Diplomacy/AIPeaces.h"
#include "Events/Events.h"
#include "GameRules/GameRules.h"
#include "HoI4Country.h"
#include "HoI4Localisation.h"
#include "Ideas/Ideas.h"
#include "Ideologies/Ideologies.h"
#include "Ideologies/Ideology.h"
#include "IntelligenceAgencies/IntelligenceAgencies.h"
#include "Leaders/Advisor.h"
#include "Localisations/ArticleRules/ArticleRules.h"
#include "Map/Buildings.h"
#include "Map/CoastalProvinces.h"
#include "Map/MapData.h"
#include "Map/StrategicRegion.h"
#include "Map/StrategicRegions.h"
#include "Map/SupplyZones.h"
#include "Mappers/Country/CountryMapper.h"
#include "Mappers/CountryName/CountryNameMapper.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/Government/GovernmentMapper.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Mappers/Ideology/IdeologyMapper.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Technology/TechMapper.h"
#include "Military/DivisionTemplate.h"
#include "MilitaryMappings/AllMilitaryMappings.h"
#include "MilitaryMappings/HoI4UnitType.h"
#include "MilitaryMappings/UnitMappings.h"
#include "Modifiers/DynamicModifiers.h"
#include "Modifiers/Modifier.h"
#include "Names/Names.h"
#include "OccupationLaws/OccupationLawsFactory.h"
#include "OnActions.h"
#include "Operations/Operations.h"
#include "OperativeNames/OperativeNames.h"
#include "Parser.h"
#include "ProvinceDefinitions.h"
#include "ScriptedEffects/ScriptedEffects.h"
#include "ScriptedLocalisations/ScriptedLocalisations.h"
#include "ScriptedTriggers/ScriptedTriggers.h"
#include "Sounds/SoundEffect.h"
#include "States/DefaultState.h"
#include "States/HoI4State.h"
#include "States/HoI4States.h"
#include "V2World/Countries/Country.h"
#include "V2World/World/World.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class World: commonItems::parser
{
  public:
	explicit World(const Vic2::World& sourceWorld,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	~World() = default;

	[[nodiscard]] const auto& getHumanCountry() const { return humanCountry; }
	[[nodiscard]] auto& getNames() { return names; }
	[[nodiscard]] const auto& getNames() const { return *names; }
	[[nodiscard]] const auto& getTheStates() const { return *states; }
	[[nodiscard]] const auto& getStrategicRegions() const { return *strategicRegions; }
	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getMilitaryMappings() const { return *theMilitaryMappings; }
	[[nodiscard]] auto& getGraphicsMapper() { return *graphicsMapper; }
	[[nodiscard]] const auto& getIdeologicalLeaderTraits() const { return ideologicalLeaderTraits; }
	[[nodiscard]] const auto& getGreatPowers() const { return greatPowers; }
	[[nodiscard]] const auto& getSupplyZones() const { return *supplyZones; }
	[[nodiscard]] const auto& getBuildings() const { return *buildings; }
	[[nodiscard]] const auto& getDecisions() const { return *theDecisions; }
	[[nodiscard]] auto& getEvents() { return *events; }
	[[nodiscard]] const auto& getEvents() const { return *events; }
	[[nodiscard]] const auto& getOnActions() const { return *onActions; }
	[[nodiscard]] const auto& getIntelligenceAgencies() const { return intelligenceAgencies; }
	[[nodiscard]] const auto& getOperativeNames() const { return *operativeNames; }
	[[nodiscard]] const auto& getOperations() const { return *operations; }
	[[nodiscard]] const auto& getPeaces() const { return *peaces; }
	[[nodiscard]] const auto& getIdeologies() const { return *ideologies; }
	[[nodiscard]] const auto& getTheIdeas() const { return *theIdeas; }
	[[nodiscard]] const auto& getOccupationLaws() const { return *occupationLaws; }
	[[nodiscard]] const auto& getDynamicModifiers() const { return dynamicModifiers; }
	[[nodiscard]] const auto& getScriptedEffects() const { return *scriptedEffects; }
	[[nodiscard]] const auto& getScriptedLocalisations() const { return scriptedLocalisations; }
	[[nodiscard]] const auto& getScriptedTriggers() const { return scriptedTriggers; }
	[[nodiscard]] const auto& getCountryCategories() const { return countryCategories; }
	[[nodiscard]] const auto& getGameRules() const { return *gameRules; }
	[[nodiscard]] const auto& getGenericFocusTree() const { return genericFocusTree; }
	[[nodiscard]] const auto& getLocalisation() const { return *hoi4Localisations; }
	[[nodiscard]] const auto& getSoundEffects() const { return soundEffects; }
	[[nodiscard]] const auto& getDate() const { return *theDate; }

	const std::map<int, HoI4::State>& getStates() const { return states->getStates(); }
	const std::map<int, int>& getProvinceToStateIDMap() const { return states->getProvinceToStateIDMap(); }
	std::vector<std::shared_ptr<Faction>> getFactions() const { return factions; }
	const auto& getMajorIdeologies() const { return ideologies->getMajorIdeologies(); }

	std::shared_ptr<HoI4::Country> findCountry(const std::string& countryTag) const;
	std::set<HoI4::Advisor> getActiveIdeologicalAdvisors() const;

	void setSphereLeaders();
	void processInfluence();
	void determineSpherelings();
	void calculateSpherelingAutonomy();

  private:
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void convertCountries(const Vic2::World& sourceWorld);
	void convertCountry(const std::string& oldTag,
		 const Vic2::Country& oldCountry,
		 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper);

	void importLeaderTraits();
	void importIdeologicalMinisters();

	void convertGovernments(const Vic2::World& sourceWorld, const Vic2::Localisations& vic2Localisations, bool debug);
	void convertCountryNames(const Vic2::Localisations& vic2Localisations);

	void convertParties(const Vic2::Localisations& vic2Localisations);

	void addNeutrality(bool debug);
	void addLeaders();
	void convertIdeologySupport();

	void convertIndustry(const Configuration& theConfiguration);
	void addStatesToCountries(const Mappers::ProvinceMapper& provinceMapper);
	void addDominions(Mappers::CountryMapper::Factory& countryMapperFactory);
	void transferPuppetsToDominions();
	void determineCoreStates();
	std::map<std::string, double> calculateFactoryWorkerRatios(const Configuration& theConfiguration);
	std::map<std::string, double> getIndustrialWorkersPerCountry();
	double getTotalWorldWorkers(const std::map<std::string, double>& industrialWorkersPerCountry);
	std::map<std::string, double> adjustWorkers(const std::map<std::string, double>& industrialWorkersPerCountry,
		 double totalWorldWorkers,
		 const Configuration& theConfiguration);
	double getWorldwideWorkerFactoryRatio(const std::map<std::string, double>& workersInCountries,
		 double totalWorldWorkers,
		 const Configuration& theConfiguration);
	void calculateIndustryInCountries();
	void reportIndustryLevels() const;

	void convertDiplomacy(const Vic2::World& sourceWorld);
	void convertAgreements(const Vic2::World& sourceWorld);

	void convertTechs();

	void convertMilitaries(const ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertArmies(const militaryMappings& localMilitaryMappings,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertNavies(const UnitMappings& unitMap,
		 const MtgUnitMappings& mtgUnitMap,
		 const ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper);
	void convertAirforces(const UnitMappings& unitMap);

	void determineGreatPowers(const Vic2::World& sourceWorld);

	void setupNavalTreaty();

	void createFactions(const Configuration& theConfiguration);
	void logFactionMember(std::ofstream& factionsLog, std::shared_ptr<HoI4::Country> member) const;
	std::optional<std::string> returnSphereLeader(std::shared_ptr<HoI4::Country> possibleSphereling) const;
	bool governmentsAllowFaction(const std::string& leaderGovernment, const std::string& allyGovernment) const;

	void addFocusTrees();
	void adjustResearchFocuses();

	void addCountryElectionEvents(const std::set<std::string>& theMajorIdeologies,
		 const Vic2::Localisations& vic2Localisations);

	std::vector<std::string> getStrongestNavyGps();

	std::set<std::string> getSouthAsianCountries() const;

	std::pair<std::string, std::shared_ptr<Country>> getDominion(const std::string& ownerTag,
		 const Country& owner,
		 const std::string& region,
		 std::map<std::string, std::shared_ptr<Country>>& countries,
		 Mappers::CountryMapper::Factory& countryMapperFactory,
		 const Regions& regions,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names,
		 Localisation& hoi4Localisations);

	bool dominionIsReleasable(const Country& dominion, const Country& overlord);

	// vector<int> getPortLocationCandidates(const vector<int>& locationCandidates, const HoI4AdjacencyMapping&
	// HoI4AdjacencyMap);

	std::optional<std::string> humanCountry;

	std::unique_ptr<Names> names;
	std::unique_ptr<Mappers::GraphicsMapper> graphicsMapper;
	std::unique_ptr<Mappers::GovernmentMapper> governmentMapper;
	std::unique_ptr<Mappers::IdeologyMapper> ideologyMapper;
	std::unique_ptr<Mappers::CountryMapper> countryMap;
	std::unique_ptr<Mappers::CountryNameMapper> countryNameMapper;
	std::unique_ptr<date> theDate;

	std::unique_ptr<States> states;

	HoI4::SupplyZones* supplyZones = nullptr;
	std::unique_ptr<StrategicRegions> strategicRegions;
	Buildings* buildings = nullptr;

	std::map<std::string, std::shared_ptr<HoI4::Country>> countries;
	std::map<std::string, std::shared_ptr<HoI4::Country>> landedCountries;
	std::vector<std::shared_ptr<HoI4::Country>> greatPowers;

	std::unique_ptr<Ideologies> ideologies;
	std::map<std::string, std::vector<std::string>> ideologicalLeaderTraits;
	std::map<std::string, HoI4::Advisor> ideologicalAdvisors;
	std::unique_ptr<HoI4::Ideas> theIdeas;
	std::unique_ptr<OccupationLaws> occupationLaws;

	std::vector<std::shared_ptr<Faction>> factions;
	std::unique_ptr<HoI4::decisions> theDecisions;
	std::unique_ptr<HoI4::AiPeaces> peaces;
	std::unique_ptr<HoI4::Events> events;
	std::unique_ptr<HoI4::OnActions> onActions;

	std::unique_ptr<IntelligenceAgencies> intelligenceAgencies;
	std::unique_ptr<OperativeNames> operativeNames;
	std::unique_ptr<Operations> operations;

	std::unique_ptr<allMilitaryMappings> theMilitaryMappings;

	CoastalProvinces theCoastalProvinces;
	std::unique_ptr<MapData> theMapData;

	std::unique_ptr<ScriptedEffects> scriptedEffects;

	std::unique_ptr<ScriptedLocalisations> scriptedLocalisations;
	ScriptedTriggers scriptedTriggers;
	std::map<std::string, TagsAndExtras> countryCategories;

	std::unique_ptr<GameRules> gameRules;
	DynamicModifiers dynamicModifiers;

	HoI4FocusTree genericFocusTree;

	std::unique_ptr<Localisation> hoi4Localisations;

	std::vector<SoundEffect> soundEffects;

	std::vector<std::string> strongestGpNavies;

	std::unique_ptr<Regions> theRegions;
	std::map<std::pair<std::string, std::string>, std::string> dominions;
};

} // namespace HoI4



#endif // HOI4_WORLD_H_