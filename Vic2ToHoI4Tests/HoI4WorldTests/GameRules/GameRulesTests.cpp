#include "HOI4World/GameRules/GameRules.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_GameRules_GameRulesTests, RulesDefaultToEmpty)
{
	const HoI4::GameRules rules({});

	ASSERT_TRUE(rules.getGameRules().empty());
}


TEST(HoI4World_GameRules_GameRulesTests, RulesDefaultParseToEmpty)
{
	const auto rules = HoI4::GameRules::Parser().parseRulesFile("GameRulesEmpty.txt");

	ASSERT_TRUE(rules.getGameRules().empty());
}


TEST(HoI4World_GameRules_GameRulesTests, RulesCanBeAdded)
{
	const HoI4::GameRules rules({HoI4::GameRule("rule_1", "", std::nullopt, "", "", {}),
		 HoI4::GameRule("rule_2", "", std::nullopt, "", "", {})});

	const auto& theRules = rules.getGameRules();
	ASSERT_EQ(2, theRules.size());
}


TEST(HoI4World_GameRules_GameRulesTests, RulesCanBeParsed)
{
	const auto rules = HoI4::GameRules::Parser().parseRulesFile("GameRules.txt");

	const auto& theRules = rules.getGameRules();
	ASSERT_EQ(5, theRules.size());
}


TEST(HoI4World_GameRules_GameRulesTests, RulesCanBeRemoved)
{
	auto rules = HoI4::GameRules::Parser().parseRulesFile("GameRules.txt");
	rules.updateRules();

	const auto& theRules = rules.getGameRules();
	ASSERT_EQ(2, theRules.size());
}