#include "HOI4World/CountryCategories/CountryGrammarRule.h"
#include "HOI4World/CountryCategories/CountryGrammarRuleFactory.h"
#include "gtest/gtest.h"



class HoI4World_CountryCategories_CountryGrammarRuleTests: public testing::Test
{
  protected:
	HoI4World_CountryCategories_CountryGrammarRuleTests() {}

	HoI4::CountryGrammarRuleFactory countryGrammarRuleFactory;
};



TEST_F(HoI4World_CountryCategories_CountryGrammarRuleTests, CategoryDefaultsToEmpty)
{
	std::stringstream input;

	const auto rule = countryGrammarRuleFactory.importCountryGrammarRule(input);

	ASSERT_TRUE(rule.category.empty());
}


TEST_F(HoI4World_CountryCategories_CountryGrammarRuleTests, CategoryCanBeSet)
{
	std::stringstream input;
	input << "category = test_category";

	const auto rule = countryGrammarRuleFactory.importCountryGrammarRule(input);

	ASSERT_EQ("test_category", rule.category);
}


TEST_F(HoI4World_CountryCategories_CountryGrammarRuleTests, TagDefaultsToEmpty)
{
	std::stringstream input;

	const auto rule = countryGrammarRuleFactory.importCountryGrammarRule(input);

	ASSERT_TRUE(rule.tag.empty());
}


TEST_F(HoI4World_CountryCategories_CountryGrammarRuleTests, TagCanBeSet)
{
	std::stringstream input;
	input << "vic2_tag = TAG";

	const auto rule = countryGrammarRuleFactory.importCountryGrammarRule(input);

	ASSERT_EQ("TAG", rule.tag);
}


TEST_F(HoI4World_CountryCategories_CountryGrammarRuleTests, ExtraDefaultsToNulltop)
{
	std::stringstream input;

	const auto rule = countryGrammarRuleFactory.importCountryGrammarRule(input);

	ASSERT_EQ(std::nullopt, rule.extra);
}


TEST_F(HoI4World_CountryCategories_CountryGrammarRuleTests, ExtraCanBeSet)
{
	std::stringstream input;
	input << R"(extra = "NOT = { has_government = democratic has_government = fascism has_government = communism }")";

	const auto rule = countryGrammarRuleFactory.importCountryGrammarRule(input);

	ASSERT_EQ(R"(NOT = { has_government = democratic has_government = fascism has_government = communism })",
		 *rule.extra);
}