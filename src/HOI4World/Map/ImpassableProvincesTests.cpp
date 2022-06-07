#include "src/HOI4World/Map/ImpassableProvinces.h"
#include "src/HOI4World/States/DefaultState.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Map_ImpassableProvinces, ProvinceDefaultsToPassable)
{
	const std::map<int, HoI4::DefaultState> defaultStates;

	const HoI4::ImpassableProvinces impassableProvinces(defaultStates);

	ASSERT_FALSE(impassableProvinces.isProvinceImpassable(1));
}


TEST(HoI4World_Map_ImpassableProvinces, ProvinceCanBeSetImpassable)
{
	std::stringstream input;
	input << "= {\n";
	input << "\timpassable = true\n";
	input << "\tprovinces = { 1 }\n";
	input << "}";
	HoI4::DefaultState defaultState(input);
	std::map<int, HoI4::DefaultState> defaultStates;
	defaultStates.insert(std::make_pair(1, defaultState));

	const HoI4::ImpassableProvinces impassableProvinces(defaultStates);

	ASSERT_TRUE(impassableProvinces.isProvinceImpassable(1));
}