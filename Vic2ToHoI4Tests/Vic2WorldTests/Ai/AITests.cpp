#include "V2World/Ai/AI.h"
#include "V2World/Ai/AIFactory.h"
#include "V2World/Provinces/Province.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "gtest/gtest.h"



TEST(Vic2World_Vic2_AI_Tests, AiStrategiesDefaultToEmpty)
{
	std::stringstream input;
	const auto newVic2Ai = Vic2::AI::Factory().importAI(input);

	ASSERT_TRUE(newVic2Ai->getStrategies().empty());
}


TEST(Vic2World_Vic2_AI_Tests, AiStrategiesCanBeSet)
{
	std::stringstream input;
	input << "threat=\n";
	input << "{\n";
	input << "\tid=\"PSA\"\n";
	input << "\tvalue=30\n";
	input << "}\n";
	input << "antagonize=\n";
	input << "{\n";
	input << "\tid=\"PSB\"\n";
	input << "\tvalue=31\n";
	input << "}\n";
	input << "befriend=\n";
	input << "{\n";
	input << "\tid=\"PSC\"\n";
	input << "\tvalue=32\n";
	input << "}\n";
	input << "protect=\n";
	input << "{\n";
	input << "\tid=\"PSD\"\n";
	input << "\tvalue=33\n";
	input << "}\n";
	input << "rival=\n";
	input << "{\n";
	input << "\tid=\"PSE\"\n";
	input << "\tvalue=34\n";
	input << "}\n";
	const auto newVic2Ai = Vic2::AI::Factory().importAI(input);

	ASSERT_EQ(5, newVic2Ai->getStrategies().size());
	ASSERT_EQ("threat", newVic2Ai->getStrategies()[0].getType());
	ASSERT_EQ("PSA", newVic2Ai->getStrategies()[0].getID());
	ASSERT_EQ(30, newVic2Ai->getStrategies()[0].getValue());
	ASSERT_EQ("antagonize", newVic2Ai->getStrategies()[1].getType());
	ASSERT_EQ("PSB", newVic2Ai->getStrategies()[1].getID());
	ASSERT_EQ(31, newVic2Ai->getStrategies()[1].getValue());
	ASSERT_EQ("befriend", newVic2Ai->getStrategies()[2].getType());
	ASSERT_EQ("PSC", newVic2Ai->getStrategies()[2].getID());
	ASSERT_EQ(32, newVic2Ai->getStrategies()[2].getValue());
	ASSERT_EQ("protect", newVic2Ai->getStrategies()[3].getType());
	ASSERT_EQ("PSD", newVic2Ai->getStrategies()[3].getID());
	ASSERT_EQ(33, newVic2Ai->getStrategies()[3].getValue());
	ASSERT_EQ("rival", newVic2Ai->getStrategies()[4].getType());
	ASSERT_EQ("PSE", newVic2Ai->getStrategies()[4].getID());
	ASSERT_EQ(34, newVic2Ai->getStrategies()[4].getValue());
}


TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesDefaultToEmpty)
{
	std::stringstream input;
	const auto newVic2Ai = Vic2::AI::Factory().importAI(input);

	ASSERT_TRUE(newVic2Ai->getConquerStrategies().empty());
}


TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesCanBeSet)
{
	std::stringstream input;
	input << "conquer_prov=\n";
	input << "{\n";
	input << "\tid=278\n";
	input << "\tvalue=182\n";
	input << "}\n";
	const auto newVic2Ai = Vic2::AI::Factory().importAI(input);

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
	input << "\tvalue=2\n";
	input << "}\n";
	input << "conquer_prov=\n";
	input << "{\n";
	input << "\tid=43\n";
	input << "\tvalue=3\n";
	input << "}\n";
	input << "conquer_prov=\n";
	input << "{\n";
	input << "\tid=44\n";
	input << "\tvalue=7\n";
	input << "}\n";
	input << "conquer_prov=\n";
	input << "{\n";
	input << "\tid=45\n";
	input << "\tvalue=11\n";
	input << "}\n";
	auto newVic2Ai = Vic2::AI::Factory().importAI(input);

	const std::map<int, std::shared_ptr<Vic2::Province>> provinceMap{
		 {42, Vic2::Province::Builder().setNumber(42).setOwner("TAG").build()},
		 {43, Vic2::Province::Builder().setNumber(43).setOwner("TAG").build()},
		 {44, {}}};

	newVic2Ai->consolidateConquerStrategies(provinceMap);

	ASSERT_EQ(5, newVic2Ai->getConsolidatedStrategies().find("TAG")->second);
}