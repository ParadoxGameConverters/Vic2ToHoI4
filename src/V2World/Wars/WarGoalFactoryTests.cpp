#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Wars/WarGoalFactory.h"
#include <sstream>



TEST(Vic2World_WarGoalFactoryTests, DefaultsAreBlanks)
{
	Vic2::WarGoalFactory theFactory;

	std::stringstream input;
	const auto warGoal = theFactory.getWarGoal(input);

	EXPECT_TRUE(warGoal.casusBelli.empty());
	EXPECT_EQ(warGoal.province, std::nullopt);
}


TEST(Vic2World_WarGoalFactoryTests, CasusBelliCanBeSet)
{
	Vic2::WarGoalFactory theFactory;

	std::stringstream input;
	input << "casus_belli = test_cb";
	const auto warGoal = theFactory.getWarGoal(input);

	EXPECT_EQ(warGoal.casusBelli, "test_cb");
}


TEST(Vic2World_WarGoalFactoryTests, ProvinceCanBeSet)
{
	Vic2::WarGoalFactory theFactory;

	std::stringstream input;
	input << "state_province_id = 42";
	const auto warGoal = theFactory.getWarGoal(input);

	ASSERT_TRUE(warGoal.province.has_value());
	EXPECT_EQ(*warGoal.province, 42);
}