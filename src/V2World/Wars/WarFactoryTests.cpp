#include "src/V2World/Wars/WarFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <gmock/gmock-matchers.h>
#include <sstream>



class Vic2World_WarTests: public testing::Test
{
  protected:
	Vic2World_WarTests() = default;

	Vic2::War::Factory warFactory;
};



TEST_F(Vic2World_WarTests, DefaultsAreAppropriate)
{
	std::stringstream input;

	const auto theWar = warFactory.getWar(input);

	EXPECT_TRUE(theWar.getOriginalAttacker().empty());
	EXPECT_EQ(theWar.getAttackers().size(), 0);
	EXPECT_TRUE(theWar.getOriginalDefender().empty());
	EXPECT_TRUE(theWar.getDefenders().empty());
	EXPECT_TRUE(theWar.getCasusBelli().empty());
	EXPECT_FALSE(theWar.getProvince().has_value());
}


TEST_F(Vic2World_WarTests, OriginalAttackerCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_attacker=\"TAG\"\n";
	input << "}";

	const auto theWar = warFactory.getWar(input);

	EXPECT_EQ(theWar.getOriginalAttacker(), "TAG");
}


TEST_F(Vic2World_WarTests, AttackersCanBeAdded)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tattacker=\"TAG\"\n";
	input << "\tattacker=\"TWO\"\n";
	input << "}";

	const auto theWar = warFactory.getWar(input);

	EXPECT_THAT(theWar.getAttackers(), testing::ElementsAre("TAG", "TWO"));
}


TEST_F(Vic2World_WarTests, OriginalDefenderCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_defender=\"TAG\"\n";
	input << "}";

	const auto theWar = warFactory.getWar(input);

	EXPECT_EQ(theWar.getOriginalDefender(), "TAG");
}


TEST_F(Vic2World_WarTests, DefendersCanBeAdded)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tdefender=\"TAG\"\n";
	input << "\tdefender=\"TWO\"\n";
	input << "}";

	const auto theWar = warFactory.getWar(input);

	EXPECT_THAT(theWar.getDefenders(), testing::ElementsAre("TAG", "TWO"));
}


TEST_F(Vic2World_WarTests, CasusBelliCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_wargoal={\n";
	input << "\t\tcasus_belli=\"theCB\"\n";
	input << "\t}\n";
	input << "}";

	const auto theWar = warFactory.getWar(input);

	EXPECT_EQ(theWar.getCasusBelli(), "theCB");
}


TEST_F(Vic2World_WarTests, ProvinceCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_wargoal={\n";
	input << "\t\tstate_province_id=42\n";
	input << "\t}\n";
	input << "}";

	const auto theWar = warFactory.getWar(input);

	ASSERT_TRUE(theWar.getProvince().has_value());
	EXPECT_EQ(*theWar.getProvince(), 42);
}