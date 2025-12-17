#ifndef HOI4_WORLD_H_
#define HOI4_WORLD_H_



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Countries/UnionCountry.h"
#include "src/HOI4World/CountryCategories/CountryCategories.h"
#include "src/HOI4World/Decisions/Decisions.h"
#include "src/HOI4World/Events/Events.h"
#include "src/HOI4World/Factions/FactionGoals.h"
#include "src/HOI4World/FocusTrees/AdjustedBranches.h"
#include "src/HOI4World/GameRules/GameRules.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/HoI4Localisation.h"
#include "src/HOI4World/Ideas/Ideas.h"
#include "src/HOI4World/Ideologies/Ideologies.h"
#include "src/HOI4World/Ideologies/Ideology.h"
#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgencies.h"
#include "src/HOI4World/Landmarks/LandmarkBuildings.h"
#include "src/HOI4World/Leaders/Advisor.h"
#include "src/HOI4World/Localisations/ArticleRules/ArticleRules.h"
#include "src/HOI4World/Map/AdjacencyRules.h"
#include "src/HOI4World/Map/Buildings.h"
#include "src/HOI4World/Map/CoastalProvinces.h"
#include "src/HOI4World/Map/Railway.h"
#include "src/HOI4World/Map/Railways.h"
#include "src/HOI4World/Map/StrategicRegion.h"
#include "src/HOI4World/Map/StrategicRegions.h"
#include "src/HOI4World/Map/SupplyZones.h"
#include "src/HOI4World/Military/DivisionTemplate.h"
#include "src/HOI4World/MilitaryMappings/AllMilitaryMappings.h"
#include "src/HOI4World/MilitaryMappings/HoI4UnitType.h"
#include "src/HOI4World/MilitaryMappings/UnitMappings.h"
#include "src/HOI4World/Modifiers/DynamicModifiers.h"
#include "src/HOI4World/Modifiers/Modifier.h"
#include "src/HOI4World/Names/Names.h"
#include "src/HOI4World/OccupationLaws/OccupationLawsFactory.h"
#include "src/HOI4World/OnActions/OnActions.h"
#include "src/HOI4World/Operations/Operations.h"
#include "src/HOI4World/OperativeNames/OperativeNames.h"
#include "src/HOI4World/Scorers/ScorersFactory.h"
#include "src/HOI4World/ScriptedEffects/ScriptedEffects.h"
#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisations.h"
#include "src/HOI4World/ScriptedTriggers/ScriptedTriggers.h"
#include "src/HOI4World/Sounds/SoundEffect.h"
#include "src/HOI4World/States/DefaultState.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "src/Mappers/CasusBelli/CasusBellis.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/CountryName/CountryNameMapper.h"
#include "src/Mappers/FactionName/FactionNameMapperFactory.h"
#include "src/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "src/Mappers/Government/GovernmentMapper.h"
#include "src/Mappers/Graphics/GraphicsMapper.h"
#include "src/Mappers/Ideology/IdeologyMapper.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Mappers/Technology/TechMapper.h"
#include "src/Maps/MapData.h"
#include "src/Maps/ProvinceDefinitions.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/World/World.h"
#include <map>
#include <memory>
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
	[[nodiscard]] const auto& GetUnionCountries() const { return union_countries_; }
	[[nodiscard]] const auto& getMilitaryMappings() const { return *theMilitaryMappings; }
	[[nodiscard]] auto& getGraphicsMapper() { return *graphicsMapper; }
	[[nodiscard]] auto& getFactionNameMapper() { return *factionNameMapper; }
	[[nodiscard]] const auto& getIdeologicalLeaderTraits() const { return ideologicalLeaderTraits; }
	[[nodiscard]] const auto& getGreatPowers() const { return greatPowers; }
	[[nodiscard]] const auto& getSupplyZones() const { return *supplyZones; }
	[[nodiscard]] const auto& getBuildings() const { return *buildings; }
	[[nodiscard]] const auto& getLandmarkBuildings() const { return *landmarkBuildings; }
	[[nodiscard]] const auto& getSupplyNodes() const { return supplyNodes_; }
	[[nodiscard]] const auto& getRailways() const { return railways_; }
	[[nodiscard]] const auto& getDecisions() const { return *theDecisions; }
	[[nodiscard]] auto& getEvents() { return *events; }
	[[nodiscard]] const auto& getEvents() const { return *events; }
	[[nodiscard]] const auto& getOnActions() const { return *onActions; }
	[[nodiscard]] const auto& getIntelligenceAgencies() const { return intelligenceAgencies; }
	[[nodiscard]] const auto& getOperativeNames() const { return *operativeNames; }
	[[nodiscard]] const auto& getOperations() const { return *operations; }
	[[nodiscard]] const auto& getIdeologies() const { return *ideologies; }
	[[nodiscard]] const auto& getTheIdeas() const { return *theIdeas; }
	[[nodiscard]] const auto& getOccupationLaws() const { return *occupationLaws; }
	[[nodiscard]] const auto& getDynamicModifiers() const { return dynamicModifiers; }
	[[nodiscard]] const auto& getScorers() const { return *scorers; }
	[[nodiscard]] const auto& getCustomizedScorers() const { return scorers->getCustomizedScorers(); }
	[[nodiscard]] const auto& getScriptedEffects() const { return *scriptedEffects; }
	[[nodiscard]] const auto& getScriptedLocalisations() const { return scriptedLocalisations; }
	[[nodiscard]] const auto& getScriptedTriggers() const { return scriptedTriggers; }
	[[nodiscard]] const auto& getCountryCategories() const { return countryCategories; }
	[[nodiscard]] const auto& getGameRules() const { return *gameRules; }
	[[nodiscard]] const auto& getGenericFocusTree() const { return genericFocusTree; }
	[[nodiscard]] const auto& getLocalisation() const { return *hoi4Localisations; }
	[[nodiscard]] const auto& getSoundEffects() const { return soundEffects; }
	[[nodiscard]] const auto& getDate() const { return *theDate; }
	[[nodiscard]] const auto& getAdjustedFocusBranches() const { return adjustedBranches->getAddedBranches(); }
	[[nodiscard]] const std::map<std::string, std::string>& GetIdeologicalCostModifiers() const
	{
		return ideological_cost_modifiers_;
	}
	[[nodiscard]] const std::map<std::string, std::string>& GetIdeologicalAiPeace() const
	{
		return ideological_ai_peace_;
	}
	[[nodiscard]] const std::map<std::string, std::string>& GetUnitMedals() const { return ideological_unit_medals_; }

	[[nodiscard]] const std::vector<std::string>& GetDynamicAiPeace() const { return dynamic_ai_peace_; }
	[[nodiscard]] const auto& getAdjacencyRules() const { return adjacencyRules->getRules(); }

	const std::map<int, HoI4::State>& getStates() const { return states->getStates(); }
	const std::map<int, int>& getProvinceToStateIDMap() const { return states->getProvinceToStateIDMap(); }
	std::vector<std::shared_ptr<Faction>> getFactions() const { return factions; }
	const auto& getIdeologicalFactionGoals() const { return factionGoals->getIdeologicalGoals(); }
	const auto& getManifestsVariables() const { return factionGoals->getVariables(); }
	const auto& getMajorIdeologies() const { return ideologies->getMajorIdeologies(); }

	std::shared_ptr<HoI4::Country> findCountry(const std::string& countryTag) const;
	std::set<Advisor> getActiveIdeologicalAdvisors() const;

  private:
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void convertCountries(const Vic2::World& sourceWorld,
		 const Mappers::ProvinceMapper& provinceMapper,
		 Character::Factory& characterFactory);
	void convertCountry(const std::string& oldTag,
		 const Vic2::Country& oldCountry,
		 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
		 const Mappers::ProvinceMapper& provinceMapper,
		 Character::Factory& characterFactory);

	void importLeaderTraits();
	void importIdeologicalMinisters();

	void convertGovernments(const Vic2::World& sourceWorld, const Vic2::Localisations& vic2Localisations, bool debug);
	void convertCountryNames(const Vic2::Localisations& vic2Localisations);

	void convertParties(const Vic2::Localisations& vic2Localisations);

	void addNeutrality(bool debug);
	void addLeaders(Character::Factory& characterFactory);
	void importCharacters(Character::Factory& characterFactory);
	void convertIdeologySupport();

	void convertIndustry(const Configuration& theConfiguration);
	void convertInfrastructure();
	void addStatesToCountries(const Mappers::ProvinceMapper& provinceMapper);
	void CalculateStateAvrgPopPerProv();
	void addDominions(Mappers::CountryMapper::Factory& countryMapperFactory);
	void transferPuppetsToDominions();
	void addUnrecognizedNations(Mappers::CountryMapper::Factory& countryMapperFactory,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Vic2::World& sourceWorld);
	void determineCoresAndClaims();
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

	void setTrainMultipliers();

	void convertDiplomacy(const Vic2::World& sourceWorld);
	void convertStrategies(const Vic2::World& sourceWorld,
		 const States& states,
		 const Mappers::ProvinceMapper& provinceMapper);
	void convertWars(const Vic2::World& sourceWorld, const Mappers::ProvinceMapper& provinceMapper);

	void convertTechs();

	void convertMilitaries(const Maps::ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertArmies(const militaryMappings& localMilitaryMappings,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertNavies(const UnitMappings& unitMap,
		 const MtgUnitMappings& mtgUnitMap,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper);
	void convertAirforces(const UnitMappings& unitMap);

	void determineGreatPowers(const Vic2::World& sourceWorld);

	void setupNavalTreaty();

	void createFactions(const Configuration& theConfiguration);
	void logFactionMember(std::ofstream& factionsLog, const Country& member) const;
	std::optional<std::string> returnSphereLeader(std::shared_ptr<HoI4::Country> possibleSphereling) const;
	bool governmentsAllowFaction(const std::string& leaderGovernment, const std::string& allyGovernment) const;

	void addFocusTrees(bool debug);
	void adjustResearchFocuses();

	void addCountryElectionEvents(const std::set<std::string>& theMajorIdeologies,
		 const Vic2::Localisations& vic2Localisations,
		 bool debug);

	std::vector<std::string> getStrongestNavyGps();

	std::set<std::string> getSouthAsianCountries() const;

	std::shared_ptr<Country> getDominion(const std::shared_ptr<Country>& owner,
		 const std::set<int>& area,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names);
	std::string getBestRegion(const std::set<int>& area, const std::string& ownerTag);
	std::set<int> getAreaStates(const std::set<int>& area,
		 const std::shared_ptr<Country>& country,
		 const std::vector<std::set<int>>& areas,
		 const std::string& ownerRegion);
	std::vector<std::pair<std::string, int>> sortAreaRegions(const std::map<std::string, int>& regions);
	std::shared_ptr<Country> getUnrecognizedNation(const std::string& region,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names);

	bool dominionIsReleasable(const Country& dominion);

	void recordUnbuiltCanals(const Vic2::World& sourceWorld);

	std::optional<std::string> humanCountry;

	std::unique_ptr<Names> names;
	std::unique_ptr<Mappers::GraphicsMapper> graphicsMapper;
	std::unique_ptr<Mappers::GovernmentMapper> governmentMapper;
	std::unique_ptr<Mappers::IdeologyMapper> ideologyMapper;
	std::unique_ptr<Mappers::CountryMapper> countryMap;
	std::unique_ptr<Mappers::CountryNameMapper> countryNameMapper;
	std::unique_ptr<Mappers::CasusBellis> casusBellis;
	std::unique_ptr<Mappers::FactionNameMapper> factionNameMapper;
	Mappers::LandmarksMapper landmarksMapper;
	std::unique_ptr<date> theDate;

	std::unique_ptr<States> states;

	HoI4::SupplyZones* supplyZones = nullptr;
	std::unique_ptr<StrategicRegions> strategicRegions;
	Buildings* buildings = nullptr;
	LandmarkBuildings* landmarkBuildings = nullptr;
	std::unique_ptr<AdjacencyRules> adjacencyRules;
	std::set<int> supplyNodes_;
	std::unique_ptr<Railways> railways_;

	std::map<std::string, std::shared_ptr<HoI4::Country>> countries;
	std::map<std::string, std::shared_ptr<HoI4::Country>> landedCountries;
	std::vector<std::shared_ptr<HoI4::Country>> greatPowers;
	std::vector<HoI4::UnionCountry> union_countries_;

	std::unique_ptr<Ideologies> ideologies;
	std::map<std::string, std::vector<std::string>> ideologicalLeaderTraits;
	std::map<std::string, HoI4::Advisor> ideologicalAdvisors;
	std::unique_ptr<HoI4::Ideas> theIdeas;
	std::unique_ptr<OccupationLaws> occupationLaws;

	std::vector<std::shared_ptr<Faction>> factions;
	std::unique_ptr<HoI4::FactionGoals> factionGoals;
	std::unique_ptr<HoI4::decisions> theDecisions;
	std::unique_ptr<HoI4::Events> events;
	std::unique_ptr<HoI4::OnActions> onActions;

	std::unique_ptr<IntelligenceAgencies> intelligenceAgencies;
	std::unique_ptr<OperativeNames> operativeNames;
	std::unique_ptr<Operations> operations;

	std::unique_ptr<allMilitaryMappings> theMilitaryMappings;

	CoastalProvinces theCoastalProvinces;
	std::unique_ptr<Maps::ProvinceDefinitions> provinceDefinitions;
	std::unique_ptr<Maps::MapData> theMapData;

	std::unique_ptr<ScriptedEffects> scriptedEffects;
	std::unique_ptr<Scorers> scorers;

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
	std::map<std::pair<std::string, std::string>, std::shared_ptr<Country>> dominions;
	std::map<std::string, std::shared_ptr<Country>> unrecognizedNations;
	std::unique_ptr<AdjustedBranches> adjustedBranches;

	std::map<std::string, std::string> ideological_cost_modifiers_;
	std::map<std::string, std::string> ideological_ai_peace_;
	std::map<std::string, std::string> ideological_unit_medals_;

	std::vector<std::string> dynamic_ai_peace_;
};

} // namespace HoI4



#endif // HOI4_WORLD_H_