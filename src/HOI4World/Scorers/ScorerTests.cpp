#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Scorers/Scorer.h"



TEST(HoI4World_Scorers_Scorer, CanMakeCustomizedCopyOfScorer)
{
	HoI4::Scorer scorer;
	scorer.setName("$IDEOLOGY_major_scorer");
	scorer.setTargets("= { score = { modifier = { NOT = { has_government = $IDEOLOGY }}}}");

	const auto& customScorer = scorer.makeCustomizedCopy("communism");
	EXPECT_EQ("communist_major_scorer", customScorer->getName());
	EXPECT_EQ("= { score = { modifier = { NOT = { has_government = communism }}}}", customScorer->getTargets());
}