#include "../Vic2ToHoI4/Source/V2World/Ai/AIStrategy.h"
#include "gtest/gtest.h"

TEST(Vic2World_AI_Strategy_Tests, TypeNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy("", input);

	ASSERT_TRUE(newAiStrategy.getType().empty());
}


TEST(Vic2World_AI_Strategy_Tests, TypeSetWhenGivenInput)
{
	std::stringstream input;
	input << "\t\tthreat=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=\"BAV\"\n";
	input << "\t\t\tvalue=400\n";
	input << "\t\t}\n";
	const auto newAiStrategy = Vic2::AIStrategy("threat", input);

	ASSERT_EQ("threat", newAiStrategy.getType());
}

TEST(Vic2World_AI_Strategy_Tests, IdNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy("", input);

	ASSERT_TRUE(newAiStrategy.getID().empty());
}


TEST(Vic2World_AI_Strategy_Tests, IdSetWhenGivenInput)
{
	std::stringstream input;
	input << "\t\tthreat=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=\"BAV\"\n";
	input << "\t\t\tvalue=400\n";
	input << "\t\t}\n";
	const auto newAiStrategy = Vic2::AIStrategy("threat", input);

	ASSERT_EQ("BAV", newAiStrategy.getID());
}

TEST(Vic2World_AI_Strategy_Tests, ProvIDNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy("", input);

	ASSERT_EQ(0, newAiStrategy.getProvID());
}


TEST(Vic2World_AI_Strategy_Tests, ProvIDSetWhenGivenInput)
{
	std::stringstream input;
	input << "\t\tconquer_prov=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=266\n";
	input << "\t\t\tvalue=8\n";
	input << "\t\t}\n";
	const auto newAiStrategy = Vic2::AIStrategy("conquer_prov", input);

	ASSERT_EQ(266, newAiStrategy.getProvID());
}

TEST(Vic2World_AI_Strategy_Tests, ValueNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy("", input);

	ASSERT_EQ(0, newAiStrategy.getValue());
}


TEST(Vic2World_AI_Strategy_Tests, ValueSetWhenGivenInput)
{
	std::stringstream input;
	input << "\t\tconquer_prov=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=266\n";
	input << "\t\t\tvalue=8\n";
	input << "\t\t}\n";
	const auto newAiStrategy = Vic2::AIStrategy("conquer_prov", input);

	ASSERT_EQ(8, newAiStrategy.getValue());
}
