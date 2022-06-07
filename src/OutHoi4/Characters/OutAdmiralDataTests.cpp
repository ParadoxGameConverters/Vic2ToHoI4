#include "src/OutHoi4/Characters/OutAdmiralData.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(OutHoI4World_Characters_OutAdmiralDataTests, AdmiralDataIsOutput)
{
	const HoI4::AdmiralData admiralData({}, 2, 3, 4, 5, 6);
	std::stringstream output;
	output << admiralData;

	std::stringstream expected;
	expected << "\t\tnavy_leader={\n";
	expected << "\t\t\tskill=2\n";
	expected << "\t\t\tattack_skill=3\n";
	expected << "\t\t\tdefense_skill=4\n";
	expected << "\t\t\tmaneuvering_skill=5\n";
	expected << "\t\t\tcoordination_skill=6\n";
	expected << "\t\t\tlegacy_id=0\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Characters_OutAdmiralDataTests, TraitsAreOutput)
{
	const HoI4::AdmiralData admiralData({"test_trait_1", "test_trait_2"}, 2, 3, 4, 5, 6);
	std::stringstream output;
	output << admiralData;

	std::stringstream expected;
	expected << "\t\tnavy_leader={\n";
	expected << "\t\t\ttraits={ test_trait_1 test_trait_2 }\n";
	expected << "\t\t\tskill=2\n";
	expected << "\t\t\tattack_skill=3\n";
	expected << "\t\t\tdefense_skill=4\n";
	expected << "\t\t\tmaneuvering_skill=5\n";
	expected << "\t\t\tcoordination_skill=6\n";
	expected << "\t\t\tlegacy_id=0\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}