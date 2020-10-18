#include "HOI4World/Localisations/AllReplacementRules.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Localisations_AllReplacementRules, RulesDefaultToEmpty)
{
	std::stringstream input;
	HoI4::AllReplacementRules rules(input);

	ASSERT_EQ(rules.getRulesForLanguage("french"), std::nullopt);
}


TEST(HoI4World_Localisations_AllReplacementRules, LanguageCanBeAdded)
{
	std::stringstream input;
	input << "french = {\n";
	input << "\t\"match\" = {\n";
	input << "\t\t_MS = $1er\n";
	input << "\t}";
	input << "}";
	HoI4::AllReplacementRules rule(input);

	const auto& theRules = rule.getRulesForLanguage("french");
	ASSERT_TRUE(theRules);
	ASSERT_EQ(theRules->getTheRules().size(), 1);
}