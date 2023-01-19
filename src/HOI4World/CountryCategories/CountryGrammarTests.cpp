#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/CountryCategories/CountryGrammarFactory.h"
#include <gmock/gmock-matchers.h>



class HoI4World_CountryCategories_CountryGrammarTests: public testing::Test
{
  protected:
	HoI4World_CountryCategories_CountryGrammarTests() {}

	HoI4::CountryGrammarFactory countryGrammarFactory;
};



TEST_F(HoI4World_CountryCategories_CountryGrammarTests, RulesCanBeImported)
{
	const auto grammar = countryGrammarFactory.importCountryGrammar();

	ASSERT_THAT(grammar,
		 testing::ElementsAre(HoI4::CountryGrammarRule{.category = "tag_mscad", .tag = "BAN"},
			  HoI4::CountryGrammarRule{.category = "tag_mscad",
					.tag = "ENG",
					.extra = R"(NOT = { $ABSOLUTIST $DEMOCRATIC })"},
			  HoI4::CountryGrammarRule{.category = "tag_mscae", .tag = "BGL"}));
}