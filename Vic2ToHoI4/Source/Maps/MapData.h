#ifndef MAP_DATA_H
#define MAP_DATA_H



#include "Color.h"
#include "Configuration.h"
#include "Maps/ProvinceDefinitions.h"
#include "ProvincePoints.h"
#include "bitmap_image.hpp"
#include <map>
#include <optional>
#include <set>



typedef std::vector<Maps::Point> borderPoints;
typedef std::map<int, borderPoints> bordersWith;



namespace Maps
{

class MapData
{
  public:
	MapData(const ProvinceDefinitions& provinceDefinitions, const Configuration& theConfiguration);

	[[nodiscard]] std::set<int> getNeighbors(int province) const;
	[[nodiscard]] std::optional<Point> getSpecifiedBorderCenter(int mainProvince, int neighbor) const;
	[[nodiscard]] std::optional<Point> getAnyBorderCenter(int province) const;
	[[nodiscard]] std::optional<int> getProvinceNumber(double x,
		 double y,
		 const ProvinceDefinitions& provinceDefinitions) const;

	[[nodiscard]] std::optional<ProvincePoints> getProvincePoints(int provinceNum) const;

  private:
	void importProvinces(const ProvinceDefinitions& provinceDefinitions, const std::string& hoi4Path);
	void handleNeighbor(const commonItems::Color& centerColor,
		 const commonItems::Color& otherColor,
		 const Point& position,
		 const ProvinceDefinitions& provinceDefinitions);
	void addNeighbor(int mainProvince, int neighborProvince);
	void removeNeighbor(int mainProvince, int neighborProvince);
	void addPointToBorder(int mainProvince, int neighborProvince, Point position);

	void importAdjacencies(const std::string& hoi4Path);

	std::map<int, std::set<int>> provinceNeighbors;
	std::map<int, bordersWith> borders;
	std::map<int, ProvincePoints> theProvincePoints;

	bitmap_image provinceMap;
};

} // namespace Maps



#endif // MAP_DATA_H
