#include "src/HOI4World/Military/RegimentType.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Military_RegimentTests, TypeDefaultsToBlank)
{
	std::stringstream input;
	const HoI4::RegimentType regimentType("", input);

	ASSERT_EQ("", regimentType.getType());
}


TEST(HoI4World_Military_RegimentTests, TypeCanBeImported)
{
	std::stringstream input;
	const HoI4::RegimentType regimentType("infantry", input);

	ASSERT_EQ("infantry", regimentType.getType());
}


TEST(HoI4World_Military_RegimentTests, PositionDefaultsToOrigin)
{
	std::stringstream input;
	HoI4::RegimentType regimentType("infantry", input);

	std::ostringstream output;
	output << regimentType;

	ASSERT_EQ("\t\tinfantry = { x = 0 y = 0 }\n", output.str());
}


TEST(HoI4World_Military_RegimentTests, PositionCanBeInput)
{
	std::stringstream input("= { x = 1 y = 2 }");
	HoI4::RegimentType regimentType("infantry", input);

	std::ostringstream output;
	output << regimentType;

	ASSERT_EQ("\t\tinfantry = { x = 1 y = 2 }\n", output.str());
}