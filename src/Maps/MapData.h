#ifndef MAPS_MAPDATA_H
#define MAPS_MAPDATA_H



#include "external/common_items/Color.h"
#include "src/Maps/ProvinceDefinitions.h"
#include "src/Maps/ProvincePoints.h"
#include "external/bitmap/bitmap_image.hpp"
#include <map>
#include <optional>
#include <set>



namespace Maps
{

using borderPoints = std::vector<Point>;
using bordersWith = std::map<int, borderPoints>;


class MapData
{
  public:
	MapData(const ProvinceDefinitions& provinceDefinitions, const std::string& path);

	[[nodiscard]] std::set<int> getNeighbors(int province) const;
	[[nodiscard]] std::optional<Point> getSpecifiedBorderCenter(int mainProvince, int neighbor) const;
	[[nodiscard]] std::optional<Point> getAnyBorderCenter(int province) const;
	[[nodiscard]] std::optional<int> getProvinceNumber(const Point& point) const;

	[[nodiscard]] std::optional<ProvincePoints> getProvincePoints(int provinceNum) const;

  private:
	void importProvinces(const bitmap_image& provinceMap);
	void handleNeighbor(const commonItems::Color& centerColor,
		 const commonItems::Color& otherColor,
		 const Point& position);
	void addNeighbor(int mainProvince, int neighborProvince);
	void removeNeighbor(int mainProvince, int neighborProvince);
	void addPointToBorder(int mainProvince, int neighborProvince, Point position);

	void importAdjacencies(const std::string& path);

	std::map<int, std::set<int>> provinceNeighbors;
	std::map<int, bordersWith> borders;
	std::map<int, ProvincePoints> theProvincePoints;

	ProvinceDefinitions provinceDefinitions_;
	std::map<Point, int> pointsToProvinces_;
};

} // namespace Maps



#endif // MAPS_MAPDATA_H