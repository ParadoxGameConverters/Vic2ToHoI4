#include "src/Mappers/CasusBelli/CasusBellis.h"
#include "src/Mappers/CasusBelli/CasusBellisFactory.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(Mappers_CasusBelli_CasusBellisTests, UnmatchedCasusBelliGoesToDefault)
{
	const auto casusBellis = Mappers::CasusBellis({});

	EXPECT_EQ(casusBellis.getWarGoalFromCasusBelli("unmatched_cb"), "topple_government");
}


TEST(Mappers_CasusBelli_CasusBellisTests, MatchedCasusBelliGivesMatchingWarGoal)
{
	const auto casusBellis =
		 Mappers::CasusBellis(std::unordered_map<std::string, std::string>{{"matched_cb", "matching_war_goal"}});

	EXPECT_EQ(casusBellis.getWarGoalFromCasusBelli("matched_cb"), "matching_war_goal");
}


TEST(Mappers_CasusBelli_CasusBellisTests, CasusBellisCanBeImported)
{
	const auto casusBellis = Mappers::CasusBellisFactory{}.importCasusBellis();
	EXPECT_EQ(casusBellis->getWarGoalFromCasusBelli("demand_concession_casus_belli"), "take_state");
}