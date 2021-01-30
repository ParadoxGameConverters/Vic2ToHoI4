#ifndef HOI4_WAR_CREATOR_H
#define HOI4_WAR_CREATOR_H



#include "HOI4World/HoI4Country.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/HoI4World.h"
#include "HOI4World/Map/MapData.h"
#include "HOI4World/ProvinceDefinitions.h"
#include "V2World/World/World.h"
#include <fstream>
#include <map>
#include <optional>
#include <string>
using namespace std;


const int maxGCWars = 1;



class HoI4WarCreator
{
  public:
	explicit HoI4WarCreator(HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);

  private:
	HoI4WarCreator(const HoI4WarCreator&) = delete;
	HoI4WarCreator& operator=(const HoI4WarCreator&) = delete;

	void determineProvinceOwners();
	void addAllTargetsToWorldTargetMap();
	void addTargetsToWorldTargetMap(shared_ptr<HoI4::Country> country);
	map<double, shared_ptr<HoI4::Country>> getDistancesToGreatPowers(shared_ptr<HoI4::Country> country);
	double calculateWorldStrength(ofstream& AILog, const Configuration& theConfiguration) const;
	void generateMajorWars(ofstream& AILog,
		 set<shared_ptr<HoI4::Faction>>& factionsAtWar,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	double calculatePercentOfWorldAtWar(ofstream& AILog,
		 const set<shared_ptr<HoI4::Faction>>& factionsAtWar,
		 double worldStrength,
		 const Configuration& theConfiguration) const;
	void generateReconquestWars(std::ofstream& AILog,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	void generateAdditionalWars(ofstream& AILog,
		 set<shared_ptr<HoI4::Faction>>& factionsAtWar,
		 double worldStrength,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	bool isImportantCountry(shared_ptr<HoI4::Country> country);

	vector<shared_ptr<HoI4::Faction>> fascistWarMaker(shared_ptr<HoI4::Country> country,
		 ofstream& AILog,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	vector<shared_ptr<HoI4::Faction>> communistWarCreator(shared_ptr<HoI4::Country> country,
		 const std::set<std::string>& majorIdeologies,
		 ofstream& AILog,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations);
	vector<shared_ptr<HoI4::Faction>> democracyWarCreator(shared_ptr<HoI4::Country> country,
		 HoI4::Localisation& hoi4Localisations);
	vector<shared_ptr<HoI4::Faction>> absolutistWarCreator(shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations);
	vector<shared_ptr<HoI4::Faction>> neighborWarCreator(shared_ptr<HoI4::Country> country,
		 ofstream& AILog,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	vector<shared_ptr<HoI4::Faction>> radicalWarCreator(shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations);

	vector<shared_ptr<HoI4::Country>> findEvilCountries() const;

	set<int> findBorderState(shared_ptr<HoI4::Country> country,
		 shared_ptr<HoI4::Country> neighbor,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	vector<int> sortStatesByCapitalDistance(const std::set<int>& stateList,
		 std::shared_ptr<HoI4::Country> country,
		 const HoI4::World* world);
	vector<shared_ptr<HoI4::Country>> findWeakNeighbors(shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	map<string, shared_ptr<HoI4::Country>> findCloseNeighbors(shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<string, shared_ptr<HoI4::Country>> findCountriesWithin(int distancePx, shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);
	vector<shared_ptr<HoI4::Country>> findWeakColonies(shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	map<string, shared_ptr<HoI4::Country>> findFarNeighbors(shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	vector<shared_ptr<HoI4::Country>> getGreatPowerTargets(shared_ptr<HoI4::Country> country);
	map<double, shared_ptr<HoI4::Country>> getGPsByDistance(shared_ptr<HoI4::Country> country);
	vector<shared_ptr<HoI4::Faction>> addGreatPowerWars(shared_ptr<HoI4::Country> country,
		 HoI4FocusTree& FocusTree,
		 vector<shared_ptr<HoI4::Country>>& greatPowerTargets,
		 HoI4::Localisation& hoi4Localisations);
	void addTradeEvents(shared_ptr<HoI4::Country> country, const vector<shared_ptr<HoI4::Country>>& greatPowerTargets);

	void setSphereLeaders(const Vic2::World* sourceWorld);
	double GetFactionStrength(const shared_ptr<HoI4::Faction>& Faction, int years) const;
	string HowToTakeLand(shared_ptr<HoI4::Country> TargetCountry,
		 shared_ptr<HoI4::Country> AttackingCountry,
		 double time);
	vector<shared_ptr<HoI4::Country>> GetMorePossibleAllies(const shared_ptr<HoI4::Country>& CountryThatWantsAllies);
	optional<double> getDistanceBetweenCountries(shared_ptr<HoI4::Country> Country1, shared_ptr<HoI4::Country> Country2);
	optional<double> getDistanceBetweenCapitals(shared_ptr<HoI4::Country> Country1, shared_ptr<HoI4::Country> Country2);
	bool bothCountriesHaveCapitals(shared_ptr<HoI4::Country> Country1, shared_ptr<HoI4::Country> Country2) const;
	pair<int, int> getCapitalPosition(shared_ptr<HoI4::Country> country);
	pair<int, int> getProvincePosition(int provinceNum);
	void establishProvincePositions();
	void processPositionLine(const string& line);
	vector<string> tokenizeLine(const string& line);
	void addProvincePosition(const vector<string>& tokenizedLine);
	double getDistanceBetweenPoints(pair<int, int> point1, pair<int, int> point2) const;
	double GetFactionStrengthWithDistance(std::shared_ptr<HoI4::Country> HomeCountry,
		 const std::vector<std::shared_ptr<HoI4::Country>>& Faction,
		 double time);
	shared_ptr<HoI4::Faction> findFaction(shared_ptr<HoI4::Country> checkingCountry);

	map<string, shared_ptr<HoI4::Country>> getNeighbors(shared_ptr<HoI4::Country> checkingCountry,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> getImmediateNeighbors(
		 std::shared_ptr<HoI4::Country> checkingCountry,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	map<string, shared_ptr<HoI4::Country>> getNearbyCountries(shared_ptr<HoI4::Country> checkingCountry);


	HoI4FocusTree* genericFocusTree;
	HoI4::World* theWorld;

	vector<HoI4::Country*> AggressorFactions;
	map<shared_ptr<HoI4::Country>, vector<shared_ptr<HoI4::Country>>> WorldTargetMap;
	map<int, pair<int, int>> provincePositions;

	map<int, string> provinceToOwnerMap;
};



#endif // HOI4_WAR_CREATOR_H