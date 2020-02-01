#include "ProvincePoints.h"



void HoI4::ProvincePoints::addPoint(const point& thePoint)
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


double calculateDistanceSquared(int pointX, int pointY, int centerX, int centerY);
point HoI4::ProvincePoints::getCentermostPoint() const
{
	point possibleCenter;
	possibleCenter.first = (leftmostPoint.first + rightmostPoint.first) / 2;
	possibleCenter.second = (lowestPoint.second + highestPoint.second) / 2;
	if (thePoints.count(possibleCenter))
	{
		return possibleCenter;
	}
	else
	{
		auto shortestDistance = std::numeric_limits<double>::max();
		point closestPoint;
		for (const auto& possiblePoint: thePoints)
		{
			const auto distanceSquared = calculateDistanceSquared(
				possiblePoint.first,
				possiblePoint.second,
				possibleCenter.first,
				possibleCenter.second
			);
			if (distanceSquared < shortestDistance)
			{
				shortestDistance = distanceSquared;
				closestPoint = possiblePoint;
			}
		}
		return closestPoint;
	}
}


double calculateDistanceSquared(const int pointX, const int pointY, const int centerX, const int centerY)
{
	const auto deltaX = static_cast<double>(pointX) - static_cast<double>(centerX);
	const auto deltaY = static_cast<double>(pointY) - static_cast<double>(centerY);
	return deltaX * deltaX + deltaY * deltaY;
}