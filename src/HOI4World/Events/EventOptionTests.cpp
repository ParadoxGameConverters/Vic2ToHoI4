#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Events/EventOption.h"
#include <sstream>



TEST(HoI4World_Events_EventOptionTests, NameDefaultsToAbsent)
{
	const HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
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
	const HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = optionName\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, TriggerDefaultsToBlank)
{
	const HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, TriggerCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveTrigger("triggerText");

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\ttrigger = {\n";
	expectedOutput += "\t\t\ttriggerText\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, TriggerCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttrigger = {\n";
	input << "\t\t\ttriggerText\n";
	input << "\t\t}\n";
	input << "}";
	HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\ttrigger = {\n";
	expectedOutput += "\t\t\ttriggerText\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, AiChanceDefaultsToBlank)
{
	const HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
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
	const HoI4::EventOption theOption(input);

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tai_chance = { factor = 0 }\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksDefaultToEmpty)
{
	const HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveScriptBlock(
		 "TAG = {\n"
		 "\t\t\tadd_to_faction = NEW\n"
		 "\t\t}");

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tTAG = {\n";
	expectedOutput += "\t\t\tadd_to_faction = NEW\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, ScriptBlocksCanBeGivenRepeatedly)
{
	HoI4::EventOption theOption;
	theOption.giveScriptBlock(
		 "TAG = {\n"
		 "\t\t\tadd_to_faction = ONE\n"
		 "\t\t}");
	theOption.giveScriptBlock(
		 "TAG = {\n"
		 "\t\t\tadd_to_faction = TWO\n"
		 "\t\t}");

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
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
	expectedOutput += "\t\tTAG = {\n";
	expectedOutput += "\t\t\tadd_to_faction = NEW\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, HiddenEffectDefaultsToEmpty)
{
	const HoI4::EventOption theOption;

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventOptionTests, HiddenEffectCanBeGiven)
{
	HoI4::EventOption theOption;
	theOption.giveHiddenEffect(
		 "= {\n"
		 "\t\t\tnews_event = { id = news.42 }\n"
		 "\t\t}");

	std::stringstream actualOutput;
	actualOutput << theOption;

	std::string expectedOutput;
	expectedOutput += "\toption = {\n";
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
	expectedOutput += "\t\thidden_effect = {\n";
	expectedOutput += "\t\t\tnews_event = { id = news.42 }\n";
	expectedOutput += "\t\t}\n";
	expectedOutput += "\t}";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}