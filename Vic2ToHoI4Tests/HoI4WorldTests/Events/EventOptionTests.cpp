#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/Events/EventOption.h"
#include <sstream>



TEST(HoI4World_Events_EventOptionTests, NameDefaultsToBlank)
{
	HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, NameCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveName("optionName");

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = optionName\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, NameCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = optionName\n";
	input << "}";
	HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = optionName\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, AiChanceDefaultsToBlank)
{
	HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, AiChanceCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveAiChance("= { factor = 0 }");

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\tai_chance = { factor = 0 }\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, AiChanceCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tai_chance = { factor = 0 }\n";
	input << "}";
	HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\tai_chance = { factor = 0 }\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksDefaultToEmpty)
{
	HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveScriptBlock("TAG = {\n" \
		"\t\t\tadd_to_faction = NEW\n" \
		"\t\t}"
	);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\tTAG = {\n";
	expectedOutput += "\t\t\tadd_to_faction = NEW\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksCanBeGivenRepeatedly)
{
	HoI4::EventOption theOption;
	theOption.giveScriptBlock("TAG = {\n" \
		"\t\t\tadd_to_faction = ONE\n" \
		"\t\t}"
	);
	theOption.giveScriptBlock("TAG = {\n" \
		"\t\t\tadd_to_faction = TWO\n" \
		"\t\t}"
	);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\tTAG = {\n";
	expectedOutput += "\t\t\tadd_to_faction = ONE\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t\tTAG = {\n";
	expectedOutput += "\t\t\tadd_to_faction = TWO\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tTAG = {\n";
	input << "\t\t\tadd_to_faction = NEW\n";
	input << "\t\t}";
	input << "}";
	HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\tTAG = {\n";
	expectedOutput += "\t\t\tadd_to_faction = NEW\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, HiddenEffectDefaultsToEmpty)
{
	HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, HiddenEffectCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveHiddenEffect(
		"= {\n" \
		"\t\t\tnews_event = { id = news.42 }\n" \
		"\t\t}"
	);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\thidden_effect = {\n";
	expectedOutput += "\t\t\tnews_event = { id = news.42 }\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, HiddenEffectCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\thidden_effect = {\n";
	input << "\t\t\tnews_event = { id = news.42 }\n";
	input << "\t\t}\n";
	input << "}";
	HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = \n";
	expectedOutput += "\t\thidden_effect = {\n";
	expectedOutput += "\t\t\tnews_event = { id = news.42 }\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}