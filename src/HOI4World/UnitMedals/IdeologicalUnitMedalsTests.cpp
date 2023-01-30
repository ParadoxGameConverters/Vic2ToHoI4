#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/UnitMedals/IdeologicalUnitMedals.h"



TEST(HoI4World_UnitMedals_IdeologicalUnitMedalsTests, ItemsCanBeImported)
{
	const auto ideological_unit_medals = HoI4::ImportIdeologicalUnitMedals();

	EXPECT_THAT(ideological_unit_medals,
		 testing::UnorderedElementsAre(testing::Pair("test_ideology",
													  "\tblock_one = {\n"
													  "\t\tfoo\n"
													  "\t}\n"
													  "\n"
													  "\tblock_two = {\n"
													  "\t\tbar\n"
													  "\t}"),
			  testing::Pair("another_ideology",
					"\tblock_three = {\n"
					"\t\tbaz\n"
					"\t}")));
}