#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Localisations/LanguageReplacementRule.h"
#include <sstream>



TEST(HoI4World_Localisations_LanguageReplacementRule, ReplacementsDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::LanguageReplacementRule rule("match", input);

	ASSERT_EQ(rule.getReplacements().size(), 0);
}


TEST(HoI4World_Localisations_LanguageReplacementRule, ReplacementCanBeAdded)
{
	std::stringstream input;
	input << " = {\n";
	input << "\t_MS = $1er\n";
	input << "}";
	const HoI4::LanguageReplacementRule rule("match", input);

	const auto& actualReplacements = rule.getReplacements();
	ASSERT_EQ(actualReplacements.size(), 1);
	ASSERT_TRUE(actualReplacements.contains("_MS"));
	ASSERT_EQ(actualReplacements.find("_MS")->second, std::string("$1er"));
}