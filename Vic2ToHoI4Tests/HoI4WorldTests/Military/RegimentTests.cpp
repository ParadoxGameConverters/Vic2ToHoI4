#include "../Vic2ToHoI4/Source/HOI4World/Military/Regiment.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Military_RegimentTests, RegimentTypeTypeDefaultsToBlank)
{
	std::stringstream input;
	const HoI4::RegimentType regimentType("", input);

	ASSERT_EQ("", regimentType.getType());
}


TEST(HoI4World_Military_RegimentTests, RegimentTypeTypeCanBeImported)
{
	std::stringstream input;
	const HoI4::RegimentType regimentType("infantry", input);

	ASSERT_EQ("infantry", regimentType.getType());
}


TEST(HoI4World_Military_RegimentTests, RegimentTypeTypeCopiedByCopyConstructor)
{
	std::stringstream input("= { x = 0 y = 0 }");
	const HoI4::RegimentType regimentType("infantry", input);
	const auto regimentType2(regimentType);

	ASSERT_EQ(regimentType.getType(), regimentType2.getType());
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