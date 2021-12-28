#include "HOI4World/Characters/AdmiralData.h"
#include "HOI4World/Characters/AdmiralDataFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Characters_AdmiralData, ItemsAreAsSet)
{
	const HoI4::AdmiralData admiral_data({}, 2, 3, 4, 5, 6);

	EXPECT_TRUE(admiral_data.getTraits().empty());
	EXPECT_EQ(admiral_data.getSkill(), 2);
	EXPECT_EQ(admiral_data.getAttackSkill(), 3);
	EXPECT_EQ(admiral_data.getDefenseSkill(), 4);
	EXPECT_EQ(admiral_data.getManeuveringSkill(), 5);
	EXPECT_EQ(admiral_data.getCoordinationSkill(), 6);
}


TEST(HoI4World_Characters_AdmiralData, TraitsCanBeSet)
{
	const HoI4::AdmiralData admiral_data({"test_trait_1", "test_trait_2"}, 2, 3, 4, 5, 6);

	EXPECT_THAT(admiral_data.getTraits(), testing::ElementsAre("test_trait_1", "test_trait_2"));
}


TEST(HoI4World_Characters_AdmiralData, ImportedItemsAreDefaulted)
{
	std::stringstream input;

	const HoI4::AdmiralData admiral_data = HoI4::AdmiralDataFactory().importAdmiralData(input);

	EXPECT_TRUE(admiral_data.getTraits().empty());
	EXPECT_EQ(admiral_data.getSkill(), 1);
	EXPECT_EQ(admiral_data.getAttackSkill(), 1);
	EXPECT_EQ(admiral_data.getDefenseSkill(), 1);
	EXPECT_EQ(admiral_data.getManeuveringSkill(), 1);
	EXPECT_EQ(admiral_data.getCoordinationSkill(), 1);
}


TEST(HoI4World_Characters_AdmiralData, ImportedItemsCanBeSet)
{
	std::stringstream input;
	input << "\t\t={\n";
	input << "\t\t\ttraits={ test_commander_trait_1 test_commander_trait_2 }\n";
	input << "\t\t\tskill=2\n";
	input << "\t\t\tattack_skill=3\n";
	input << "\t\t\tdefense_skill=4\n";
	input << "\t\t\tplanning_skill=5\n";
	input << "\t\t\tlogistics_skill=6\n";
	input << "\t\t\tlegacy_id=0\n";
	input << "\t\t}\n";

	const HoI4::AdmiralData admiral_data = HoI4::AdmiralDataFactory().importAdmiralData(input);

	EXPECT_THAT(admiral_data.getTraits(), testing::ElementsAre("test_commander_trait_1", "test_commander_trait_2"));
	EXPECT_EQ(admiral_data.getSkill(), 2);
	EXPECT_EQ(admiral_data.getAttackSkill(), 3);
	EXPECT_EQ(admiral_data.getDefenseSkill(), 4);
	EXPECT_EQ(admiral_data.getManeuveringSkill(), 5);
	EXPECT_EQ(admiral_data.getCoordinationSkill(), 6);
}