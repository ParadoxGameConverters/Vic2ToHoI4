#ifndef MAPS_PROVINCE_POINTS_H
#define MAPS_PROVINCE_POINTS_H



#include <climits>
#include <set>



namespace Maps
{

using Point = std::pair<int, int>;

class ProvincePoints
{
  public:
	void addPoint(const Point& thePoint);

	[[nodiscard]] Point getCentermostPoint() const;

  private:
	std::set<Point> thePoints;
	Point leftmostPoint = {INT_MAX, 0};
	Point rightmostPoint = {0, 0};
	Point highestPoint = {0, 0};
	Point lowestPoint = {0, INT_MAX};
};

} // namespace Maps



#endif // MAPS_PROVINCE_POINTS_H