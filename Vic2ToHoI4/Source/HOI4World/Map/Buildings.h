#ifndef HOI4_BUILDINGS_H
#define HOI4_BUILDINGS_H



#include "BuildingPosition.h"
#include "Configuration.h"
#include "HOI4World/Map/CoastalProvinces.h"
#include "HOI4World/States/HoI4States.h"
#include "Hoi4Building.h"
#include "Maps/MapData.h"
#include "Maps/ProvinceDefinitions.h"
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
		 MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const Configuration& theConfiguration);

	[[nodiscard]] const auto& getBuildings() const { return buildings; }
	[[nodiscard]] const auto& getAirportLocations() const { return airportLocations; }

  private:
	void importDefaultBuildings(MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const Configuration& theConfiguration);
	void processLine(const std::string& line, MapData& theMapData, const ProvinceDefinitions& provinceDefinitions);
	void importDefaultBuilding(const std::smatch& matches,
		 defaultPositions& positions,
		 MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions) const;

	void placeBuildings(const States& theStates,
		 const CoastalProvinces& theCoastalProvinces,
		 const MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeArmsFactories(const States& theStates, const MapData& theMapData);
	void placeIndustrialComplexes(const States& theStates, const MapData& theMapData);
	void placeAirports(const States& theStates, const MapData& theMapData);
	void placeNavalBases(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const MapData& theMapData,
		 const Configuration& theConfiguration);
	void addNavalBase(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeBunkers(const std::map<int, int>& provinceToStateIDMap,
		 const MapData& theMapData,
		 const Configuration& theConfiguration);
	void addBunker(int stateID, int province, const MapData& theMapData, const Configuration& theConfiguration);
	void placeCoastalBunkers(const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, std::vector<int>>& actualCoastalProvinces,
		 const MapData& theMapData,
		 const Configuration& theConfiguration);
	void addCoastalBunker(int stateID,
		 const std::pair<int, std::vector<int>>& province,
		 const MapData& theMapData,
		 const Configuration& theConfiguration);
	void placeDockyards(const States& theStates,
		 const CoastalProvinces& theCoastalProvinces,
		 std::map<int, std::vector<int>> actualCoastalProvinces,
		 const MapData& theMapData);
	void placeAntiAir(const States& theStates, const MapData& theMapData);
	void placeSyntheticRefineries(const States& theStates, const MapData& theMapData);
	void placeNuclearReactors(const States& theStates, const MapData& theMapData);

	std::multimap<int, Building> buildings;

	defaultPositions defaultArmsFactories;
	defaultPositions defaultIndustrialComplexes;
	defaultPositions defaultAirBases;
	defaultPositions defaultNavalBases;
	defaultPositions defaultBunkers;
	defaultPositions defaultCoastalBunkers;
	defaultPositions defaultDockyards;
	defaultPositions defaultAntiAirs;
	defaultPositions defaultSyntheticRefineries;
	defaultPositions defaultNuclearReactors;

	std::map<int, int> airportLocations;
};

} // namespace HoI4



#endif // HOI4_BUILDINGS_H