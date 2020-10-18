#include "HOI4World/Map/ProvincePoints.h"
#include "gtest/gtest.h"



TEST(HoI4World_Map_ProvincePoints, CentermostIsOriginIfNoPoints)
{
	const HoI4::ProvincePoints provincePoints;

	const point expectedPoint{0, 0};
	ASSERT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}


TEST(HoI4World_Map_ProvincePoints, CenterPointIsAverageLatitude)
{
	HoI4::ProvincePoints provincePoints;
	provincePoints.addPoint(point{0, 1});
	provincePoints.addPoint(point{0, 2});
	provincePoints.addPoint(point{0, 3});
	provincePoints.addPoint(point{0, 4});

	const point expectedPoint{0, 2};
	ASSERT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}


TEST(HoI4World_Map_ProvincePoints, CenterPointIsAverageLongitude)
{
	HoI4::ProvincePoints provincePoints;
	provincePoints.addPoint(point{1, 0});
	provincePoints.addPoint(point{2, 0});
	provincePoints.addPoint(point{3, 0});
	provincePoints.addPoint(point{4, 0});

	const point expectedPoint{2, 0};
	ASSERT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}


TEST(HoI4World_Map_ProvincePoints, CentermostPointWhenCenterNotControlled)
{
	HoI4::ProvincePoints provincePoints;
	provincePoints.addPoint(point{1, 0});
	provincePoints.addPoint(point{3, 0});
	provincePoints.addPoint(point{10, 0});

	const point expectedPoint{3, 0};
	ASSERT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}