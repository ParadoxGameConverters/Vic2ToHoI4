#include "V2World/Wars/WarGoalFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_WarGoalFactoryTests, CBDefaultsToBlank)
{
	Vic2::WarGoalFactory theFactory;

	std::stringstream input;

	ASSERT_TRUE(theFactory.getCB(input).empty());
}


TEST(Vic2World_WarGoalFactoryTests, CBCanBeExtracted)
{
	Vic2::WarGoalFactory theFactory;

	std::stringstream input;
	input << "casus_belli = test_cb";

	ASSERT_EQ("test_cb", theFactory.getCB(input));
}


TEST(Vic2World_WarGoalFactoryTests, FactoryIsReset)
{
	Vic2::WarGoalFactory theFactory;

	std::stringstream input;
	input << "casus_belli = test_cb";
	theFactory.getCB(input);

	std::stringstream input2;

	ASSERT_TRUE(theFactory.getCB(input2).empty());
}