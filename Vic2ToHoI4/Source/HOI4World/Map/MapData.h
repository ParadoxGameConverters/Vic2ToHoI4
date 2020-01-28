#ifndef MAP_DATA_H
#define MAP_DATA_H



#include <optional>
#include <map>
#include <set>
#include "../../bitmap_image.hpp"
#include "../../Color.h"



typedef std::pair<int, int> point;
typedef std::vector<point> borderPoints;
typedef std::map<int, borderPoints> bordersWith;



namespace HoI4
{

class provincePoints
{
	public:
		provincePoints() = default;

		void addPoint(const point& thePoint);

		point getCentermostPoint();

	private:
		std::set<point> thePoints;
		point leftmostPoint = {1000000, 0};
		point rightmostPoint = {-1, 0};
		point highestPoint = {0, -1};
		point lowestPoint = {0, 1000000};
};


class MapData
{
	public:
		MapData() noexcept;

		std::set<int> getNeighbors(int province) const;
		std::optional<point> getSpecifiedBorderCenter(int mainProvince, int neighbor) const;
		std::optional<point> getAnyBorderCenter(int province) const;
		std::optional<int> getProvinceNumber(double x, double y);

		std::optional<provincePoints> getProvincePoints(int provinceNum) const;

	private:
		MapData(const MapData&) = delete;
		MapData& operator=(const MapData&) = delete;

		ConverterColor::Color getCenterColor(point position);
		ConverterColor::Color getAboveColor(point position, int height);
		ConverterColor::Color getBelowColor(point position, int height);
		ConverterColor::Color getLeftColor(point position, int width);
		ConverterColor::Color getRightColor(point position, int width);
		void handleNeighbor(
			const ConverterColor::Color& centerColor,
			const ConverterColor::Color& otherColor,
			const point& position
		);
		void addNeighbor(int mainProvince, int neighborProvince);
		void addPointToBorder(int mainProvince, int neighborProvince, point position);

		std::map<int, std::set<int>> provinceNeighbors;
		std::map<int, bordersWith> borders;
		std::map<int, provincePoints> theProvincePoints;

		bitmap_image provinceMap;
};

}



#endif //MAP_DATA_H
