#include "src/HOI4World/Modifiers/Modifier.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Modifiers_DynamicModifiersTests, NameIsAsSet)
{
	std::stringstream input;
	const HoI4::Modifier theModifier("theName", input);

	ASSERT_EQ("theName", theModifier.getName());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, AllItemsDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::Modifier theModifier("theModifier", input);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, IconCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ticon = test_icon";
	input << "}";
	const HoI4::Modifier theModifier("theModifier", input);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\ticon = test_icon\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, EnableCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tenable = {\n";
	input << "\t\tNOT = { has_government = fascism }\n";
	input << "\t}\n";
	input << "}";
	const HoI4::Modifier theModifier("theModifier", input);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\tenable = {\n";
	expectedOutput << "\t\tNOT = { has_government = fascism }\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, EnableCanBeUpdated)
{
	std::stringstream input;
	HoI4::Modifier theModifier("theModifier", input);

	std::string newString = "= {\n";
	newString += "\t\tNOT = { has_government = fascism }\n";
	newString += "\t}";
	theModifier.updateEnable(newString);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\tenable = {\n";
	expectedOutput << "\t\tNOT = { has_government = fascism }\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, RemoveTriggerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tremove_trigger = {\n";
	input << "\t\tNOT = { check_variable = { revanchism > 0 } }\n";
	input << "\t}\n";
	input << "}";
	const HoI4::Modifier theModifier("theModifier", input);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\tremove_trigger = {\n";
	expectedOutput << "\t\tNOT = { check_variable = { revanchism > 0 } }\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, RemoveTriggerCanBeUpdated)
{
	std::stringstream input;
	HoI4::Modifier theModifier("theModifier", input);

	std::string newString = "= {\n";
	newString += "\t\tNOT = { check_variable = { revanchism > 0 } }\n";
	newString += "\t}";
	theModifier.updateRemoveTrigger(newString);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\tremove_trigger = {\n";
	expectedOutput << "\t\tNOT = { check_variable = { revanchism > 0 } }\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, EffectCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tfascism_drift = var:revanchism\n";
	input << "}";
	const HoI4::Modifier theModifier("theModifier", input);

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tfascism_drift = var:revanchism\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Modifiers_DynamicModifiersTests, EffectCanBeAdded)
{
	std::stringstream input;
	HoI4::Modifier theModifier("theModifier", input);
	theModifier.addEffect("fascism_drift", "var:revanchism");

	std::stringstream actualOutput;
	actualOutput << theModifier;

	std::stringstream expectedOutput;
	expectedOutput << "theModifier = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tfascism_drift = var:revanchism\n";
	expectedOutput << "}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}
