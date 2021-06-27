#include "Mappers/CasusBelli/CasusBelli.h"
#include "Mappers/CasusBelli/CasusBelliFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_CasusBelli_CasusBelliTests, DefaultsAreEmpty)
{
	std::stringstream input;
	const auto casusBelli = Mappers::CasusBelliFactory{}.importCasusBelli(input);

	EXPECT_TRUE(casusBelli.getCBs().empty());
	EXPECT_TRUE(casusBelli.getWarGoal().empty());
}


TEST(Mappers_CasusBelli_CasusBelliTests, CBsCanBeSet)
{
	std::stringstream input;
	input << "vic = test_cb_one vic = test_cb_two";
	const auto casusBelli = Mappers::CasusBelliFactory{}.importCasusBelli(input);

	EXPECT_THAT(casusBelli.getCBs(), testing::UnorderedElementsAre("test_cb_one", "test_cb_two"));
}


TEST(Mappers_CasusBelli_CasusBelliTests, WarGoalCanBeSet)
{
	std::stringstream input;
	input << "hoi = test_war_goal";
	const auto casusBelli = Mappers::CasusBelliFactory{}.importCasusBelli(input);

	EXPECT_EQ(casusBelli.getWarGoal(), "test_war_goal");
}