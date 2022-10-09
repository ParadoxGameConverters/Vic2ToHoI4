#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PeaceConferences/IdeologicalCostModifiers.h"
#include "gmock/gmock-matchers.h"



TEST(HoI4World_PeaceConferences_IdeologicalCostModifiersTests, ItemsCanBeImported)
{
	const auto ideological_ai_peace = HoI4::ImportIdeologicalCostModifiers();

	EXPECT_THAT(ideological_ai_peace,
		 testing::UnorderedElementsAre(testing::Pair("test_modifier",
													  "\tblock_one = {\n"
													  "\t\tfoo\n"
													  "\t}\n"
													  "\n"
													  "\tblock_two = {\n"
													  "\t\tbar\n"
													  "\t}"),
			  testing::Pair("another_modifier",
					"\tblock_three = {\n"
					"\t\tbaz\n"
					"\t}")));
}