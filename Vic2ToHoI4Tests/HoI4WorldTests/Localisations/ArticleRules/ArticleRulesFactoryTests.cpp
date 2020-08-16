#include "../Vic2ToHoI4/Source/HOI4World/Localisations/ArticleRules/ArticleRulesFactory.h"
#include "gtest/gtest.h"
#include <sstream>


#pragma optimize("",off)
TEST(HoI4World_Localisations_ArticleRules_ArticleRulesFactory, LanguageDefaultsToEmpty)
{
	const auto rules = HoI4::ArticleRules::Factory{}.getRules("ArticleRules.txt");

	ASSERT_EQ("Matching String", rules->updateArticles("english", "The Matching String"));
}
#pragma optimize("", on)