#include "HOI4World/Regions/Regions.h"
#include "HOI4World/Regions/RegionsFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



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


TEST(HoI4World_Regions_RegionsTests, GeographyInUnmappedRegionReturnsEmpty)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::vector<std::string>{}, regions->getRegionGeography("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, GeographyInMappedRegionReturnsGeography)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_THAT(regions->getRegionGeography("test_region"), testing::UnorderedElementsAre("localregion", "superregion"));
}


TEST(HoI4World_Regions_RegionsTests, BlockedInUnmappedRegionReturnsEmpty)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ(std::vector<std::string>{}, regions->getRegionBlocked("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, BlockedInMappedRegionReturnsBlocked)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_THAT(regions->getRegionBlocked("test_region"), testing::UnorderedElementsAre("localregion", "superregion"));
}