#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Scorers/ScorerFactory.h"



TEST(HoI4World_Scorers_ScorerFactoryTests, NameCanBeSet)
{
	std::stringstream input;
	const auto scorer = HoI4::Scorer::Factory().getScorer("scorer_name", input);

	ASSERT_EQ("scorer_name", scorer->getName());
}


TEST(HoI4World_Scorers_ScorerFactoryTests, TargetsDefaultsToEmpty)
{
	std::stringstream input;
	const auto scorer = HoI4::Scorer::Factory().getScorer("scorer_name", input);

	ASSERT_TRUE(scorer->getTargets().empty());
}


TEST(HoI4World_Scorers_ScorerFactoryTests, TargetsCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\ttargets = { targets_dynamic = no }\n";
	input << "}";
	const auto scorer = HoI4::Scorer::Factory().getScorer("scorer_name", input);

	ASSERT_EQ("= { targets_dynamic = no }", scorer->getTargets());
}