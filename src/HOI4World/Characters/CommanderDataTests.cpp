#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/CommanderData.h"
#include "src/HOI4World/Characters/CommanderDataFactory.h"
#include <sstream>



TEST(HoI4World_Characters_CommanderData, ItemsAreAsSet)
{
	const HoI4::CommanderData commander_data(HoI4::CommanderLevel::CorpsCommander, {}, 2, 3, 4, 5, 6);

	EXPECT_EQ(commander_data.getLevel(), HoI4::CommanderLevel::CorpsCommander);
	EXPECT_TRUE(commander_data.getTraits().empty());
	EXPECT_EQ(commander_data.getSkill(), 2);
	EXPECT_EQ(commander_data.getAttackSkill(), 3);
	EXPECT_EQ(commander_data.getDefenseSkill(), 4);
	EXPECT_EQ(commander_data.getPlanningSkill(), 5);
	EXPECT_EQ(commander_data.getLogisticsSkill(), 6);
}


TEST(HoI4World_Characters_CommanderData, LevelCanBeSetToFieldMarshall)
{
	const HoI4::CommanderData commander_data(HoI4::CommanderLevel::FieldMarshal, {}, 2, 3, 4, 5, 6);

	EXPECT_EQ(commander_data.getLevel(), HoI4::CommanderLevel::FieldMarshal);
}


TEST(HoI4World_Characters_CommanderData, TraitsCanBeSet)
{
	const HoI4::CommanderData
		 commander_data(HoI4::CommanderLevel::CorpsCommander, {"test_trait_1", "test_trait_2"}, 2, 3, 4, 5, 6);

	EXPECT_THAT(commander_data.getTraits(), testing::ElementsAre("test_trait_1", "test_trait_2"));
}


TEST(HoI4World_Characters_CommanderData, ImportedItemsAreDefaulted)
{
	std::stringstream input;

	const HoI4::CommanderData commander_data = HoI4::CommanderDataFactory().importCommanderData("", input);

	EXPECT_EQ(commander_data.getLevel(), HoI4::CommanderLevel::CorpsCommander);
	EXPECT_TRUE(commander_data.getTraits().empty());
	EXPECT_EQ(commander_data.getSkill(), 1);
	EXPECT_EQ(commander_data.getAttackSkill(), 1);
	EXPECT_EQ(commander_data.getDefenseSkill(), 1);
	EXPECT_EQ(commander_data.getPlanningSkill(), 1);
	EXPECT_EQ(commander_data.getLogisticsSkill(), 1);
}


TEST(HoI4World_Characters_CommanderData, ImportedItemsCanBeSet)
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

	const HoI4::CommanderData commander_data = HoI4::CommanderDataFactory().importCommanderData("field_marshal", input);

	EXPECT_EQ(commander_data.getLevel(), HoI4::CommanderLevel::FieldMarshal);
	EXPECT_THAT(commander_data.getTraits(), testing::ElementsAre("test_commander_trait_1", "test_commander_trait_2"));
	EXPECT_EQ(commander_data.getSkill(), 2);
	EXPECT_EQ(commander_data.getAttackSkill(), 3);
	EXPECT_EQ(commander_data.getDefenseSkill(), 4);
	EXPECT_EQ(commander_data.getPlanningSkill(), 5);
	EXPECT_EQ(commander_data.getLogisticsSkill(), 6);
}