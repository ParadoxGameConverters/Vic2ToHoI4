#ifndef MAP_UTILS_H
#define MAP_UTILS_H



#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/HoI4World.h"
#include <memory>
#include <optional>



namespace HoI4
{

struct Coordinate
{
	int x;
	int y;

	auto operator<=>(const Coordinate&) const = default;
};


class MapUtils
{
  public:
	explicit MapUtils(const std::map<int, State>& theStates,
		 const std::map<std::string, std::shared_ptr<Country>>& theCountries);

	[[nodiscard]] std::optional<float> getDistanceBetweenCapitals(const Country& country1, const Country& country2);

	[[nodiscard]] std::optional<Coordinate> getCapitalPosition(const Country& country) const;

	// Returns the state IDs of all states within neighbor that border states withing country
	[[nodiscard]] std::set<int> findBorderStates(const Country& country,
		 const Country& neighbor,
		 const std::map<int, int>& provinceToStateIdMapping,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions) const;
	[[nodiscard]] std::vector<int> sortStatesByDistance(const std::set<int>& stateList,
		 const Coordinate& location,
		 const std::map<int, State>& states);

	[[nodiscard]] std::set<std::string> getNearbyCountries(const std::string& country, float range) const;
	[[nodiscard]] std::set<std::string> getFarCountries(const std::string& country, float range) const;
	[[nodiscard]] std::vector<std::string> getGPsByDistance(const Country& country,
		 const std::vector<std::shared_ptr<Country>>& greatPowers);
	[[nodiscard]] const auto& getNeighbors(const std::string& country) const { return neighbors.at(country); }

  private:
	void establishProvincePositions();
	void addProvincePosition(const std::vector<std::string>& lineTokens);
	[[nodiscard]] std::vector<std::string> tokenizeLine(const std::string& line) const;
	void processPositionLine(const std::string& line);
	void determineProvinceOwners(const std::map<int, State>& theStates);
	void establishDistancesBetweenCountries(const std::map<std::string, std::shared_ptr<Country>>& theCountries);

	[[nodiscard]] std::optional<Coordinate> getProvincePosition(int provinceNum) const;
	[[nodiscard]] float getDistanceSquaredBetweenPoints(const Coordinate& point1, const Coordinate& point2);
	[[nodiscard]] std::optional<float> getDistanceBetweenCountries(const Country& country1, const Country& country2);

	std::map<int, Coordinate> provincePositions;
	std::map<int, std::string> provinceToOwnerMap;
	std::map<std::string, std::map<std::string, float>> distancesBetweenCountries;
	std::map<std::string, std::set<std::string>> neighbors;
};

} // namespace HoI4



#endif // MAP_UTILS_H