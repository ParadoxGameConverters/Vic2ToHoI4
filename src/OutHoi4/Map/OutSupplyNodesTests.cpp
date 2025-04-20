#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Map/OutSupplyNodes.h"
#include <fstream>



TEST(OutHoI4_Map_OutSupplyNodes, ExceptionThrownOnBadPath)
{
	ASSERT_THROW(HoI4::outputSupplyNodes("OutHoI4Tests/BadPath", {}), std::runtime_error);
}


TEST(OutHoI4_Map_OutSupplyNodes, SupplyNodesAreOutput)
{
	std::filesystem::create_directories("OutHoI4Tests/Map/map");

	HoI4::outputSupplyNodes("OutHoI4Tests/Map", {1, 2, 3});

	std::ifstream file("OutHoI4Tests/Map/map/supply_nodes.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::stringstream expected;
	expected << "1 1\n";
	expected << "1 2\n";
	expected << "1 3\n";
	EXPECT_EQ(content, expected.str());
}