#include "external/googletest/googletest/include/gtest/gtest.h"
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


TEST(HoI4World_States_StateCategoryFileTests, categoriesReferencedByNumberOfSlots)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcity = {\n";
	input << "\t\tlocal_building_slots = 6\n";
	input << "\t}\n";
	input << "\t}";
	const HoI4::StateCategoryFile theStateCategoryFile(input);

	ASSERT_EQ("city", theStateCategoryFile.getCategories().find(6)->second);
}


TEST(HoI4World_States_StateCategoryFileTests, secondCategoryWithSameSlotsDiscarded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcity = {\n";
	input << "\t\tlocal_building_slots = 6\n";
	input << "\t}\n";
	input << "\tsecond_city = {\n";
	input << "\t\tlocal_building_slots = 6\n";
	input << "\t}\n";
	input << "\t}";
	const HoI4::StateCategoryFile theStateCategoryFile(input);

	ASSERT_EQ(theStateCategoryFile.getCategories().size(), 1);
	ASSERT_EQ("city", theStateCategoryFile.getCategories().find(6)->second);
}