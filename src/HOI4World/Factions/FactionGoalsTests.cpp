#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "src/HOI4World/Factions/FactionGoals.h"


TEST(HoI4World_Factions_FactionGoals, FactionGoalsCanBeImported)
{
	HoI4::FactionGoals goals;

	std::stringstream emptyStream;
	const auto& goalOne = HoI4::FactionGoal("faction_goal_one", emptyStream);
	const auto& goalTwo = HoI4::FactionGoal("faction_goal_two", emptyStream);

	EXPECT_THAT(goals.getImportedGoals(),
		 testing::UnorderedElementsAre(
			  testing::Pair("ideology", testing::ElementsAre(testing::Pointee(goalOne), testing::Pointee(goalTwo)))));
}


TEST(HoI4World_Factions_FactionGoals, VariablesCanBeImported)
{
	HoI4::FactionGoals goals;

	EXPECT_THAT(goals.getVariables(), testing::UnorderedElementsAre(testing::Pair("@variable", 0.75)));
}