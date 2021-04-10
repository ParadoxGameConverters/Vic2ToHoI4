#ifndef HOI4_WAR_CREATOR_H
#define HOI4_WAR_CREATOR_H



#include "HOI4World/HoI4Country.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/HoI4World.h"
#include "HOI4World/Map/MapData.h"
#include "HOI4World/ProvinceDefinitions.h"
#include "MapUtils.h"
#include "V2World/World/World.h"
#include <fstream>
#include <map>
#include <optional>
#include <string>



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
	void addTargetsToWorldTargetMap(std::shared_ptr<HoI4::Country> country);
	std::map<double, std::shared_ptr<HoI4::Country>> getDistancesToGreatPowers(std::shared_ptr<HoI4::Country> country);
	double calculateWorldStrength(std::ofstream& AILog, const Configuration& theConfiguration) const;
	void generateMajorWars(std::ofstream& AILog,
		 std::set<std::shared_ptr<HoI4::Faction>>& factionsAtWar,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	double calculatePercentOfWorldAtWar(std::ofstream& AILog,
		 const std::set<std::shared_ptr<HoI4::Faction>>& factionsAtWar,
		 double worldStrength,
		 const Configuration& theConfiguration) const;
	void generateReconquestWars(std::ofstream& AILog,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	void generateAdditionalWars(std::ofstream& AILog,
		 std::set<std::shared_ptr<HoI4::Faction>>& factionsAtWar,
		 double worldStrength,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	bool isImportantCountry(std::shared_ptr<HoI4::Country> country);

	std::vector<std::shared_ptr<HoI4::Faction>> fascistWarMaker(std::shared_ptr<HoI4::Country> country,
		 std::ofstream& AILog,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	std::vector<std::shared_ptr<HoI4::Faction>> communistWarCreator(std::shared_ptr<HoI4::Country> country,
		 const std::set<std::string>& majorIdeologies,
		 std::ofstream& AILog,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations);
	std::vector<std::shared_ptr<HoI4::Faction>> democracyWarCreator(std::shared_ptr<HoI4::Country> country,
		 HoI4::Localisation& hoi4Localisations);
	std::vector<std::shared_ptr<HoI4::Faction>> absolutistWarCreator(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations);
	std::vector<std::shared_ptr<HoI4::Faction>> neighborWarCreator(std::shared_ptr<HoI4::Country> country,
		 std::ofstream& AILog,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	std::vector<std::shared_ptr<HoI4::Faction>> radicalWarCreator(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations);

	std::vector<std::shared_ptr<HoI4::Country>> findEvilCountries() const;

	std::set<int> findBorderState(std::shared_ptr<HoI4::Country> country,
		 std::shared_ptr<HoI4::Country> neighbor,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::vector<int> sortStatesByCapitalDistance(const std::set<int>& stateList,
		 std::shared_ptr<HoI4::Country> country,
		 const HoI4::World* world);
	std::vector<std::shared_ptr<HoI4::Country>> findWeakNeighbors(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> findCloseNeighbors(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> findCountriesWithin(int distancePx,
		 std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData);
	std::vector<std::shared_ptr<HoI4::Country>> findWeakColonies(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> findFarNeighbors(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::vector<std::shared_ptr<HoI4::Country>> getGreatPowerTargets(std::shared_ptr<HoI4::Country> country);
	std::map<double, std::shared_ptr<HoI4::Country>> getGPsByDistance(std::shared_ptr<HoI4::Country> country);
	std::vector<std::shared_ptr<HoI4::Faction>> addGreatPowerWars(std::shared_ptr<HoI4::Country> country,
		 HoI4FocusTree& FocusTree,
		 std::vector<std::shared_ptr<HoI4::Country>>& greatPowerTargets,
		 HoI4::Localisation& hoi4Localisations);
	void addTradeEvents(std::shared_ptr<HoI4::Country> country,
		 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowerTargets);

	void setSphereLeaders(const Vic2::World* sourceWorld);
	double GetFactionStrength(const std::shared_ptr<HoI4::Faction>& Faction, int years) const;
	std::string HowToTakeLand(std::shared_ptr<HoI4::Country> TargetCountry,
		 std::shared_ptr<HoI4::Country> AttackingCountry,
		 double time);
	std::vector<std::shared_ptr<HoI4::Country>> GetMorePossibleAllies(
		 const std::shared_ptr<HoI4::Country>& CountryThatWantsAllies);

	double GetFactionStrengthWithDistance(std::shared_ptr<HoI4::Country> HomeCountry,
		 const std::vector<std::shared_ptr<HoI4::Country>>& Faction,
		 double time);
	std::shared_ptr<HoI4::Faction> findFaction(std::shared_ptr<HoI4::Country> checkingCountry);

	std::map<std::string, std::shared_ptr<HoI4::Country>> getNeighbors(std::shared_ptr<HoI4::Country> checkingCountry,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> getImmediateNeighbors(
		 std::shared_ptr<HoI4::Country> checkingCountry,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> getNearbyCountries(
		 std::shared_ptr<HoI4::Country> checkingCountry);


	HoI4FocusTree* genericFocusTree;
	HoI4::World* theWorld;

	HoI4::MapUtils mapUtils;

	std::vector<HoI4::Country*> AggressorFactions;
	std::map<std::shared_ptr<HoI4::Country>, std::vector<std::shared_ptr<HoI4::Country>>> WorldTargetMap;

	std::map<int, std::string> provinceToOwnerMap;
};



#endif // HOI4_WAR_CREATOR_H