#include "V2World/Ai/AIStrategy.h"
#include "V2World/Ai/AIStrategyFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_AI_Strategy_Tests, TypeDefaultsToEmpty)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("", input);

	ASSERT_TRUE(newAiStrategy->getType().empty());
}


TEST(Vic2World_AI_Strategy_Tests, TypeCanBeSet)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("threat", input);

	ASSERT_EQ("threat", newAiStrategy->getType());
}


TEST(Vic2World_AI_Strategy_Tests, IdDefaultsToEmpty)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("", input);

	ASSERT_TRUE(newAiStrategy->getID().empty());
}


TEST(Vic2World_AI_Strategy_Tests, IdCanBeSet)
{
	std::stringstream input;
	input << "id=\"BAV\"";
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("threat", input);

	ASSERT_EQ("BAV", newAiStrategy->getID());
}


TEST(Vic2World_AI_Strategy_Tests, ProvIdDefaultsToZero)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("", input);

	ASSERT_EQ(0, newAiStrategy->getProvID());
}


TEST(Vic2World_AI_Strategy_Tests, ProvIdCanBeSet)
{
	std::stringstream input;
	input << "id=266";
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("conquer_prov", input);

	ASSERT_EQ(266, newAiStrategy->getProvID());
}


TEST(Vic2World_AI_Strategy_Tests, ValueDefaultsToZero)
{
	std::stringstream input;
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("", input);

	ASSERT_EQ(0, newAiStrategy->getValue());
}


TEST(Vic2World_AI_Strategy_Tests, ValueCanBeSet)
{
	std::stringstream input;
	input << "value=8";
	const auto newAiStrategy = Vic2::AIStrategy::Factory().importStrategy("conquer_prov", input);

	ASSERT_EQ(8, newAiStrategy->getValue());
}