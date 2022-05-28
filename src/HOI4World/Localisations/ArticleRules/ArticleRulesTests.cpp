#include "HOI4World/Localisations/ArticleRules/ArticleRuleBuilder.h"
#include "HOI4World/Localisations/ArticleRules/ArticleRules.h"
#include "HOI4World/Localisations/ArticleRules/ArticleRulesBuilder.h"
#include "gtest/gtest.h"



TEST(HoI4World_Localisations_ArticleRules_ArticleRules, NonMatchingLanguageDoesNotUpdateText)
{
	const auto rule = HoI4::ArticleRules::Builder().build();

	ASSERT_EQ("The Original Text", rule->updateArticles("non-language", "The Original Text"));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRules, NonMatchingRuleDoesNotUpdateText)
{
	const auto rule = HoI4::ArticleRules::Builder().addRules("english", {}).build();

	ASSERT_EQ("The Original Text", rule->updateArticles("english", "The Original Text"));
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRules, MatchingRuleUpdatesText)
{
	const auto rule =
		 HoI4::ArticleRules::Builder()
			  .addRules("english",
					{*HoI4::ArticleRule::Builder().setMatcher(std::regex("The (.+)")).setReplacement("$1").build()})
			  .build();

	ASSERT_EQ("Original Text", rule->updateArticles("english", "The Original Text"));
}