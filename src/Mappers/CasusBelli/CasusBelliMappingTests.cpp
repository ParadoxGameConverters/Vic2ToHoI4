#include "Mappers/CasusBelli/CasusBelliMapping.h"
#include "Mappers/CasusBelli/CasusBelliMappingFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_CasusBelli_CasusBelliMappingTests, DefaultsAreEmpty)
{
	std::stringstream input;
	const auto casusBelli = Mappers::CasusBelliMappingFactory{}.importCasusBelli(input);

	EXPECT_TRUE(casusBelli.cbs_.empty());
	EXPECT_TRUE(casusBelli.warGoal_.empty());
}


TEST(Mappers_CasusBelli_CasusBelliMappingTests, CBsCanBeSet)
{
	std::stringstream input;
	input << "vic = test_cb_one vic = test_cb_two";
	const auto casusBelli = Mappers::CasusBelliMappingFactory{}.importCasusBelli(input);

	EXPECT_THAT(casusBelli.cbs_, testing::UnorderedElementsAre("test_cb_one", "test_cb_two"));
}


TEST(Mappers_CasusBelli_CasusBelliMappingTests, WarGoalCanBeSet)
{
	std::stringstream input;
	input << "hoi = test_war_goal";
	const auto casusBelli = Mappers::CasusBelliMappingFactory{}.importCasusBelli(input);

	EXPECT_EQ(casusBelli.warGoal_, "test_war_goal");
}