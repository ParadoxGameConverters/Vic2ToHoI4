#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "src/HOI4World/Factions/FactionGoals.h"


TEST(HoI4World_Factions_FactionGoals, FactionGoalsCanBeImported)
{
	HoI4::FactionGoals goals;
	goals.importFactionGoals(std::filesystem::path("Configurables") / "faction_goals.txt");

	std::stringstream emptyStream;
	const auto& theGoal = std::make_shared<HoI4::FactionGoal>("faction_goal_one", emptyStream);

	EXPECT_THAT(goals.getImportedGoals(),
		 testing::UnorderedElementsAre(testing::Pair("faction_goal_one", testing::Pointee(*theGoal))));
}