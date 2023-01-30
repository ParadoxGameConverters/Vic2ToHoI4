#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/SupplyNodes.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/StateCategoriesBuilder.h"
#include "src/Mappers/Provinces/ProvinceMapperBuilder.h"
#include "src/V2World/Provinces/Province.h"
#include "src/V2World/States/StateBuilder.h"
#include <gmock/gmock-matchers.h>



using HoI4::determineSupplyNodes;
using Mappers::ProvinceMapper;
using Vic2::State;



TEST(HoI4World_Map_SupplyNodes, SupplyNodesDefaultToNone)
{
	const auto supplyNodes = determineSupplyNodes({}, {});

	EXPECT_TRUE(supplyNodes.empty());
}


TEST(HoI4World_Map_SupplyNodes, SeaProvincesDoNotGetNodes)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 1, "TAG");
	theState.addProvince(1);
	theState.makeImpassable();
	const auto supplyNodes = determineSupplyNodes({{1, theState}}, {1});
	EXPECT_TRUE(supplyNodes.empty());
}

TEST(HoI4World_Map_SupplyNodes, provincesWithoutRailEndpointsDoNotGetNodes)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 1, "TAG");
	theState.addProvince(1);
	const auto supplyNodes = determineSupplyNodes({{1, theState}}, {});
	EXPECT_TRUE(supplyNodes.empty());
}


TEST(HoI4World_Map_SupplyNodes, SupplyNodesGetCreated)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 1, "TAG");
	theState.addProvince(1);
	const auto supplyNodes = determineSupplyNodes({{1, theState}}, {1});
	EXPECT_THAT(supplyNodes, testing::UnorderedElementsAre(1));
}

TEST(HoI4World_Map_SupplyNodes, CorrectNumberOfNodesAreCreated)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 1, "TAG");
	theState.addProvince(1);
	theState.addProvince(2);
	theState.addProvince(3);
	theState.addProvince(4);
	theState.addProvince(5);
	theState.addProvince(6);
	theState.addProvince(7);
	theState.addProvince(8);
	theState.addProvince(9);
	theState.addProvince(10);
	theState.addProvince(11);
	theState.addProvince(12);
	theState.addProvince(13);
	const auto supplyNodes = determineSupplyNodes({{1, theState}}, {1, 2, 3, 4});
	EXPECT_THAT(supplyNodes, testing::UnorderedElementsAreArray({1, 2}));
}