#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/ScriptedLocalisations/ScriptedLocalisation.h"



TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, NameDefaultsToBlank)
{
	const HoI4::ScriptedLocalisation theLocalisation;

	ASSERT_EQ(std::string(""), theLocalisation.getName());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, NameCanBeSet)
{
	HoI4::ScriptedLocalisation theLocalisation;
	theLocalisation.setName("test");

	ASSERT_EQ(std::string("test"), theLocalisation.getName());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, TextsDefaultsToEmpty)
{
	const HoI4::ScriptedLocalisation theLocalisation;

	ASSERT_TRUE(theLocalisation.getTexts().empty());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, TextsCanBeAdded)
{
	HoI4::ScriptedLocalisation theLocalisation;
	theLocalisation.addText("test");

	ASSERT_EQ(1, theLocalisation.getTexts().size());
	ASSERT_EQ(theLocalisation.getTexts()[0], "test");
}