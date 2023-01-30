#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Decisions/DecisionsCategory.h"
#include "src/OutHoi4/Decisions/OutDecisionsCategory.h"
#include <sstream>



TEST(HoI4World_Decisions_DecisionsCategoryTests, DefaultsAreBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("", input);

	std::stringstream expectedOutput;
	expectedOutput << " = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, IconCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ticon = generic_research\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\ticon = generic_research\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, PictureCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpicture = GFX_decision_cat_picture_naval_treaties\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\tpicture = GFX_decision_cat_picture_naval_treaties\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, PriorityCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpriority = 100\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\tpriority = 100\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, AllowedCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed = {\n";
	input << "\t\thas_dlc = \"Man the Guns\"\n";
	input << "\t}\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\tallowed = {\n";
	expectedOutput << "\t\thas_dlc = \"Man the Guns\"\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, VisibleCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tvisible = {\n";
	input << "\t\tis_debug = yes\n";
	input << "\t}\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\tvisible = {\n";
	expectedOutput << "\t\tis_debug = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, VisibilityTypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tvisibility_type = map_and_decisions_view\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\tvisibility_type = map_and_decisions_view\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, ExtraItemsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\textra_item_one = {\n";
	input << "\t}\n";
	input << "\textra_item_two = {\n";
	input << "\t\tcan_it_have_stuff_inside = yes\n";
	input << "\t}\n";
	input << "}";
	const auto theDecisionsCategory = HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_name", input);

	std::stringstream expectedOutput;
	expectedOutput << "category_name = {\n";
	expectedOutput << "\textra_item_one = {\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\textra_item_two = {\n";
	expectedOutput << "\t\tcan_it_have_stuff_inside = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategory;

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}