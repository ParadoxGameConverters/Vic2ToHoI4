#ifndef HOI4_WAR_CREATOR_H
#define HOI4_WAR_CREATOR_H



#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/HoI4Localisation.h"
#include "src/HOI4World/HoI4World.h"
#include "src/HOI4World/WarCreator/MapUtils.h"
#include "src/Maps/MapData.h"
#include "src/Maps/ProvinceDefinitions.h"
#include "src/V2World/World/World.h"
#include <fstream>
#include <map>
#include <optional>
#include <string>



const int maxGCWars = 1;


enum class ConquestStrategies
{
	None,
	NoActionNeeded,
	FactionNeeded,
	MoreAlliesNeeded,
	Coup,
};



class HoI4WarCreator
{
  public:
	explicit HoI4WarCreator(HoI4::World* world,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);

  private:
	HoI4WarCreator(const HoI4WarCreator&) = delete;
	HoI4WarCreator& operator=(const HoI4WarCreator&) = delete;

	void addAllTargetsToWorldTargetMap();
	void addTargetsToWorldTargetMap(std::shared_ptr<HoI4::Country> country);
	double calculateWorldStrength(std::ofstream& AILog, const Configuration& theConfiguration) const;
	void generateMajorWars(std::ofstream& AILog,
		 std::set<std::shared_ptr<HoI4::Faction>>& factionsAtWar,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::World* world,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	void generateReconquestWars(std::ofstream& AILog,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);

	std::vector<std::shared_ptr<HoI4::Faction>> fascistWarMaker(std::shared_ptr<HoI4::Country> country,
		 std::ofstream& AILog,
		 const HoI4::World* world,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 const Configuration& theConfiguration);
	std::vector<std::shared_ptr<HoI4::Faction>> communistWarCreator(std::shared_ptr<HoI4::Country> country,
		 const std::set<std::string>& majorIdeologies,
		 std::ofstream& AILog,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	std::vector<std::shared_ptr<HoI4::Faction>> democracyWarCreator(std::shared_ptr<HoI4::Country> country,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	std::vector<std::shared_ptr<HoI4::Faction>> absolutistWarCreator(std::shared_ptr<HoI4::Country> country,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	std::vector<std::shared_ptr<HoI4::Faction>> radicalWarCreator(std::shared_ptr<HoI4::Country> country,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);

	std::vector<std::shared_ptr<HoI4::Country>> findWeakNeighbors(std::shared_ptr<HoI4::Country> country,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions);
	std::vector<std::shared_ptr<HoI4::Country>> findWeakColonies(std::shared_ptr<HoI4::Country> country,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions);
	std::vector<std::shared_ptr<HoI4::Country>> getGreatPowerTargets(std::shared_ptr<HoI4::Country> country);
	std::vector<std::shared_ptr<HoI4::Faction>> addGreatPowerWars(std::shared_ptr<HoI4::Country> country,
		 HoI4FocusTree& FocusTree,
		 std::vector<std::shared_ptr<HoI4::Country>>& greatPowerTargets,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addTradeEvents(std::shared_ptr<HoI4::Country> country,
		 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowerTargets);

	ConquestStrategies HowToTakeLand(std::shared_ptr<HoI4::Country> TargetCountry,
		 std::shared_ptr<HoI4::Country> AttackingCountry,
		 double time);
	std::vector<std::shared_ptr<HoI4::Country>> GetMorePossibleAllies(
		 const std::shared_ptr<HoI4::Country>& CountryThatWantsAllies);

	double GetFactionStrengthWithDistance(const HoI4::Country& homeCountry,
		 const std::vector<std::shared_ptr<HoI4::Country>>& Faction,
		 double time);

	HoI4FocusTree* genericFocusTree;
	HoI4::World* theWorld;

	HoI4::MapUtils mapUtils;

	std::vector<HoI4::Country*> AggressorFactions;
	std::map<std::shared_ptr<HoI4::Country>, std::vector<std::shared_ptr<HoI4::Country>>> WorldTargetMap;
};



#endif // HOI4_WAR_CREATOR_H