#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Localisations/ArticleRules/ArticleRulesDefinition.h"
#include <sstream>



TEST(HoI4World_Localisations_ArticleRules_ArticleRulesDefinition, LanguageDefaultsToEmpty)
{
	std::stringstream input;
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_TRUE(definition.getLanguage().empty());
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRulesDefinition, LanguageCanBeSet)
{
	std::stringstream input;
	input << "language = test_language";
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_EQ("test_language", definition.getLanguage());
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRulesDefinition, MatchersDefaultsToEmpty)
{
	std::stringstream input;
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_TRUE(definition.getMatchers().empty());
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRulesDefinition, matchersCanBeAdded)
{
	std::stringstream input;
	input << "matcher = \"Le (.+)\" matcher = \"L'(.+)\"";
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_EQ(2, definition.getMatchers().size());
	ASSERT_EQ("Le (.+)", definition.getMatchers()[0]);
	ASSERT_EQ("L'(.+)", definition.getMatchers()[1]);
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRulesDefinition, ReplacementDefaultsToEmpty)
{
	std::stringstream input;
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_TRUE(definition.getReplacement().empty());
}


TEST(HoI4World_Localisations_ArticleRules_ArticleRulesDefinition, ReplacementCanBeSet)
{
	std::stringstream input;
	input << R"(replacement = "$1")";
	const auto definition = HoI4::ArticleRulesDefinition(input);

	ASSERT_EQ("$1", definition.getReplacement());
}