#include "V2World/Ai/AI.h"
#include "V2World/Ai/AIFactory.h"
#include "V2World/Provinces/Province.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "gtest/gtest.h"



TEST(Vic2World_Vic2_AI_Tests, AiStrategiesDefaultToEmpty)
{
	std::stringstream input;
	const auto newVic2Ai = Vic2::AI::Factory{}.importAI(input);

	ASSERT_TRUE(newVic2Ai->getStrategies().empty());
}


TEST(Vic2World_Vic2_AI_Tests, AiStrategiesSetWhenGivenInput)
{
	std::stringstream input;
	input << "rival=\n";
	input << "{\n";
	input << "\tid=\"PSA\"\n";
	input << "\tvalue=30\n";
	input << "}\n";
	const auto newVic2Ai = Vic2::AI::Factory{}.importAI(input);

	ASSERT_EQ(1, newVic2Ai->getStrategies().size());
	ASSERT_EQ("rival", newVic2Ai->getStrategies()[0].getType());
	ASSERT_EQ("PSA", newVic2Ai->getStrategies()[0].getID());
	ASSERT_EQ(30, newVic2Ai->getStrategies()[0].getValue());
}


TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesDefaultToEmpty)
{
	std::stringstream input;
	const auto newVic2Ai = Vic2::AI::Factory{}.importAI(input);

	ASSERT_TRUE(newVic2Ai->getConquerStrategies().empty());
}


TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesSetWhenGivenInput)
{
	std::stringstream input;
	input << "conquer_prov=\n";
	input << "{\n";
	input << "\tid=278\n";
	input << "\tvalue=182\n";
	input << "}\n";
	const auto newVic2Ai = Vic2::AI::Factory{}.importAI(input);

	ASSERT_EQ(1, newVic2Ai->getConquerStrategies().size());
	ASSERT_EQ("conquer_prov", newVic2Ai->getConquerStrategies()[0].getType());
	ASSERT_EQ(278, newVic2Ai->getConquerStrategies()[0].getProvID());
	ASSERT_EQ(182, newVic2Ai->getConquerStrategies()[0].getValue());
}


TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesProperlyConsolidated)
{
	std::stringstream input;
	input << "conquer_prov=\n";
	input << "{\n";
	input << "\tid=42\n";
	input << "\tvalue=182\n";
	input << "}\n";
	auto newVic2Ai = Vic2::AI::Factory{}.importAI(input);

	const std::map<int, std::shared_ptr<Vic2::Province>> provinceMap{
		 {42, Vic2::Province::Builder{}.setNumber(278).setOwner("TAG").build()}};

	newVic2Ai->consolidateConquerStrategies(provinceMap);

	ASSERT_EQ(182, newVic2Ai->getConsolidatedStrategies().find("TAG")->second);
}