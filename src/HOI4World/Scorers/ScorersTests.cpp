#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Scorers/Scorers.h"



TEST(HoI4World_Scorers_Scorers, ScorersCanBeUpdated)
{
	HoI4::Scorer scorer;
	scorer.setName("$IDEOLOGY_major_scorer");

	HoI4::Scorers scorers;
	scorers.giveScorer(std::move(scorer));

	scorers.updateScorers({"democratic"});
	ASSERT_TRUE(scorers.getCustomizedScorers().find("democratic_major_scorer") != scorers.getCustomizedScorers().end());
}