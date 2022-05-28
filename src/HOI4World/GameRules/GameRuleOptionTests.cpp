#include "HOI4World/GameRules/GameRuleOption.h"
#include "OutHoi4/GameRules/OutGameRuleOption.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_GameRules_GameRuleOptionTests, DefaultsAreEmpty)
{
	HoI4::GameRuleOption option(false, "", "", "", std::nullopt);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, IsDefaultCanBeSet)
{
	HoI4::GameRuleOption option(true, "OPTION_NAME", "", "", std::nullopt);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\tdefault = {\n";
	expectedOutput << "\t\tname = OPTION_NAME\n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, IsDefaultCanBeParsed)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tname = OPTION_NAME\n";
	input << "\t}";
	auto option = HoI4::GameRuleOption::Parser().parseOption("default", input);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\tdefault = {\n";
	expectedOutput << "\t\tname = OPTION_NAME\n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, NameCanBeSet)
{
	HoI4::GameRuleOption option(false, "OPTION_NAME", "", "", std::nullopt);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = OPTION_NAME\n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, NameCanBeParsed)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tname = OPTION_NAME\n";
	input << "\t}";
	auto option = HoI4::GameRuleOption::Parser().parseOption("option", input);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = OPTION_NAME\n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, TextCanBeSet)
{
	HoI4::GameRuleOption option(false, "", "OPTION_TEXT", "", std::nullopt);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = OPTION_TEXT\n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, TextCanBeParsed)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttext = OPTION_TEXT\n";
	input << "\t}";
	auto option = HoI4::GameRuleOption::Parser().parseOption("option", input);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = OPTION_TEXT\n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, DescriptionCanBeSet)
{
	HoI4::GameRuleOption option(false, "", "", "OPTION_DESC", std::nullopt);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = OPTION_DESC\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, DescriptionCanBeParsed)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tdesc = OPTION_DESC\n";
	input << "\t}";
	auto option = HoI4::GameRuleOption::Parser().parseOption("option", input);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = OPTION_DESC\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, AllowAchievementsCanBeSetToYes)
{
	HoI4::GameRuleOption option(false, "", "", "", true);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t\tallow_achievements = yes\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, AllowAchievementsCanBeParsedToYes)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tallow_achievements = yes\n";
	input << "\t}";
	auto option = HoI4::GameRuleOption::Parser().parseOption("option", input);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t\tallow_achievements = yes\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, AllowAchievementsCanBeSetToNo)
{
	HoI4::GameRuleOption option(false, "", "", "", false);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t\tallow_achievements = no\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_GameRules_GameRuleOptionTests, AllowAchievementsCanBeParsedToNo)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tallow_achievements = no\n";
	input << "\t}";
	auto option = HoI4::GameRuleOption::Parser().parseOption("option", input);

	std::stringstream output;
	output << option;

	std::stringstream expectedOutput;
	expectedOutput << "\toption = {\n";
	expectedOutput << "\t\tname = \n";
	expectedOutput << "\t\ttext = \n";
	expectedOutput << "\t\tdesc = \n";
	expectedOutput << "\t\tallow_achievements = no\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}