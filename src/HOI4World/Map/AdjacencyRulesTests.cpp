#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/AdjacencyRules.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/V2World/States/StateBuilder.h"



TEST(HoI4World_Map_AdjacencyRules, DefaultAdjacencyRulesCanBeImported)
{
	auto adjacencyRules = HoI4::AdjacencyRules().getRules();

	EXPECT_FALSE(adjacencyRules.empty());
}