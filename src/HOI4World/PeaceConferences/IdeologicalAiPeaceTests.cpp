#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PeaceConferences/IdeologicalAiPeace.h"
#include "gmock/gmock-matchers.h"



TEST(HoI4World_PeaceConferences_IdeologicalAiPeaceTests, ItemsCanBeImported)
{
	const auto ideological_ai_peace = HoI4::ImportIdeologicalAiPeace();

	EXPECT_THAT(ideological_ai_peace,
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