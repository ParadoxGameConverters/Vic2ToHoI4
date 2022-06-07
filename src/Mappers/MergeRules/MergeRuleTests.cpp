#include "src/Configuration.h"
#include "src/Mappers/MergeRules/MergeRule.h"
#include "src/Mappers/MergeRules/MergeRuleFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_MergeRules_MergeRuleTests, IsEnabledDefaultsToFalse)
{
	std::stringstream input;

	const auto mergeRule = Mappers::MergeRule::Factory().importMergeRule(input);

	ASSERT_FALSE(mergeRule->isEnabled());
}


TEST(Mappers_MergeRules_MergeRuleTests, RuleCanBeEnabled)
{
	std::stringstream input;
	input << "merge = yes";

	const auto mergeRule = Mappers::MergeRule::Factory().importMergeRule(input);

	ASSERT_TRUE(mergeRule->isEnabled());
}


TEST(Mappers_MergeRules_MergeRuleTests, MasterDefaultsToEmpty)
{
	std::stringstream input;

	const auto mergeRule = Mappers::MergeRule::Factory().importMergeRule(input);

	ASSERT_TRUE(mergeRule->getMaster().empty());
}


TEST(Mappers_MergeRules_MergeRuleTests, MasterCanBeSet)
{
	std::stringstream input;
	input << "master = TAG";

	const auto mergeRule = Mappers::MergeRule::Factory().importMergeRule(input);

	ASSERT_EQ("TAG", mergeRule->getMaster());
}


TEST(Mappers_MergeRules_MergeRuleTests, SlavesDefaultsToEmpty)
{
	std::stringstream input;

	const auto mergeRule = Mappers::MergeRule::Factory().importMergeRule(input);

	ASSERT_TRUE(mergeRule->getSlaves().empty());
}


TEST(Mappers_MergeRules_MergeRuleTests, SlavesCanBeSet)
{
	std::stringstream input;
	input << "slave = TAG\n";
	input << "slave = TWO\n";

	const auto mergeRule = Mappers::MergeRule::Factory().importMergeRule(input);

	ASSERT_EQ(2, mergeRule->getSlaves().size());
	ASSERT_EQ("TAG", mergeRule->getSlaves()[0]);
	ASSERT_EQ("TWO", mergeRule->getSlaves()[1]);
}