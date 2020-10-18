#include "HOI4World/States/StateCategory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_States_StateCategoryTests, NumberOfSlotsDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateCategory theStateCategory(input);

	ASSERT_EQ(0, theStateCategory.getNumberOfSlots());
}


TEST(HoI4World_States_StateCategoryTests, NumberOfSlotsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlocal_building_slots = 6\n";
	input << "\t}";
	const HoI4::StateCategory theStateCategory(input);

	ASSERT_EQ(6, theStateCategory.getNumberOfSlots());
}