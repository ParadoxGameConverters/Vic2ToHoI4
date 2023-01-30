#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Ideologies/IdeologyItems.h"
#include <sstream>



TEST(HoI4World_Ideologies_IdeologyItemsTests, ItemsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::IdeologyItems ideologyItems(input);

	ASSERT_TRUE(ideologyItems.takeItems().empty());
}


TEST(HoI4World_Ideologies_IdeologyItemsTests, ItemsCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tkey = value\n";
	input << "\tkey2 = { complex value }\n";
	input << "}";
	HoI4::IdeologyItems ideologyItems(input);

	const std::map<std::string, std::string> expectedItems{{"key", "= value"}, {"key2", "= { complex value }"}};

	ASSERT_EQ(expectedItems, ideologyItems.takeItems());
}