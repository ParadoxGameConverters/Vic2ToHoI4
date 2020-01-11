#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HoI4World/Localisations/LanguageReplacementRules.h"
#include <sstream>



TEST(HoI4World_Localisations_LanguageReplacementRules, RulesDefaultToEmpty)
{
	std::stringstream input;
	HoI4::LanguageReplacementRules rule(input);

	ASSERT_EQ(rule.getTheRules().size(), 0);
}


TEST(HoI4World_Localisations_LanguageReplacementRules, RuleCanBeAdded)
{
	std::stringstream input;
	input << "\"match\" = {\n";
	input << "\t_MS = $1er\n";
	input << "}";
	HoI4::LanguageReplacementRules rule(input);

	const auto& theRules = rule.getTheRules();
	ASSERT_EQ(theRules.size(), 1);
	ASSERT_EQ(theRules[0].getReplacements().size(), 1);
}