#ifndef HoI4WORLD_H_
#define HoI4WORLD_H_



#include "AIPeaces.h"
#include "CoastalProvinces.h"
#include "Decisions/Decisions.h"
#include "Ideas.h"
#include "Leaders/Advisor.h"
#include "MapData.h"
#include "MilitaryMappings/AllMilitaryMappings.h"
#include "MilitaryMappings/UnitMappings.h"
#include "Names.h"
#include "OnActions.h"
#include "ScriptedLocalisations/ScriptedLocalisations.h"
#include "States/HoI4States.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/GovernmentMapper.h"
#include "../Mappers/GraphicsMapper.h"
#include "../Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "newParser.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



class HoI4Diplomacy;
class HoI4Faction;
class HoI4Ideology;
class HoI4Province;
class HoI4StrategicRegion;


namespace mappers
{

class techMapper;

}

namespace Vic2
{

class Country;
class World;

}



namespace HoI4
{

class Advisor;
class Buildings;
class Country;
class DefaultState;
class DivisionTemplateType;
class Events;
class State;
class States;
class SupplyZones;
class HoI4UnitType;
struct advisorCompare;


class World: commonItems::parser
{
	public:
		explicit World(const Vic2::World* sourceWorld);
		~World() = default;

		void output();

		std::map<std::string, std::shared_ptr<HoI4::Country>> getCountries()	const { return countries; }
		std::vector<std::shared_ptr<HoI4::Country>> getGreatPowers() const { return greatPowers; }
		std::map<int, HoI4::State> getStates() const { return states->getStates(); }
		const std::map<int, int>& getProvinceToStateIDMap() const { return states->getProvinceToStateIDMap(); }
		std::vector<std::shared_ptr<HoI4Faction>> getFactions() const { return factions; }
		HoI4::Events* getEvents() const { return events; }
		std::set<std::string> getMajorIdeologies() const { return majorIdeologies; }

		std::shared_ptr<HoI4::Country> findCountry(const std::string& countryTag);

	private:
		World(const World&) = delete;
		World& operator=(const World&) = delete;

		void convertCountries();
		void convertCountry(
			std::pair<std::string, Vic2::Country*> country,
			const mappers::FlagsToIdeasMapper& flagsToIdeasMapper
		);

		void importIdeologies();
		void importLeaderTraits();
		void importIdeologicalMinisters();

		void convertGovernments();

		void convertParties();

		void identifyMajorIdeologies();
		void addNeutrality();
		void convertIdeologySupport();

		void convertIndustry();
		void addStatesToCountries();
		std::map<std::string, double> calculateFactoryWorkerRatios();
		std::map<std::string, double> getIndustrialWorkersPerCountry();
		double getTotalWorldWorkers(const std::map<std::string, double>& industrialWorkersPerCountry);
		std::map<std::string, double> adjustWorkers(
			const std::map<std::string, double>& industrialWorkersPerCountry,
			double totalWorldWorkers
		);
		double getWorldwideWorkerFactoryRatio(
			const std::map<std::string, double>& workersInCountries,
			double totalWorldWorkers
		);
		void calculateIndustryInCountries();
		void reportIndustryLevels();
		void reportCountryIndustry();
		void reportDefaultIndustry();
		std::pair<std::string, std::array<int, 3>> getDefaultStateIndustry(const HoI4::DefaultState& state);
		void reportDefaultIndustry(const std::map<std::string, std::array<int, 3>>& countryIndustry);

		void convertStrategicRegions();
		std::map<int, int> importStrategicRegions();
		std::map<int, int> determineUsedRegions(
			const HoI4::State& state,
			std::map<int, int>& provinceToStrategicRegionMap
		);
		std::optional<int> determineMostUsedRegion(const std::map<int, int>& usedRegions) const;
		void addProvincesToRegion(const HoI4::State& state, int regionNum);
		void addLeftoverProvincesToRegions(const std::map<int, int>& provinceToStrategicRegionMap);

		void convertDiplomacy();
		void convertAgreements();
		void convertRelations();

		void convertTechs();

		void convertMilitaries();
		void convertArmies(const militaryMappings& localMilitaryMappings);
		void convertNavies(
			const UnitMappings& unitMap,
			const MtgUnitMappings& mtgUnitMap);
		void convertAirforces(const UnitMappings& unitMap);

		void determineGreatPowers();

		void setupNavalTreaty();

		double getStrongestCountryStrength() const;

		void createFactions();
		void logFactionMember(std::ofstream& factionsLog, std::shared_ptr<HoI4::Country> member) const;
		std::optional<std::string> returnSphereLeader(std::shared_ptr<HoI4::Country> possibleSphereling) const;
		bool governmentsAllowFaction(const std::string& leaderGovernment, const std::string& allyGovernment) const;

		void addFocusTrees();
		void adjustResearchFocuses();

		void addCountryElectionEvents(const std::set<std::string>& theMajorIdeologies);

		void outputCommonCountries() const;
		void outputColorsfile() const;
		void outputNames() const;
		void outputUnitNames() const;
		void outputMap() const;
		void outputGenericFocusTree() const;
		void outputCountries();
		std::set<HoI4::Advisor, HoI4::advisorCompare> getActiveIdeologicalAdvisors() const;
		void outputRelations() const;
		void outputIdeologies() const;
		void outputLeaderTraits() const;
		void outputIdeas() const;
		void outputScriptedTriggers() const;
		void outputBookmarks() const;

		std::optional<std::pair<std::string, std::string>> getStrongestNavyGps();

		/*vector<int> getPortLocationCandidates(const vector<int>& locationCandidates, const HoI4AdjacencyMapping& HoI4AdjacencyMap);
		vector<int> getPortProvinces(const vector<int>& locationCandidates);
		int getAirLocation(HoI4Province* locationProvince, const HoI4AdjacencyMapping& HoI4AdjacencyMap, string owner);*/

		HoI4::namesMapper theNames;
		graphicsMapper theGraphics;
		governmentMapper governmentMap;
		CountryMapper countryMap;

		const Vic2::World* sourceWorld = nullptr;

		std::unique_ptr<States> states;
		//map<int, HoI4Province*> provinces;

		HoI4::SupplyZones* supplyZones = nullptr;
		std::map<int, HoI4StrategicRegion*> strategicRegions;
		Buildings* buildings = nullptr;

		std::map<std::string, std::shared_ptr<HoI4::Country>> countries;
		std::map<std::string, std::shared_ptr<HoI4::Country>> landedCountries;
		std::vector<std::shared_ptr<HoI4::Country>> greatPowers;

		std::map<std::string, HoI4Ideology*> ideologies;
		std::set<std::string> majorIdeologies;
		std::map<std::string, std::vector<std::string>> ideologicalLeaderTraits;
		std::map<std::string, HoI4::Advisor> ideologicalAdvisors;
		std::unique_ptr<HoI4::Ideas> theIdeas;
		
		std::vector<std::shared_ptr<HoI4Faction>> factions;
		HoI4Diplomacy* diplomacy = nullptr;
		std::unique_ptr<HoI4::decisions> decisions;
		std::unique_ptr<HoI4::AIPeaces> peaces;
		HoI4::Events* events = nullptr;
		std::unique_ptr<HoI4::OnActions> onActions;

		std::unique_ptr<allMilitaryMappings> theMilitaryMappings;

		coastalProvinces theCoastalProvinces;
		MapData theMapData;

		ScriptedLocalisations scriptedLocalisations;
};

}



#endif // HoI4WORLD_H_
