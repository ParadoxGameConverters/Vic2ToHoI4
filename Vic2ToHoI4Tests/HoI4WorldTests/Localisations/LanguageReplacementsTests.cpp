#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HoI4World/Localisations/LanguageReplacements.h"
#include <sstream>



TEST(HoI4World_Localisations_LanguageReplacements, RulesDefaultToEmpty)
{
	std::stringstream input;
	HoI4::LanguageReplacements replacements(input);

	ASSERT_EQ(replacements.getReplacements().size(), 0);
}


TEST(HoI4World_Localisations_LanguageReplacements, RuleCanBeAdded)
{
	std::stringstream input;
	input << "_MS = $1er";
	HoI4::LanguageReplacements replacements(input);

	const auto& actualReplacements = replacements.getReplacements();
	ASSERT_EQ(actualReplacements.size(), 1);
	ASSERT_NE(actualReplacements.find("_MS"), actualReplacements.end());
	ASSERT_EQ(actualReplacements.find("_MS")->second, std::string("$1er"));
}


TEST(HoI4World_Localisations_LanguageReplacements, RuleCanHaveUTF8)
{
	std::stringstream input;
	input << "_FS = $1\xC3\xA8re";
	HoI4::LanguageReplacements replacements(input);

	const auto& actualReplacements = replacements.getReplacements();
	ASSERT_EQ(actualReplacements.size(), 1);
	ASSERT_NE(actualReplacements.find("_FS"), actualReplacements.end());
	ASSERT_EQ(actualReplacements.find("_FS")->second, std::string("$1\xC3\xA8re"));
}