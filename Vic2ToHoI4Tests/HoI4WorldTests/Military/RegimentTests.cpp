#include "../Vic2ToHoI4/Source/HoI4World/Military/Regiment.h"
#include "gtest/gtest.h"



TEST(HoI4World_RegimentTests, RegimentTypeTypeDefaultsToBlank)
{
	std::istringstream input("");
	HoI4::RegimentType regimentType("", input);
	ASSERT_EQ(std::string(""), regimentType.getType());
}


TEST(HoI4World_RegimentTests, RegimentTypeTypeCanBeImported)
{
	std::istringstream input("= { x = 0 y = 0 }");
	HoI4::RegimentType regimentType("infantry", input);
	ASSERT_EQ(std::string("infantry"), regimentType.getType());
}


TEST(HoI4World_RegimentTests, RegimentTypeTypeCopiedByCopyConstructor)
{
	std::istringstream input("= { x = 0 y = 0 }");
	HoI4::RegimentType regimentType("infantry", input);
	HoI4::RegimentType regimentType2(regimentType);
	ASSERT_EQ(regimentType.getType(), regimentType2.getType());
}


TEST(HoI4World_RegimentTests, BlankRegimentTypeOutputsProperly)
{
	std::istringstream input("");
	HoI4::RegimentType regimentType("", input);
	std::ostringstream output;
	output << regimentType;
	ASSERT_EQ(std::string("\t\t = { x = 0 y = 0 }\n"), output.str());
}


TEST(HoI4World_RegimentTests, ImportedRegimentTypeOutputsProperly)
{
	std::istringstream input("= { x = 1 y = 2 }");
	HoI4::RegimentType regimentType("infantry", input);
	std::ostringstream output;
	output << regimentType;
	ASSERT_EQ(std::string("\t\tinfantry = { x = 1 y = 2 }\n"), output.str());
}


TEST(HoI4World_RegimentTests, CopiedRegimentTypeOutputsProperly)
{
	std::istringstream input("= { x = 1 y = 2 }");
	HoI4::RegimentType regimentType("infantry", input);
	std::ostringstream output;
	output << regimentType;
	HoI4::RegimentType regimentType2(regimentType);
	std::ostringstream output2;
	output2 << regimentType2;
	ASSERT_EQ(output.str(), output2.str());
}