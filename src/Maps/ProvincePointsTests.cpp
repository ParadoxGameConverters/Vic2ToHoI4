#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Maps/ProvincePoints.h"



TEST(Maps_ProvincePoints, CentermostIsOriginIfNoPoints)
{
	const Maps::ProvincePoints provincePoints;

	constexpr Maps::Point expectedPoint{0, 0};
	EXPECT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}


TEST(Maps_ProvincePoints, CenterPointIsAverageLatitude)
{
	Maps::ProvincePoints provincePoints;
	provincePoints.addPoint(Maps::Point{0, 1});
	provincePoints.addPoint(Maps::Point{0, 2});
	provincePoints.addPoint(Maps::Point{0, 3});
	provincePoints.addPoint(Maps::Point{0, 4});

	constexpr Maps::Point expectedPoint{0, 2};
	EXPECT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}


TEST(Maps_ProvincePoints, CenterPointIsAverageLongitude)
{
	Maps::ProvincePoints provincePoints;
	provincePoints.addPoint(Maps::Point{1, 0});
	provincePoints.addPoint(Maps::Point{2, 0});
	provincePoints.addPoint(Maps::Point{3, 0});
	provincePoints.addPoint(Maps::Point{4, 0});

	constexpr Maps::Point expectedPoint{2, 0};
	EXPECT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}


TEST(Maps_ProvincePoints, CentermostPointWhenCenterNotControlled)
{
	Maps::ProvincePoints provincePoints;
	provincePoints.addPoint(Maps::Point{1, 0});
	provincePoints.addPoint(Maps::Point{3, 0});
	provincePoints.addPoint(Maps::Point{10, 0});

	constexpr Maps::Point expectedPoint{3, 0};
	EXPECT_EQ(expectedPoint, provincePoints.getCentermostPoint());
}