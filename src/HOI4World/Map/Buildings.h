#ifndef HOI4_BUILDINGS_H
#define HOI4_BUILDINGS_H



#include "src/Configuration.h"
#include "src/HOI4World/Map/BuildingPosition.h"
#include "src/HOI4World/Map/CoastalProvinces.h"
#include "src/HOI4World/Map/Hoi4Building.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/Maps/MapData.h"
#include "src/Maps/ProvinceDefinitions.h"
#include <map>
#include <optional>
#include <regex>
#include <string>
#include <vector>



namespace HoI4
{

typedef std::map<std::pair<int, int>, BuildingPosition> defaultPositions;


class Buildings
{
  public:
	explicit Buildings(const States& theStates,
		 const CoastalProvinces& theCoastalProvinces,
		 Maps::MapData& theMapData,
		 const Configuration& theConfiguration);

	[[nodiscard]] const auto& getBuildings() const { return buildings; }

  private:
	void importDefaultBuildings(Maps::MapData& theMapData, const Configuration& theConfiguration);
	void processLine(const std::string& line, Maps::MapData& theMapData);
	void importDefaultBuilding(const std::vector<std::string>& matches,
		 defaultPositions& positions,
		 Maps::MapData& theMapData) const;

	void placeBuildings(const States& theStates,
		 const CoastalProvinces& theCoastalProvinces,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeArmsFactories(const States& theStates, const Maps::MapData& theMapData);
	void placeIndustrialComplexes(const States& theStates, const Maps::MapData& theMapData);
	void placeAirports(const States& theStates, const Maps::MapData& theMapData);
	void placeNavalBases(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeFloatingHarbors(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void addFloatingHarbors(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void addNavalBase(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeBunkers(const std::map<int, int>& provinceToStateIDMap,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void addBunker(int stateID, int province, const Maps::MapData& theMapData, const Configuration& theConfiguration);
	void placeCoastalBunkers(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void addCoastalBunker(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeStrongholds(const States& theStates, const Maps::MapData& theMapData);
	void placeDockyards(const States& theStates,
		 const CoastalProvinces& theCoastalProvinces,
		 std::map<int, std::vector<int>> actualCoastalProvinces,
		 const Maps::MapData& theMapData);
	void placeAntiAir(const States& theStates, const Maps::MapData& theMapData);
	void placeSyntheticRefineries(const States& theStates, const Maps::MapData& theMapData);
	void placeFuelSilos(const States& theStates, const Maps::MapData& theMapData);
	void placeRadarStations(const States& theStates, const Maps::MapData& theMapData);
	void placeNavalSupplyHubs(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void addNavalSupplyHub(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeNavalHeadquarters(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void addNavalHeadquarters(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeNuclearReactors(const States& theStates, const Maps::MapData& theMapData);
	void placeSpecialProjects(const States& theStates, const Maps::MapData& theMapData);
	void placeDams(const States& theStates, const Maps::MapData& theMapData);
	void placeCanals(const States& theStates, const Maps::MapData& theMapData);
	void placeRocketSites(const States& theStates, const Maps::MapData& theMapData);

	void placeSupplyNodes(const std::map<int, int>& provinceToStateIDMap,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);

	void addSupplyNodes(int stateID,
		 int province,
		 const Maps::MapData& theMapData,
		 const Configuration& theConfiguration);

	void placeLandmarks(const States& theStates, const Maps::MapData& theMapData);

	std::multimap<int, Building> buildings;

	defaultPositions defaultArmsFactories;
	defaultPositions defaultIndustrialComplexes;
	defaultPositions defaultAirBases;
	defaultPositions defaultNavalBases;
	defaultPositions defaultBunkers;
	defaultPositions defaultCoastalBunkers;
	defaultPositions defaultStrongholds;
	defaultPositions defaultDockyards;
	defaultPositions defaultAntiAirs;
	defaultPositions defaultSyntheticRefineries;
	defaultPositions defaultFuelSilos;
	defaultPositions defaultRadarStations;
	defaultPositions defaultNavalSupplyHubs;
	defaultPositions defaultNavalHqs;
	defaultPositions defaultNuclearReactors;
	defaultPositions defaultSpecialProjects;
	defaultPositions defaultDams;
	defaultPositions defaultCanals;
	defaultPositions defaultSupplyNodes;
	defaultPositions defaultFloatingHarbors;
	defaultPositions defaultRocketSites;
	defaultPositions defaultLandmarks;
};

} // namespace HoI4



#endif // HOI4_BUILDINGS_H