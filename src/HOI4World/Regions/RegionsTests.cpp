#include "src/HOI4World/Regions/Regions.h"
#include "src/HOI4World/Regions/RegionsFactory.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Regions_RegionsTests, ProvinceInUnmappedRegionsReturnsNullptr)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::nullopt, regions->getRegion(0));
}


TEST(HoI4World_Regions_RegionsTests, ProvinceInMappedRegionsReturnsRegion)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ("test_region", regions->getRegion(42));
}


TEST(HoI4World_Regions_RegionsTests, NameInUnmappedRegionReturnsNullopt)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::nullopt, regions->getRegionName("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, NameInMappedRegionReturnsName)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ("Test Region", regions->getRegionName("test_region"));
}


TEST(HoI4World_Regions_RegionsTests, AdjectiveInUnmappedRegionReturnsNullopt)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::nullopt, regions->getRegionAdjective("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, AdjectiveInMappedRegionReturnsAdjective)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ("Test Regional", regions->getRegionAdjective("test_region"));
}


TEST(HoI4World_Regions_RegionsTests, LevelInUnmappedRegionReturnsNullopt)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::nullopt, regions->getRegionLevel("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, LevelInMappedRegionReturnsLevel)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ("autonomy_test", regions->getRegionLevel("test_region"));
}


TEST(HoI4World_Regions_RegionsTests, SubregionsInUnmappedRegionReturnsEmpty)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::vector<std::string>{}, regions->getSubregions("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, SubregionsInMappedRegionReturnsSubregions)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_THAT(regions->getSubregions("superregion1"), testing::UnorderedElementsAre("test_region", "subregion1"));
}


TEST(HoI4World_Regions_RegionsTests, BlockedInUnmappedRegionReturnsEmpty)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::vector<std::string>{}, regions->getBlockedRegions("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, BlockedInMappedRegionReturnsBlocked)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_THAT(regions->getBlockedRegions("test_region"), testing::UnorderedElementsAre("region1", "region2"));
}


TEST(HoI4World_Regions_RegionsTests, SuperregionsInUnmappedRegionReturnsEmpty)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::vector<std::string>{}, regions->getSuperregions("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, SuperregionsInMappedRegionReturnsGeography)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_THAT(regions->getSuperregions("test_region"), testing::UnorderedElementsAre("superregion1", "superregion2"));
}