#include "ProvincePoints.h"
#include <numeric>



namespace
{

double calculateDistanceSquared(const Maps::Point point, const Maps::Point center)
{
	const auto deltaX = static_cast<double>(point.first) - static_cast<double>(center.first);
	const auto deltaY = static_cast<double>(point.second) - static_cast<double>(center.second);
	return deltaX * deltaX + deltaY * deltaY;
}

} // namespace



void Maps::ProvincePoints::addPoint(const Point& thePoint)
{
	thePoints.emplace(thePoint);
	if (thePoint.first < leftmostPoint.first)
	{
		leftmostPoint = thePoint;
	}
	if (thePoint.first > rightmostPoint.first)
	{
		rightmostPoint = thePoint;
	}
	if (thePoint.second < lowestPoint.second)
	{
		lowestPoint = thePoint;
	}
	if (thePoint.second > highestPoint.second)
	{
		highestPoint = thePoint;
	}
}


Maps::Point Maps::ProvincePoints::getCentermostPoint() const
{
	Point possibleCenter;
	possibleCenter.first = std::midpoint(leftmostPoint.first, rightmostPoint.first);
	possibleCenter.second = std::midpoint(lowestPoint.second, highestPoint.second);
	if (thePoints.contains(possibleCenter))
	{
		return possibleCenter;
	}

	auto shortestDistance = std::numeric_limits<double>::max();
	Point closestPoint;
	for (const auto& possiblePoint: thePoints)
	{
		const auto distanceSquared = calculateDistanceSquared(possiblePoint, possibleCenter);
		if (distanceSquared < shortestDistance)
		{
			shortestDistance = distanceSquared;
			closestPoint = possiblePoint;
		}
	}
	return closestPoint;
}