#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Decisions/DecisionsCategories.h"
#include <sstream>



TEST(HoI4World_Decisions_DecisionsCategoryTests, CategoriesDefaultToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const auto theDecisionsCategories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(input);

	ASSERT_TRUE(theDecisionsCategories->getTheCategories().empty());
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, CategoriesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcategory_one = {\n";
	input << "\t}\n";
	input << "\tcategory_two = {\n";
	input << "\t}\n";
	input << "}";
	const auto theDecisionsCategories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(input);

	ASSERT_EQ(theDecisionsCategories->getTheCategories().size(), 2);
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, CategoriesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	auto theDecisionsCategories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(input);

	theDecisionsCategories->addCategory(HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_one", input));

	ASSERT_EQ(theDecisionsCategories->getTheCategories().size(), 1);
}


TEST(HoI4World_Decisions_DecisionsCategoryTests, CategoriesCanBeReplaced)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	auto theDecisionsCategories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(input);

	theDecisionsCategories->addCategory(HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_one", input));

	std::stringstream replacementInput;
	replacementInput << "= {\n";
	replacementInput << "\ticon = generic_research\n";
	replacementInput << "}";
	theDecisionsCategories->replaceCategory(
		 HoI4::DecisionsCategory::Factory().getDecisionsCategory("category_one", replacementInput));

	ASSERT_EQ(theDecisionsCategories->getTheCategories().size(), 1);

	std::stringstream expectedOutput;
	expectedOutput << "category_one = {\n";
	expectedOutput << "\ticon = generic_research\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	std::stringstream actualOutput;
	actualOutput << theDecisionsCategories->getTheCategories()[0];

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}