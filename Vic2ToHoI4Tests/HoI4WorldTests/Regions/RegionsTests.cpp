#include "HOI4World/Regions/Regions.h"
#include "HOI4World/Regions/RegionsFactory.h"
#include "gtest/gtest.h"



TEST(HoI4World_Regions_RegionsTests, ProvinceInUnmappedRegionsReturnsNullptr)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	ASSERT_EQ(std::nullopt, regions->getRegion(0));
}


TEST(HoI4World_Regions_RegionsTests, ProvinceInMappedRegionsReturnsRegion)
{
	const auto regions = HoI4::Regions::Factory().getRegions();

	ASSERT_EQ("test_region", regions->getRegion(42));
}