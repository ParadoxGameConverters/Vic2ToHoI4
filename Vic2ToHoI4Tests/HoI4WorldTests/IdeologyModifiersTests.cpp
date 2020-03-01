#include "../Vic2ToHoI4/Source/HOI4World/IdeologyModifiers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_IdeologyModifiersTests, ModifiersDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::IdeologyModifiers ideologyModifiers(input);

	ASSERT_TRUE(ideologyModifiers.takeModifiers().empty());
}


TEST(HoI4World_IdeologyModifiersTests, ModifiersCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tkey = value\n";
	input << "\tkey2 = { complex value }\n";
	input << "}";
	HoI4::IdeologyModifiers ideologyModifiers(input);

	const std::map<std::string, std::string> expectedModifiers{{"key", "= value"}, {"key2", "= { complex value }"}};

	ASSERT_EQ(expectedModifiers, ideologyModifiers.takeModifiers());
}