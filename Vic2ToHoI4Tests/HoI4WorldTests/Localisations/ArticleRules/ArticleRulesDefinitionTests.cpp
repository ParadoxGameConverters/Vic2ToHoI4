#include "../Vic2ToHoI4/Source/HOI4World/Localisations/ArticleRules/ArticleRulesDefinition.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Localisations_ArticleRulesDefinition_ArticleRules, LanguageDefaultsToEmpty)
{
	std::stringstream input;
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_TRUE(definition.getLanguage().empty());
}


TEST(HoI4World_Localisations_ArticleRulesDefinition_ArticleRules, LanguageCanBeSet)
{
	std::stringstream input;
	input << "language = test_language";
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_EQ("test_language", definition.getLanguage());
}


TEST(HoI4World_Localisations_ArticleRulesDefinition_ArticleRules, MatchersDefaultsToEmpty)
{
	std::stringstream input;
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_TRUE(definition.getMatchers().empty());
}


TEST(HoI4World_Localisations_ArticleRulesDefinition_ArticleRules, matchersCanBeAdded)
{
	std::stringstream input;
	input << "matcher = \"Le (.+)\" matcher = \"L'(.+)\"";
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_EQ(2, definition.getMatchers().size());
	ASSERT_EQ("Le (.+)", definition.getMatchers()[0]);
	ASSERT_EQ("L'(.+)", definition.getMatchers()[1]);
}


TEST(HoI4World_Localisations_ArticleRulesDefinition_ArticleRules, ResultDefaultsToEmpty)
{
	std::stringstream input;
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_TRUE(definition.getResult().empty());
}


TEST(HoI4World_Localisations_ArticleRulesDefinition_ArticleRules, ResultCanBeSet)
{
	std::stringstream input;
	input << R"(result = "$1")";
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_EQ("$1", definition.getResult());
}