#include "V2World/Ai/AIStrategy.h"
#include "V2World/Ai/AIStrategyFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_AI_Strategy_Tests, TypeNotSetWhenNotInitialized)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("", input);

	ASSERT_TRUE(newAiStrategy->getType().empty());
}


TEST(Vic2World_AI_Strategy_Tests, TypeSetWhenInitialized)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("threat", input);

	ASSERT_EQ("threat", newAiStrategy->getType());
}


TEST(Vic2World_AI_Strategy_Tests, IdNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("", input);

	ASSERT_TRUE(newAiStrategy->getID().empty());
}


TEST(Vic2World_AI_Strategy_Tests, IdSetWhenGivenInput)
{
	std::stringstream input;
	input << "id=\"BAV\"";
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("threat", input);

	ASSERT_EQ("BAV", newAiStrategy->getID());
}


TEST(Vic2World_AI_Strategy_Tests, ProvIDNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("", input);

	ASSERT_EQ(0, newAiStrategy->getProvID());
}


TEST(Vic2World_AI_Strategy_Tests, ProvIDSetWhenGivenInput)
{
	std::stringstream input;
	input << "id=266";
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("conquer_prov", input);

	ASSERT_EQ(266, newAiStrategy->getProvID());
}


TEST(Vic2World_AI_Strategy_Tests, ValueNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("", input);

	ASSERT_EQ(0, newAiStrategy->getValue());
}


TEST(Vic2World_AI_Strategy_Tests, ValueSetWhenGivenInput)
{
	std::stringstream input;
	input << "value=8";
	const auto newAiStrategy = Vic2::AIStrategy::Factory{}.importStrategy("conquer_prov", input);

	ASSERT_EQ(8, newAiStrategy->getValue());
}