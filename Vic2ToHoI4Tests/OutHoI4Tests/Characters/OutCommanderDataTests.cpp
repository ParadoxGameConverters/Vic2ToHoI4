#include "OutHoi4/Characters/OutCommanderData.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(OutHoI4World_Characters_OutCommanderDataTests, CommanderDataIsOutput)
{
	const HoI4::CommanderData commanderData(HoI4::CommanderLevel::CorpsCommander, {}, 2, 3, 4, 5, 6);
	std::stringstream output;
	output << commanderData;

	std::stringstream expected;
	expected << "\t\tcorps_commander={\n";
	expected << "\t\t\tskill=2\n";
	expected << "\t\t\tattack_skill=3\n";
	expected << "\t\t\tdefense_skill=4\n";
	expected << "\t\t\tplanning_skill=5\n";
	expected << "\t\t\tlogistics_skill=6\n";
	expected << "\t\t\tlegacy_id=0\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Characters_OutCommanderDataTests, FieldMarshalLevelIsOutput)
{
	const HoI4::CommanderData commanderData(HoI4::CommanderLevel::FieldMarshal, {}, 2, 3, 4, 5, 6);
	std::stringstream output;
	output << commanderData;

	std::stringstream expected;
	expected << "\t\tfield_marshal={\n";
	expected << "\t\t\tskill=2\n";
	expected << "\t\t\tattack_skill=3\n";
	expected << "\t\t\tdefense_skill=4\n";
	expected << "\t\t\tplanning_skill=5\n";
	expected << "\t\t\tlogistics_skill=6\n";
	expected << "\t\t\tlegacy_id=0\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Characters_OutCommanderDataTests, TraitsAreOutput)
{
	const HoI4::CommanderData
		 commanderData(HoI4::CommanderLevel::CorpsCommander, {"test_trait_1", "test_trait_2"}, 2, 3, 4, 5, 6);
	std::stringstream output;
	output << commanderData;

	std::stringstream expected;
	expected << "\t\tcorps_commander={\n";
	expected << "\t\t\ttraits={ test_trait_1 test_trait_2 }\n";
	expected << "\t\t\tskill=2\n";
	expected << "\t\t\tattack_skill=3\n";
	expected << "\t\t\tdefense_skill=4\n";
	expected << "\t\t\tplanning_skill=5\n";
	expected << "\t\t\tlogistics_skill=6\n";
	expected << "\t\t\tlegacy_id=0\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}