#include "V2World/Wars/WarBuilder.h"
#include "gtest/gtest.h"



TEST(Vic2World_WarBuilderTests, OriginalAttackerDefaultsToEmpty)
{
	const auto war = Vic2::War::Builder().build();
	ASSERT_TRUE(war->getOriginalAttacker().empty());
}


TEST(Vic2World_WarBuilderTests, OriginalAttackerCanBeSet)
{
	const auto war = Vic2::War::Builder().setOriginalAttacker("ATT").build();
	ASSERT_EQ("ATT", war->getOriginalAttacker());
}


TEST(Vic2World_WarBuilderTests, AttackersDefaultToEmpty)
{
	const auto war = Vic2::War::Builder().build();
	ASSERT_TRUE(war->getAttackers().empty());
}


TEST(Vic2World_WarBuilderTests, AttackersCanBeSet)
{
	const auto war = Vic2::War::Builder().setAttackers({"AT1", "AT2"}).build();

	const auto expected = std::set<std::string>{"AT1", "AT2"};
	ASSERT_EQ(expected, war->getAttackers());
}


TEST(Vic2World_WarBuilderTests, OriginalDefenderDefaultsToEmpty)
{
	const auto war = Vic2::War::Builder().build();
	ASSERT_TRUE(war->getOriginalDefender().empty());
}


TEST(Vic2World_WarBuilderTests, OriginalDefenderCanBeSet)
{
	const auto war = Vic2::War::Builder().setOriginalDefender("ATT").build();
	ASSERT_EQ("ATT", war->getOriginalDefender());
}


TEST(Vic2World_WarBuilderTests, DefendersDefaultToEmpty)
{
	const auto war = Vic2::War::Builder().build();
	ASSERT_TRUE(war->getDefenders().empty());
}


TEST(Vic2World_WarBuilderTests, DefendersCanBeSet)
{
	const auto war = Vic2::War::Builder().setDefenders({"AT1", "AT2"}).build();

	const auto expected = std::set<std::string>{"AT1", "AT2"};
	ASSERT_EQ(expected, war->getDefenders());
}


TEST(Vic2World_WarBuilderTests, CBDefaultsToEmpty)
{
	const auto war = Vic2::War::Builder().build();
	ASSERT_TRUE(war->getCB().empty());
}


TEST(Vic2World_WarBuilderTests, CBCanBeSet)
{
	const auto war = Vic2::War::Builder().setCB("test_cb").build();
	ASSERT_EQ("test_cb", war->getCB());
}