#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/States/StateCategory.h"
#include <sstream>



TEST(HoI4World_States_StateCategoryTests, NumberOfSlotsDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateCategory theStateCategory("test_category", input);

	ASSERT_EQ(0, theStateCategory.getNumberOfSlots());
}


TEST(HoI4World_States_StateCategoryTests, NumberOfSlotsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlocal_building_slots = 6\n";
	input << "\t}";
	const HoI4::StateCategory theStateCategory("test_category", input);

	ASSERT_EQ(6, theStateCategory.getNumberOfSlots());
}


TEST(HoI4World_States_StateCategoryTests, BuildingsMaxLevelsDefaultsToTen)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateCategory theStateCategory("test_category", input);

	ASSERT_EQ(10, theStateCategory.getBuildingMaxLevel("test_building"));
}


TEST(HoI4World_States_StateCategoryTests, BuildingsMaxLevelsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tbuildings_max_level = {\n";
	input << "\t\tnaval_base = 6\n";
	input << "\t}\n";
	input << "}\n";
	const HoI4::StateCategory theStateCategory("test_category", input);

	ASSERT_EQ(6, theStateCategory.getBuildingMaxLevel("naval_base"));
}