#include "src/HOI4World/GameRules/GameRule.h"
#include "src/OutHoi4/GameRules/OutGameRule.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_GameRules_GameRuleTests, DefaultsAreEmpty)
{
	HoI4::GameRule rule("", "", std::nullopt, "", std::nullopt, {});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, KeyCanBeSet)
{
	HoI4::GameRule rule("test_rule", "", std::nullopt, "", std::nullopt, {});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << "test_rule = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
	ASSERT_EQ("test_rule", rule.getKey());
}


TEST(HoI4World_GameRules_GameRuleTests, KeyCanBeParsed)
{
	std::stringstream input;
	auto rule = HoI4::GameRule::Parser().parseRule("test_rule", input);

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << "test_rule = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
	ASSERT_EQ("test_rule", rule.getKey());
}


TEST(HoI4World_GameRules_GameRuleTests, NameCanBeSet)
{
	HoI4::GameRule rule("", "RULE_TEST", std::nullopt, "", std::nullopt, {});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"RULE_TEST\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, NameCanBeParsed)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = RULE_TEST\n";
	input << "}";
	auto rule = HoI4::GameRule::Parser().parseRule("", input);

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"RULE_TEST\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, RequiredDlcCanBeSet)
{
	HoI4::GameRule rule("", "", "Test Required DLC", "", std::nullopt, {});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\trequired_dlc = \"Test Required DLC\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, RequiredDlcCanBeParsed)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_dlc = \"Test Required DLC\"\n";
	input << "}";
	auto rule = HoI4::GameRule::Parser().parseRule("", input);

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\trequired_dlc = \"Test Required DLC\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, GroupCanBeSet)
{
	HoI4::GameRule rule("", "", std::nullopt, "RULE_GROUP_TEST", std::nullopt, {});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"RULE_GROUP_TEST\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, GroupCanBeParsed)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tgroup = \"RULE_GROUP_TEST\"\n";
	input << "}";
	auto rule = HoI4::GameRule::Parser().parseRule("", input);

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"RULE_GROUP_TEST\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, IconCanBeSet)
{
	HoI4::GameRule rule("", "", std::nullopt, "", "GFX_test", {});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "\ticon = \"GFX_test\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, IconCanBeParsed)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ticon = \"GFX_test\"\n";
	input << "}";
	auto rule = HoI4::GameRule::Parser().parseRule("", input);

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "\ticon = \"GFX_test\"\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, OptionsCanBeSet)
{
	HoI4::GameRule rule("",
		 "",
		 std::nullopt,
		 "",
		 std::nullopt,
		 std::vector<HoI4::GameRuleOption>{HoI4::GameRuleOption{false, "", "", "", std::nullopt},
			  HoI4::GameRuleOption{true, "", "", "", std::nullopt}});

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tdefault = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleTests, OptionsCanBeParsed)
{
	std::stringstream input;
	input << " = {\n";
	input << "\toption= {\n";
	input << "\t}";
	input << "\tdefault= {\n";
	input << "\t}";
	input << "}";
	auto rule = HoI4::GameRule::Parser().parseRule("", input);

	std::stringstream output;
	output << rule;

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "\tname = \"\"\n";
	expectedOutput << "\tgroup = \"\"\n";
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tdefault = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}