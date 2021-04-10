#ifndef MAP_UTILS_H
#define MAP_UTILS_H



#include "HOI4World/HoI4Country.h"
#include "HOI4World/HoI4World.h"
#include <memory>
#include <optional>



namespace HoI4
{

class MapUtils
{
  public:
	MapUtils(const World& theWorld);
	
	std::optional<double> getDistanceBetweenCountries(std::shared_ptr<Country> Country1,
		 std::shared_ptr<Country> Country2);
	std::optional<double> getDistanceBetweenCapitals(std::shared_ptr<Country> Country1,
		 std::shared_ptr<Country> Country2);
	bool bothCountriesHaveCapitals(std::shared_ptr<Country> Country1, std::shared_ptr<Country> Country2) const;
	std::pair<int, int> getCapitalPosition(std::shared_ptr<Country> country);
	std::pair<int, int> getProvincePosition(int provinceNum);
	void establishProvincePositions();
	void processPositionLine(const std::string& line);
	std::vector<std::string> tokenizeLine(const std::string& line);
	void addProvincePosition(const std::vector<std::string>& tokenizedLine);
	double getDistanceBetweenPoints(std::pair<int, int> point1, std::pair<int, int> point2) const;

	void determineProvinceOwners(const World& theWorld);

	std::map<std::string, std::shared_ptr<HoI4::Country>> getNeighbors(std::shared_ptr<HoI4::Country> checkingCountry,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld);
	std::map<std::string, std::shared_ptr<HoI4::Country>> getImmediateNeighbors(
		 std::shared_ptr<HoI4::Country> checkingCountry,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld);
	std::map<std::string, std::shared_ptr<HoI4::Country>> getNearbyCountries(
		 std::shared_ptr<HoI4::Country> checkingCountry,
		 const World& theWorld);
	std::set<int> findBorderState(std::shared_ptr<HoI4::Country> country,
		 std::shared_ptr<HoI4::Country> neighbor,
		 const HoI4::World* world,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions);
	std::map<std::string, std::shared_ptr<HoI4::Country>> findCloseNeighbors(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld);
	std::map<std::string, std::shared_ptr<HoI4::Country>> findCountriesWithin(int distancePx,
		 std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const World& theWorld);
	std::map<std::string, std::shared_ptr<HoI4::Country>> findFarNeighbors(std::shared_ptr<HoI4::Country> country,
		 const HoI4::MapData& theMapData,
		 const HoI4::ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld);
	std::map<double, std::shared_ptr<HoI4::Country>> getGPsByDistance(std::shared_ptr<HoI4::Country> country,
		 const World& theWorld);
	std::vector<int> sortStatesByCapitalDistance(const std::set<int>& stateList,
		 std::shared_ptr<HoI4::Country> country,
		 const HoI4::World* world);

  private:
	std::map<int, std::pair<int, int>> provincePositions;
	std::map<int, std::string> provinceToOwnerMap;
};

} // namespace HoI4



#endif // MAP_UTILS_H