#ifndef HOI4_BUILDINGS_H
#define HOI4_BUILDINGS_H



#include <fstream>
#include <map>
#include <optional>
#include <regex>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class coastalProvinces;
class MapData;
class States;


struct buildingPosition
{
	double xCoordinate = 0.0;
	double yCoordinate = 0.0;
	double zCoordinate = 0.0;
	double rotation = 0.0;
};


class Building
{
	public:
		explicit Building(int _stateID, const std::string& _type, buildingPosition& _position, std::optional<int> _connectingSeaProvince);

		friend std::ostream& operator << (std::ostream& out, const Building& building);

	private:
		Building(const Building&) = delete;
		Building& operator=(const Building&) = delete;

		int stateID = 0;
		std::string type;
		buildingPosition position;
		int connectingSeaProvince = 0;
};


std::ostream& operator << (std::ostream& out, const Building& building);


typedef std::map<std::pair<int, int>, buildingPosition> defaultPositions;


class Buildings
{
	public:
		explicit Buildings(const States& theStates, const coastalProvinces& theCoastalProvinces, MapData& theMapData);

		void output() const;

	private:
		Buildings(const Buildings&) = delete;
		Buildings& operator=(const Buildings&) = delete;

		void importDefaultBuildings(MapData& theMapData);
		void processLine(const std::string& line, MapData& theMapData);
		void importDefaultBuilding(const std::smatch& matches, defaultPositions& positions, MapData& theMapData);

		void placeBuildings(
			const States& theStates,
			const coastalProvinces& theCoastalProvinces,
			const MapData& theMapData
		);
		void placeArmsFactories(const States& theStates, const MapData& theMapData);
		void placeIndustrialComplexes(const States& theStates, const MapData& theMapData);
		void placeAirports(const States& theStates, const MapData& theMapData);
		void placeNavalBases(
			const std::map<int, int>& provinceToStateIDMap,
			const std::map<int, std::vector<int>>& actualCoastalProvinces,
			const MapData& theMapData
		);
		void addNavalBase(int stateID, const std::pair<int, std::vector<int>>& province, const MapData& theMapData);
		void placeBunkers(const std::map<int, int>& provinceToStateIDMap, const MapData& theMapData);
		void addBunker(int stateID, int province, const MapData& theMapData);
		void placeCoastalBunkers(
			const std::map<int, int>& provinceToStateIDMap,
			const std::map<int, std::vector<int>>& actualCoastalProvinces,
			const MapData& theMapData
		);
		void addCoastalBunker(int stateID, const std::pair<int, std::vector<int>>& province, const MapData& theMapData);
		void placeDockyards(
			const States& theStates,
			const coastalProvinces& theCoastalProvinces,
			std::map<int, std::vector<int>> actualCoastalProvinces,
			const MapData& theMapData
		);
		void placeAntiAir(const States& theStates, const MapData& theMapData);
		void placeSyntheticRefineries(const States& theStates, const MapData& theMapData);
		void placeNuclearReactors(const States& theStates, const MapData& theMapData);

		std::multimap<int, Building*> buildings;

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

}




#endif // HOI4_BUILDINGS_H