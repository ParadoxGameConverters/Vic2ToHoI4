#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisation.h"
#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisationFactory.h"
#include <sstream>



TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, NameDefaultsToBlank)
{
	const HoI4::ScriptedLocalisation theLocalisation;

	ASSERT_EQ("", theLocalisation.getName());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, NameCanBeSet)
{
	HoI4::ScriptedLocalisation theLocalisation;
	theLocalisation.setName("test");

	ASSERT_EQ("test", theLocalisation.getName());
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, NameCanBeImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname=test_name\n";
	input << "}";
	const auto theLocalisation = HoI4::ScriptedLocalisation::Factory().getScriptedLocalisation(input);

	ASSERT_EQ("test_name", theLocalisation->getName());
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
	ASSERT_EQ("test", theLocalisation.getTexts()[0]);
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, TextCanBeImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttext = {\n";
	input << "\t\ttrigger = { has_government = fascism }\n";
	input << "\t\tlocalization_key = FRLOC_FASCISME\n";
	input << "\t}\n";
	input << "\ttext = {\n";
	input << "\t\ttrigger = { has_government = communism }\n";
	input << "\t\tlocalization_key = FRLOC_COMMUNISME\n";
	input << "\t}";
	const auto theLocalisation = HoI4::ScriptedLocalisation::Factory().getScriptedLocalisation(input);

	ASSERT_EQ(2, theLocalisation->getTexts().size());
	ASSERT_EQ(
		 "= {\n"
		 "\t\ttrigger = { has_government = fascism }\n"
		 "\t\tlocalization_key = FRLOC_FASCISME\n"
		 "\t}",
		 theLocalisation->getTexts()[0]);
	ASSERT_EQ(
		 "= {\n"
		 "\t\ttrigger = { has_government = communism }\n"
		 "\t\tlocalization_key = FRLOC_COMMUNISME\n"
		 "\t}",
		 theLocalisation->getTexts()[1]);
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, TextsCanBeFiltered)
{
	HoI4::ScriptedLocalisation theLocalisation;
	theLocalisation.addText("test");
	theLocalisation.addText("test2");
	theLocalisation.addText("test3");

	theLocalisation.filterTexts([](const std::string& a) {
		return a == "test2";
	});

	ASSERT_EQ(2, theLocalisation.getTexts().size());
	ASSERT_EQ("test", theLocalisation.getTexts()[0]);
	ASSERT_EQ("test3", theLocalisation.getTexts()[1]);
}


TEST(HoI4World_ScriptedLocalisations_SciptedLocalisationTests, TextsCanBeUpdated)
{
	HoI4::ScriptedLocalisation theLocalisation;
	theLocalisation.addText("test = { replace_me }");
	theLocalisation.addText("test2 = { replace_me_too }");

	theLocalisation.updateTexts(std::regex("replace_me"), "new_text");

	ASSERT_EQ(2, theLocalisation.getTexts().size());
	ASSERT_EQ("test = { new_text }", theLocalisation.getTexts()[0]);
	ASSERT_EQ("test2 = { new_text_too }", theLocalisation.getTexts()[1]);
}