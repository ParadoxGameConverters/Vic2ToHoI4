#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/Decisions/DecisionsCategories.h"
#include <sstream>



TEST(HoI4World_DecisionsCategoriesTests, noOutputByDefault)
{
	std::set<std::string> majorIdeologies;
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_DecisionsCategoriesTests, fascismCanBeOutput)
{
	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("fascism");
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;
	expectedOutput << "fascism_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_fascism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = fascism }\n";
	expectedOutput << "\t#	has_idea_with_trait = fascism_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_DecisionsCategoriesTests, absolutistCanBeOutput)
{
	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutist");
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;
	expectedOutput << "absolutist_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_fascism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = absolutist }\n";
	expectedOutput << "\t#	has_idea_with_trait = absolutist_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_DecisionsCategoriesTests, democraticCanBeOutput)
{
	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("democratic");
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;
	expectedOutput << "democratic_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_democracy\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = democratic }\n";
	expectedOutput << "\t#	has_idea_with_trait = democratic_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_DecisionsCategoriesTests, communismCanBeOutput)
{
	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("communism");
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;
	expectedOutput << "communism_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_communism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = communism }\n";
	expectedOutput << "\t#	has_idea_with_trait = communism_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_DecisionsCategoriesTests, radicalCanBeOutput)
{
	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("radical");
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;
	expectedOutput << "radical_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_communism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = radical }\n";
	expectedOutput << "\t#	has_idea_with_trait = radical_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_DecisionsCategoriesTests, allCanBeOutputTogether)
{
	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("fascism");
	majorIdeologies.insert("absolutist");
	majorIdeologies.insert("democratic");
	majorIdeologies.insert("communism");
	majorIdeologies.insert("radical");
	HoI4::DecisionsCategories theCategories(majorIdeologies);

	std::stringstream expectedOutput;
	expectedOutput << "fascism_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_fascism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = fascism }\n";
	expectedOutput << "\t#	has_idea_with_trait = fascism_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "absolutist_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_fascism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = absolutist }\n";
	expectedOutput << "\t#	has_idea_with_trait = absolutist_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "democratic_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_democracy\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = democratic }\n";
	expectedOutput << "\t#	has_idea_with_trait = democratic_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "communism_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_communism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = communism }\n";
	expectedOutput << "\t#	has_idea_with_trait = communism_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "radical_on_the_rise = {\n";
	expectedOutput << "\ticon = generic_communism\n";
	expectedOutput << "\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t#visible = {\n";
	expectedOutput << "\t#	NOT = { has_government = radical }\n";
	expectedOutput << "\t#	has_idea_with_trait = radical_minister\n";
	expectedOutput << "\t#}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theCategories;
	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}