#include "src/HOI4World/Ideologies/IdeologyFile.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Ideologies_IdeologyFileTests, IdeologiesDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::IdeologyFile ideologyFile(input);

	ASSERT_TRUE(ideologyFile.getIdeologies().empty());
}


TEST(HoI4World_Ideologies_IdeologyFileTests, IdeologiesCanBeAdded)
{
	std::stringstream input;
	input << "ideology_one = { color = { 0 0 0 } }\n";
	input << "ideology_two = { color = { 0 0 0 } }\n";
	const HoI4::IdeologyFile ideologyFile(input);

	ASSERT_EQ(2, ideologyFile.getIdeologies().size());
}