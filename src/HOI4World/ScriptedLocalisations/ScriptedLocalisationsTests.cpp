#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisations.h"



TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationsTests, LocalisationsDefaultsToEmpty)
{
	const HoI4::ScriptedLocalisations theLocalisations;

	ASSERT_TRUE(theLocalisations.getLocalisations().empty());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationsTests, GetStrengthRatioAdded)
{
	HoI4::ScriptedLocalisations theLocalisations;
	theLocalisations.addNavyScriptedLocalisations({"TAG", "TWO"});

	ASSERT_TRUE(!theLocalisations.getLocalisations().empty());
	ASSERT_EQ("GetStrengthRatioBritain", theLocalisations.getLocalisations()[0].getName());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationsTests, GetRelevantNavalTreatyNationAdded)
{
	HoI4::ScriptedLocalisations theLocalisations;
	theLocalisations.addNavyScriptedLocalisations({"TAG", "TWO"});

	ASSERT_TRUE(theLocalisations.getLocalisations().size() > 1);
	ASSERT_EQ("GetRelevantNavalTreatyNation", theLocalisations.getLocalisations()[1].getName());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationsTests, TagsGetApplied)
{
	HoI4::ScriptedLocalisations theLocalisations;
	theLocalisations.addNavyScriptedLocalisations({"TAG", "TWO"});

	ASSERT_TRUE(theLocalisations.getLocalisations().size() > 1);
	ASSERT_EQ(2, theLocalisations.getLocalisations()[1].getTexts().size());

	std::string textTwo = "= {\n";
	textTwo += "\t\ttrigger = { \n";
	textTwo += "\t\t\tTAG = { \n";
	textTwo += "\t\t\t\tnot = { has_naval_treaty_trigger = yes }\n";
	textTwo += "\t\t\t}\n";
	textTwo += "\t\t\tTWO = { \n";
	textTwo += "\t\t\t\thas_naval_treaty_trigger = yes\n";
	textTwo += "\t\t\t}\n";
	textTwo += "\t\t}\n";
	textTwo += "\t\tlocalization_key = TWO_Naval_treaty_nation\n";
	textTwo += "\t}";
	ASSERT_EQ(textTwo, theLocalisations.getLocalisations()[1].getTexts()[1]);
}