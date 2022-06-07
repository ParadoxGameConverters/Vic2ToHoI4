#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Map/OutRailway.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(OutHoI4_Map_OutRailway, RailwayIsOutput)
{
	const HoI4::Railway railway(4, {32, 64, 96});
	std::stringstream output;
	output << railway;

	std::stringstream expected;
	expected << "4 3 32 64 96\n";
	EXPECT_EQ(output.str(), expected.str());
}