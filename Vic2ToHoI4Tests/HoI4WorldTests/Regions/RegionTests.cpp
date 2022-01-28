#include "HOI4World/Regions/Region.h"
#include "HOI4World/Regions/RegionFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(HoI4World_Regions_RegionsTests, DefaultsAreSet)
{
	std::stringstream input;
	const auto region = HoI4::Region::Factory().importRegion(input);

	EXPECT_TRUE(region->getName().empty());
	EXPECT_TRUE(region->getAdjective().empty());
	EXPECT_TRUE(region->getProvinces().empty());
	EXPECT_TRUE(region->getLevel().empty());
	EXPECT_TRUE(region->getBlocked().empty());
}


TEST(HoI4World_Regions_RegionsTests, ItemsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = \"Test Name\"\n";
	input << "\tadjective = \"Test Adjective\"\n";
	input << "\tprovinces = { 42 43 44 }\n";
	input << "\tlevel = autonomy_test\n";
	input << "\tsubregions = { subregion1 subregion2 }\n";
	input << "\tblocked = { region1 region2 }\n";
	input << "}";
	const auto region = HoI4::Region::Factory().importRegion(input);

	EXPECT_EQ("Test Name", region->getName());
	EXPECT_EQ("Test Adjective", region->getAdjective());
	EXPECT_THAT(region->getProvinces(), testing::UnorderedElementsAre(42, 43, 44));
	EXPECT_EQ("autonomy_test", region->getLevel());
	EXPECT_THAT(region->getSubregions(), testing::UnorderedElementsAre("subregion1", "subregion2"));
	EXPECT_THAT(region->getBlocked(), testing::UnorderedElementsAre("region1", "region2"));
}