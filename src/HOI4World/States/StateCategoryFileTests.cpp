#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/States/StateCategoryFile.h"
#include <sstream>



TEST(HoI4World_States_StateCategoryFileTests, categoriesDefaultsToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateCategoryFile theStateCategoryFile(input);

	ASSERT_TRUE(theStateCategoryFile.getCategories().empty());
}


TEST(HoI4World_States_StateCategoryFileTests, categoriesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcity = {\n";
	input << "\t}\n";
	input << "\t}";
	const HoI4::StateCategoryFile theStateCategoryFile(input);

	ASSERT_EQ(1, theStateCategoryFile.getCategories().size());
}