#include "HOI4World/Military/RegimentTypeGroup.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Military_RegimentTypeGroupTests, RegimentTypesDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::RegimentTypeGroup regimentTypeGroup(input);

	ASSERT_TRUE(regimentTypeGroup.takeRegimentTypes().empty());
}


TEST(HoI4World_Military_RegimentTypeGroupTests, RegimentTypesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tinfantry = { x = 0 y = 0 }\n";
	input << "}";
	const HoI4::RegimentTypeGroup regimentTypeGroup(input);

	ASSERT_EQ(1, regimentTypeGroup.takeRegimentTypes().size());
	ASSERT_EQ("infantry", regimentTypeGroup.takeRegimentTypes()[0].getType());
}