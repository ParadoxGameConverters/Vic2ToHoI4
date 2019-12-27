#ifndef HoI4WORLD_H_
#define HoI4WORLD_H_



#include "Advisor.h"
#include "AIPeaces.h"
#include "CoastalProvinces.h"
#include "Decisions/Decisions.h"
#include "Ideas.h"
#include "OnActions.h"
#include "Names.h"
#include "MapData.h"
#include "MilitaryMappings/AllMilitaryMappings.h"
#include "MilitaryMappings/UnitMappings.h"
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
class HoI4States;
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
class SupplyZones;
class HoI4UnitType;
struct advisorCompare;


class World: commonItems::parser
{
	public:
		explicit World(const Vic2::World* sourceWorld);
		~World() = default;

		void output();

		map<string, shared_ptr<HoI4::Country>> getCountries()	const { return countries; }
		vector<shared_ptr<HoI4::Country>> getGreatPowers() const { return greatPowers; }
		map<int, HoI4::State> getStates() const { return states->getStates(); }
		const map<int, int>& getProvinceToStateIDMap() const { return states->getProvinceToStateIDMap(); }
		vector<shared_ptr<HoI4Faction>> getFactions() const { return factions; }
		HoI4::Events* getEvents() const { return events; }
		set<string> getMajorIdeologies() const { return majorIdeologies; }

		shared_ptr<HoI4::Country> findCountry(const string& countryTag);

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
		map<string, double> calculateFactoryWorkerRatios();
		map<string, double> getIndustrialWorkersPerCountry();
		double getTotalWorldWorkers(const map<string, double>& industrialWorkersPerCountry);
		map<string, double> adjustWorkers(const map<string, double>& industrialWorkersPerCountry, double totalWorldWorkers);
		double getWorldwideWorkerFactoryRatio(const map<string, double>& workersInCountries, double totalWorldWorkers);
		void calculateIndustryInCountries();
		void reportIndustryLevels();
		void reportCountryIndustry();
		void reportDefaultIndustry();
		std::pair<std::string, std::array<int, 3>> getDefaultStateIndustry(const HoI4::DefaultState& state);
		void reportDefaultIndustry(const map<string, array<int, 3>>& countryIndustry);

		void convertStrategicRegions();
		map<int, int> importStrategicRegions();
		map<int, int> determineUsedRegions(const HoI4::State& state, map<int, int>& provinceToStrategicRegionMap);
		optional<int> determineMostUsedRegion(const map<int, int>& usedRegions) const;
		void addProvincesToRegion(const HoI4::State& state, int regionNum);
		void addLeftoverProvincesToRegions(const map<int, int>& provinceToStrategicRegionMap);

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

		double getStrongestCountryStrength() const;

		void createFactions();
		void logFactionMember(ofstream& factionsLog, shared_ptr<HoI4::Country> member) const;
		optional<string> returnSphereLeader(shared_ptr<HoI4::Country> possibleSphereling) const;
		bool governmentsAllowFaction(const string& leaderGovernment, const string& allyGovernment) const;

		void addFocusTrees();
		void adjustResearchFocuses();

		void addCountryElectionEvents(const std::set<string>& theMajorIdeologies);

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

		HoI4States* states = nullptr;
		//map<int, HoI4Province*> provinces;

		HoI4::SupplyZones* supplyZones = nullptr;
		map<int, HoI4StrategicRegion*> strategicRegions;
		Buildings* buildings = nullptr;

		map<string, shared_ptr<HoI4::Country>> countries;
		map<string, shared_ptr<HoI4::Country>> landedCountries;
		vector<shared_ptr<HoI4::Country>> greatPowers;

		map<string, HoI4Ideology*> ideologies;
		std::set<std::string> majorIdeologies;
		std::map<std::string, vector<std::string>> ideologicalLeaderTraits;
		map<std::string, HoI4::Advisor> ideologicalAdvisors;
		std::unique_ptr<HoI4::Ideas> theIdeas;
		
		vector<shared_ptr<HoI4Faction>> factions;
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
