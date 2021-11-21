#ifndef PROVINCE_POINTS_H
#define PROVINCE_POINTS_H



#include <climits>
#include <set>



typedef std::pair<int, int> point;



namespace Maps
{

class ProvincePoints
{
  public:
	void addPoint(const point& thePoint);

	[[nodiscard]] point getCentermostPoint() const;

  private:
	std::set<point> thePoints;
	point leftmostPoint = {INT_MAX, 0};
	point rightmostPoint = {-1, 0};
	point highestPoint = {0, -1};
	point lowestPoint = {0, INT_MAX};
};

} // namespace Maps



#endif // PROVINCE_POINTS_H