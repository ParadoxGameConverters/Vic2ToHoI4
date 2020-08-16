#ifndef HOI4_WORLD_H_
#define HOI4_WORLD_H_



#include "../Mappers/CountryMapping.h"
#include "../Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Mappers/GovernmentMapper.h"
#include "../Mappers/GraphicsMapper.h"
#include "Decisions/Decisions.h"
#include "Diplomacy/AIPeaces.h"
#include "GameRules/GameRules.h"
#include "HoI4Localisation.h"
#include "Ideas/Ideas.h"
#include "Ideologies/Ideologies.h"
#include "IntelligenceAgencies/IntelligenceAgencies.h"
#include "Leaders/Advisor.h"
#include "Localisations/ArticleRules/ArticleRules.h"
#include "Map/CoastalProvinces.h"
#include "Map/MapData.h"
#include "Map/StrategicRegions.h"
#include "MilitaryMappings/AllMilitaryMappings.h"
#include "MilitaryMappings/UnitMappings.h"
#include "Names/Names.h"
#include "OccupationLaws/OccupationLawsFactory.h"
#include "OnActions.h"
#include "Operations/Operations.h"
#include "OperativeNames/OperativeNames.h"
#include "Parser.h"
#include "ScriptedLocalisations/ScriptedLocalisations.h"
#include "ScriptedTriggers/ScriptedTriggers.h"
#include "States/HoI4States.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



class HoI4Ideology;



namespace mappers
{

class ProvinceMapper;
class techMapper;

} // namespace mappers


namespace Vic2
{

class Country;
class Faction;
class World;

} // namespace Vic2



namespace HoI4
{

class Advisor;
class Buildings;
class Country;
class DefaultState;
class DivisionTemplateType;
class Events;
class ProvinceDefinitions;
class State;
class States;
class StrategicRegion;
class SupplyZones;
class HoI4UnitType;



class World: commonItems::parser
{
  public:
	explicit World(const Vic2::World* sourceWorld,
		 const mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	~World() = default;

	[[nodiscard]] auto& getNames() { return names; }
	[[nodiscard]] const auto& getNames() const { return *names; }
	[[nodiscard]] const auto& getTheStates() const { return *states; }
	[[nodiscard]] const auto& getStrategicRegions() const { return *strategicRegions; }
	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getMilitaryMappings() const { return *theMilitaryMappings; }
	[[nodiscard]] auto& getGraphics() { return theGraphics; }
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
	[[nodiscard]] const auto& getScriptedLocalisations() const { return scriptedLocalisations; }
	[[nodiscard]] const auto& getScriptedTriggers() const { return scriptedTriggers; }
	[[nodiscard]] const auto& getGameRules() const { return *gameRules; }
	[[nodiscard]] const auto& getGenericFocusTree() const { return genericFocusTree; }
	[[nodiscard]] const auto& getLocalisation() const { return *hoi4Localisations; }

	std::map<int, HoI4::State> getStates() const { return states->getStates(); }
	const std::map<int, int>& getProvinceToStateIDMap() const { return states->getProvinceToStateIDMap(); }
	std::vector<std::shared_ptr<Faction>> getFactions() const { return factions; }
	const auto& getMajorIdeologies() const { return ideologies->getMajorIdeologies(); }

	std::shared_ptr<HoI4::Country> findCountry(const std::string& countryTag);
	std::set<HoI4::Advisor> getActiveIdeologicalAdvisors() const;

	void setSphereLeaders();
	void processInfluence();
	void determineSpherelings();
	void calculateSpherelingAutonomy();

  private:
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void convertCountries(const Vic2::Localisations& vic2Localisations);
	void convertCountry(std::pair<std::string, Vic2::Country*> country,
		 const mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
		 const Vic2::Localisations& vic2Localisations,
		 const ArticleRules& articleRules);

	void importLeaderTraits();
	void importIdeologicalMinisters();

	void convertGovernments(const Vic2::Localisations& vic2Localisations, bool debug);

	void convertParties(const Vic2::Localisations& vic2Localisations);

	void addNeutrality(bool debug);
	void addLeaders();
	void convertIdeologySupport();

	void convertIndustry(const Configuration& theConfiguration);
	void addStatesToCountries(const mappers::ProvinceMapper& provinceMapper);
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

	void convertDiplomacy();
	void convertAgreements();

	void convertTechs();

	void convertMilitaries(const ProvinceDefinitions& provinceDefinitions,
		 const mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertArmies(const militaryMappings& localMilitaryMappings,
		 const mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertNavies(const UnitMappings& unitMap,
		 const MtgUnitMappings& mtgUnitMap,
		 const ProvinceDefinitions& provinceDefinitions,
		 const mappers::ProvinceMapper& provinceMapper);
	void convertAirforces(const UnitMappings& unitMap);

	void determineGreatPowers();

	void setupNavalTreaty();

	double getStrongestCountryStrength() const;

	void createFactions(const Configuration& theConfiguration);
	void logFactionMember(std::ofstream& factionsLog, std::shared_ptr<HoI4::Country> member) const;
	std::optional<std::string> returnSphereLeader(std::shared_ptr<HoI4::Country> possibleSphereling) const;
	bool governmentsAllowFaction(const std::string& leaderGovernment, const std::string& allyGovernment) const;

	void addFocusTrees();
	void adjustResearchFocuses();

	void addCountryElectionEvents(const std::set<std::string>& theMajorIdeologies,
		 const Vic2::Localisations& vic2Localisations);

	std::optional<std::pair<std::string, std::string>> getStrongestNavyGps();

	// vector<int> getPortLocationCandidates(const vector<int>& locationCandidates, const HoI4AdjacencyMapping&
	// HoI4AdjacencyMap);

	std::unique_ptr<Names> names;
	graphicsMapper theGraphics;
	governmentMapper governmentMap;
	CountryMapper countryMap;

	const Vic2::World* sourceWorld = nullptr;

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

	ScriptedLocalisations scriptedLocalisations;
	ScriptedTriggers scriptedTriggers;

	std::unique_ptr<GameRules> gameRules;

	HoI4FocusTree genericFocusTree;

	std::unique_ptr<Localisation> hoi4Localisations;
};

} // namespace HoI4



#endif // HOI4_WORLD_H_