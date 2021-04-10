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
	explicit MapUtils(const World& theWorld);

	std::optional<double> getDistanceBetweenCapitals(const Country& Country1, const Country& Country2) const;

	std::set<int> findBorderState(const Country& country,
		 const Country& neighbor,
		 const World& world,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions) const;
	std::vector<int> sortStatesByCapitalDistance(const std::set<int>& stateList,
		 const Country& country,
		 const World& world) const;

	std::map<std::string, std::shared_ptr<Country>> getNeighbors(const Country& checkingCountry,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	std::map<std::string, std::shared_ptr<Country>> getImmediateNeighbors(const Country& checkingCountry,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	std::map<std::string, std::shared_ptr<Country>> findCloseNeighbors(const Country& country,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	std::map<std::string, std::shared_ptr<Country>> findFarNeighbors(const Country& country,
		 const MapData& theMapData,
		 const ProvinceDefinitions& provinceDefinitions,
		 const World& theWorld) const;
	std::map<std::string, std::shared_ptr<Country>> findCountriesWithin(int distancePx,
		 const Country& country,
		 const MapData& theMapData,
		 const World& theWorld) const;
	std::map<double, std::shared_ptr<Country>> getGPsByDistance(const Country& country, const World& theWorld) const;

  private:
	void determineProvinceOwners(const World& theWorld);
	void addProvincePosition(const std::vector<std::string>& tokenizedLine);
	std::vector<std::string> tokenizeLine(const std::string& line) const;
	void processPositionLine(const std::string& line);
	void establishProvincePositions();
	std::pair<int, int> getProvincePosition(int provinceNum) const;
	std::pair<int, int> getCapitalPosition(const Country& country) const;
	bool bothCountriesHaveCapitals(const Country& Country1, const Country& Country2) const;
	double getDistanceBetweenPoints(const std::pair<int, int>& point1, const std::pair<int, int>& point2) const;
	std::map<std::string, std::shared_ptr<Country>> getNearbyCountries(const Country& checkingCountry,
		 const World& theWorld) const;
	std::optional<double> getDistanceBetweenCountries(const Country& Country1, const Country& Country2) const;

	std::map<int, std::pair<int, int>> provincePositions;
	std::map<int, std::string> provinceToOwnerMap;
};

} // namespace HoI4



#endif // MAP_UTILS_H