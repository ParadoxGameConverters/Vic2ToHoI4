#include "src/HOI4World/Localisations/ArticleRules/ArticleRule.h"
#include "src/HOI4World/Localisations/ArticleRules/ArticleRuleBuilder.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Localisations_ArticleRules_ArticleRule, RuleDoesNotApplyToNonMatch)
{
	const auto rule = HoI4::ArticleRule::Builder().build();

	ASSERT_FALSE(rule->doesRuleApply("Non-matching String"));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRule, RuleDoesNotApplyToEmptyString)
{
	const auto rule = HoI4::ArticleRule::Builder().build();

	ASSERT_FALSE(rule->doesRuleApply(""));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRule, RuleAppliesToMachingString)
{
	const auto rule = HoI4::ArticleRule::Builder().setMatcher(std::regex(R"(The (.+))")).build();

	ASSERT_TRUE(rule->doesRuleApply("The Matching String"));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRule, RuleDoesNotUpdateNonMachingString)
{
	const auto rule = HoI4::ArticleRule::Builder().setMatcher(std::regex(R"(The (.+))")).setReplacement(R"($1)").build();

	ASSERT_EQ("Non-matching String", rule->applyRuleToText("Non-matching String"));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRule, RuleUpdatesMachingString)
{
	const auto rule = HoI4::ArticleRule::Builder().setMatcher(std::regex(R"(The (.+))")).setReplacement(R"($1)").build();

	ASSERT_EQ("Matching String", rule->applyRuleToText("The Matching String"));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRule, RuleUpdatesMachingEmptyString)
{
	const auto rule = HoI4::ArticleRule::Builder().setMatcher(std::regex("")).setReplacement("Foo").build();

	ASSERT_EQ("Foo", rule->applyRuleToText(""));
}