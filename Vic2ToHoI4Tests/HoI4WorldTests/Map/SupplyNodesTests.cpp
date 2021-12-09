#include "HOI4World/Map/SupplyNodes.h"
#include "Mappers/Provinces/ProvinceMapperBuilder.h"
#include "V2World/Provinces/Province.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>



using HoI4::determineSupplyNodes;
using Mappers::ProvinceMapper;
using Vic2::Province;



TEST(HoI4World_Map_SupplyNodes, SupplyNodesDefaultToNone)
{
	const auto supplyNodes = determineSupplyNodes({}, *ProvinceMapper::Builder{}.Build());

	EXPECT_TRUE(supplyNodes.empty());
}


TEST(HoI4World_Map_SupplyNodes, SeaProvincesDoNotGetNodes)
{
	const auto supplyNodes =
		 determineSupplyNodes({{1, Province::Builder{}.setNumber(1).build()}}, *ProvinceMapper::Builder{}.Build());

	EXPECT_TRUE(supplyNodes.empty());
}


TEST(HoI4World_Map_SupplyNodes, UnmappedProvincesDoNotGetNodes)
{
	const auto supplyNodes = determineSupplyNodes({{1, Province::Builder{}.setNumber(1).setIsLand().build()}},
		 *ProvinceMapper::Builder{}.Build());

	EXPECT_TRUE(supplyNodes.empty());
}


TEST(HoI4World_Map_SupplyNodes, SupplyNodesGetCreated)
{
	const auto supplyNodes = determineSupplyNodes({{1, Province::Builder{}.setNumber(1).setIsLand().build()}},
		 *ProvinceMapper::Builder{}.addVic2ToHoI4ProvinceMap(1, {10}).Build());

	EXPECT_THAT(supplyNodes, testing::UnorderedElementsAre(10));
}