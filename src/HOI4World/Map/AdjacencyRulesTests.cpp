#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/AdjacencyRules.h"
#include "src/HOI4World/States/HoI4State.h"



TEST(HoI4World_Map_AdjacencyRules, DefaultAdjacencyRulesCanBeImported)
{
	const std::map<int, HoI4::State> states;
	auto adjacencyRules = HoI4::AdjacencyRules(states).getRules();

	EXPECT_FALSE(adjacencyRules.empty());
}