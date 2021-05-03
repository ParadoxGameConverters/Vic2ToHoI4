#include "HOI4World/Regions/Regions.h"
#include "HOI4World/Regions/RegionsFactory.h"
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

	EXPECT_EQ(std::nullopt, regions->getRegionName("missing_region"));
}


TEST(HoI4World_Regions_RegionsTests, AdjectiveInMappedRegionReturnsAdjective)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	EXPECT_EQ("Test Regional", regions->getRegionAdjective("test_region"));
}