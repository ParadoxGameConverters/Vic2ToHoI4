#include "../Vic2ToHoI4/Source/V2World/Wars/WarFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_WarTests: public testing::Test
{
  protected:
	Vic2World_WarTests() = default;

	Vic2::War::Factory warFactory;
};



TEST_F(Vic2World_WarTests, OriginalAttackerDefaultsToBlank)
{
	std::stringstream input;

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getOriginalAttacker(), "");
}


TEST_F(Vic2World_WarTests, OriginalAttackerCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_attacker=\"TAG\"\n";
	input << "}";

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getOriginalAttacker(), "TAG");
}


TEST_F(Vic2World_WarTests, AttackersDefaultToEmpty)
{
	std::stringstream input;

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getAttackers().size(), 0);
}


TEST_F(Vic2World_WarTests, AttackersCanBeAdded)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tattacker=\"TAG\"\n";
	input << "\tattacker=\"TWO\"\n";
	input << "}";

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getAttackers().size(), 2);
	ASSERT_EQ(theWar.getAttackers().count("TAG"), 1);
	ASSERT_EQ(theWar.getAttackers().count("TWO"), 1);
}


TEST_F(Vic2World_WarTests, OriginalDefenderDefaultsToBlank)
{
	std::stringstream input;

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getOriginalDefender(), "");
}


TEST_F(Vic2World_WarTests, OriginalDefenderCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_defender=\"TAG\"\n";
	input << "}";

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getOriginalDefender(), "TAG");
}


TEST_F(Vic2World_WarTests, DefendersDefaultToEmpty)
{
	std::stringstream input;

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getDefenders().size(), 0);
}


TEST_F(Vic2World_WarTests, DefendersCanBeAdded)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tdefender=\"TAG\"\n";
	input << "\tdefender=\"TWO\"\n";
	input << "}";

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getDefenders().size(), 2);
	ASSERT_EQ(theWar.getDefenders().count("TAG"), 1);
	ASSERT_EQ(theWar.getDefenders().count("TWO"), 1);
}


TEST_F(Vic2World_WarTests, CBDefaultsToBlank)
{
	std::stringstream input;

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getCB(), "");
}


TEST_F(Vic2World_WarTests, CBCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_wargoal={\n";
	input << "\t\tcasus_belli=\"theCB\"\n";
	input << "\t}\n";
	input << "}";

	const auto theWar = *warFactory.getWar(input);

	ASSERT_EQ(theWar.getCB(), "theCB");
}