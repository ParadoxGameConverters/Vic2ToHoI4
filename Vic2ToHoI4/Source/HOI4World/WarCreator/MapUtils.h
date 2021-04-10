#ifndef MAP_UTILS_H
#define MAP_UTILS_H



#include "HOI4World/HoI4Country.h"
#include "HOI4World/HoI4World.h"
#include <memory>
#include <optional>



namespace HoI4
{

struct Coordinate
{
	int x;
	int y;
};


class MapUtils
{
  public:
	explicit MapUtils(const std::map<int, State>& theStates);

	[[nodiscard]] std::optional<double> getDistanceBetweenCapitals(const Country& Country1,
		 const Country& Country2) const;

	[[nodiscard]] std::optional<Coordinate> getCapitalPosition(const Country& country) const;
	[[nodiscard]] std::set<int> findBorderStates(const Country& country,
		 const Country& neighbor,
		 const std::map<int, int>& provinceToStateIdMapping,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions) const;
	[[nodiscard]] std::vector<int> sortStatesByDistance(const std::set<int>& stateList,
		 const Coordinate& location,
		 const std::map<int, State>& states) const;

	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> getNeighbors(const Country& checkingCountry,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> getImmediateNeighbors(const Country& checkingCountry,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> findCloseNeighbors(const Country& country,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> findFarNeighbors(const Country& country,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> findCountriesWithin(int distancePx,
		 const Country& country,
		 const MapData& theMapData,
		 const World& theWorld) const;
	[[nodiscard]] std::map<double, std::shared_ptr<Country>> getGPsByDistance(const Country& country,
		 const World& theWorld) const;

  private:
	void determineProvinceOwners(const std::map<int, State>& theStates);
	void addProvincePosition(const std::vector<std::string>& lineTokens);
	[[nodiscard]] std::vector<std::string> tokenizeLine(const std::string& line) const;
	void processPositionLine(const std::string& line);
	void establishProvincePositions();
	[[nodiscard]] Coordinate getProvincePosition(int provinceNum) const;
	[[nodiscard]] double getDistanceBetweenPoints(const Coordinate& point1, const Coordinate& point2) const;
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> getNearbyCountries(const Country& checkingCountry,
		 const World& theWorld) const;
	[[nodiscard]] std::optional<double> getDistanceBetweenCountries(const Country& Country1,
		 const Country& Country2) const;

	std::map<int, Coordinate> provincePositions;
	std::map<int, std::string> provinceToOwnerMap;
};

} // namespace HoI4



#endif // MAP_UTILS_H