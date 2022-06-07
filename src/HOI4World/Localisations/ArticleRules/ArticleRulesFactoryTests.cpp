#include "src/HOI4World/Localisations/ArticleRules/ArticleRulesFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Localisations_ArticleRules_ArticleRulesFactory, LanguageDefaultsToEmpty)
{
	const auto rules = HoI4::ArticleRules::Factory().getRules("ArticleRules.txt");

	ASSERT_EQ("Matching String", rules->updateArticles("english", "The Matching String"));
}