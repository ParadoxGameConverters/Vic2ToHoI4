#ifndef MAP_DATA_H
#define MAP_DATA_H



#include "ProvincePoints.h"
#include "bitmap_image.hpp"
#include "newColor.h"
#include <map>
#include <optional>
#include <set>



class Configuration;


typedef std::vector<point> borderPoints;
typedef std::map<int, borderPoints> bordersWith;



namespace HoI4
{

class ProvinceDefinitions;


class MapData
{
  public:
	MapData(const ProvinceDefinitions& provinceDefinitions, const Configuration& theConfiguration);

	[[nodiscard]] std::set<int> getNeighbors(int province) const;
	[[nodiscard]] std::optional<point> getSpecifiedBorderCenter(int mainProvince, int neighbor) const;
	[[nodiscard]] std::optional<point> getAnyBorderCenter(int province) const;
	[[nodiscard]] std::optional<int> getProvinceNumber(double x,
		 double y,
		 const ProvinceDefinitions& provinceDefinitions) const;

	[[nodiscard]] std::optional<ProvincePoints> getProvincePoints(int provinceNum) const;

  private:
	void handleNeighbor(const commonItems::newColor& centerColor,
		 const commonItems::newColor& otherColor,
		 const point& position,
		 const ProvinceDefinitions& provinceDefinitions);
	void addNeighbor(int mainProvince, int neighborProvince);
	void addPointToBorder(int mainProvince, int neighborProvince, point position);

	std::map<int, std::set<int>> provinceNeighbors;
	std::map<int, bordersWith> borders;
	std::map<int, ProvincePoints> theProvincePoints;

	bitmap_image provinceMap;
};

} // namespace HoI4



#endif // MAP_DATA_H
