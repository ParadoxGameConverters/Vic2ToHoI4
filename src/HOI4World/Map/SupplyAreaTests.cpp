#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/SupplyArea.h"



TEST(HoI4World_Map_SupplyArea, IdDefaultsToZero)
{
	std::stringstream input;
	const HoI4::SupplyArea area(input);

	ASSERT_EQ(0, area.getID());
}


TEST(HoI4World_Map_SupplyArea, IdCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tid = 42";
	input << "}";
	const HoI4::SupplyArea area(input);

	ASSERT_EQ(42, area.getID());
}


TEST(HoI4World_Map_SupplyArea, ValueDefaultsToZero)
{
	std::stringstream input;
	const HoI4::SupplyArea area(input);

	ASSERT_EQ(0, area.getValue());
}


TEST(HoI4World_Map_SupplyArea, ValueCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tvalue = 42";
	input << "}";
	const HoI4::SupplyArea area(input);

	ASSERT_EQ(42, area.getValue());
}


TEST(HoI4World_Map_SupplyArea, StatesDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::SupplyArea area(input);

	ASSERT_TRUE(area.getStates().empty());
}


TEST(HoI4World_Map_SupplyArea, StatesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tstates = { 1 2 3 }\n";
	input << "}";
	const HoI4::SupplyArea area(input);

	const std::vector<int> expectedStates{1, 2, 3};
	ASSERT_EQ(expectedStates, area.getStates());
}