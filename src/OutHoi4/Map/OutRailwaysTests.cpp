#include "external/common_items/OSCompatibilityLayer.h"
#include "OutHoi4/Map/OutRailways.h"
#include "gtest/gtest.h"
#include <fstream>



using HoI4::Railway;



TEST(OutHoI4_Map_OutRailways, ExceptionThrownOnBadPath)
{
	ASSERT_THROW(HoI4::outputRailways("OutHoI4Tests/BadPath", {}), std::runtime_error);
}


TEST(OutHoI4_Map_OutRailways, RailwaysAreOutput)
{
	commonItems::TryCreateFolder("OutHoI4Tests");
	commonItems::TryCreateFolder("OutHoI4Tests/Map");
	commonItems::TryCreateFolder("OutHoI4Tests/Map/map");

	const Railway railwayOne(1, {1, 2, 3});
	const Railway railwayTwo(2, {10, 11, 12, 13});
	const Railway railwayThree(3, {20, 21, 22, 23, 24});
	HoI4::outputRailways("OutHoI4Tests/Map", {railwayOne, railwayTwo, railwayThree});

	std::ifstream file("OutHoI4Tests/Map/map/railways.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::stringstream expected;
	expected << "1 3 1 2 3\n";
	expected << "2 4 10 11 12 13\n";
	expected << "3 5 20 21 22 23 24\n";
	EXPECT_EQ(content, expected.str());
}