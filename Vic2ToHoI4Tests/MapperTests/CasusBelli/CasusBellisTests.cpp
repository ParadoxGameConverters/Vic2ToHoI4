#include "Mappers/CasusBelli/CasusBellis.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(CasusBellisTests, UnmatchedCasusBelliGoesToDefault)
{
	const auto casusBellis = Mappers::CasusBellis({});

	EXPECT_EQ(casusBellis.getWarGoalFromCasusBelli("unmatched_cb"), "topple_government");
}


TEST(CasusBellisTests, MatchedCasusBelliGivesMatchingWarGoal)
{
	const auto casusBellis =
		 Mappers::CasusBellis(std::unordered_map<std::string, std::string>{{"matched_cb", "matching_war_goal"}});

	EXPECT_EQ(casusBellis.getWarGoalFromCasusBelli("matched_cb"), "matching_war_goal");
}