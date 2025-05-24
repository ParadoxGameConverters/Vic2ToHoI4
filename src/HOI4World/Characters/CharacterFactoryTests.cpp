#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/CharacterFactory.h"
#include "src/HOI4World/Characters/Portrait.h"



TEST(HoI4World_Characters_CharacterFactory, AllImportedItemsAreDefaulted)
{
	std::stringstream input;

	const auto character = HoI4::Character::Factory().importCharacter("", input);

	EXPECT_EQ(character.getId(), "");
	EXPECT_EQ(character.getName(), "Nomen Nescio");
	EXPECT_TRUE(character.getPortraits().empty());
	EXPECT_FALSE(character.getAllowed().has_value());
	EXPECT_FALSE(character.getAllowedCivilWar().has_value());
	EXPECT_FALSE(character.getAdvisorData().has_value());
	EXPECT_FALSE(character.getCountryLeaderData().has_value());
	EXPECT_FALSE(character.getCommanderData().has_value());
	EXPECT_FALSE(character.getAdmiralData().has_value());
	EXPECT_TRUE(character.getInstances().empty());
}


TEST(HoI4World_Characters_CharacterFactory, ItemsAreSetWhenImportingCharacter)
{
	std::stringstream input;
	input << "={\n";
	input << "\t\tallowed = {\n";
	input << "\t\t\thas_dlc = \"La Resistance\"\n";
	input << "\t\t}\n";
	input << "\t\tname=TAG_test_character_name\n";
	input << "\t\tportraits={\n";
	input << "\t\t\tcivilian={\n";
	input << "\t\t\t\tlarge=\"gfx/leaders/TAG/TAG_test_character.dds\"\n";
	input << "\t\t\t}\n";
	input << "\t\t\tarmy={\n";
	input << "\t\t\t\tsmall=\"gfx/interface/ideas/idea_TAG_test_character.dds\"\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\tallowed_civil_war = {\n";
	input << "\t\t\ttag = USA\n";
	input << "\t\t\thas_government = communism\n";
	input << "\t\t}\n";
	input << "\t\tadvisor={\n";
	input << "\t\t\tslot = political_advisor\n";
	input << "\t\t\tidea_token = thomas_kinkaid\n";
	input << "\t\t\tallowed = {\n";
	input << "\t\t\t\toriginal_tag = USA\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\tcountry_leader={\n";
	input << "\t\t\tideology=test_ideology\n";
	input << "\t\t\ttraits={ test_leader_trait_1 test_leader_trait_2 }\n";
	input << "\t\t\texpire=\"1965.1.1.1\"\n";
	input << "\t\t\tid=-1\n";
	input << "\t\t}\n";
	input << "\t\tcorps_commander={\n";
	input << "\t\t\ttraits={ test_commander_trait_1 test_commander_trait_2 }\n";
	input << "\t\t\tskill=5\n";
	input << "\t\t\tattack_skill=7\n";
	input << "\t\t\tdefense_skill=3\n";
	input << "\t\t\tplanning_skill=2\n";
	input << "\t\t\tlogistics_skill=4\n";
	input << "\t\t\tlegacy_id=0\n";
	input << "\t\t}\n";
	input << "\t\tnavy_leader={\n";
	input << "\t\t\ttraits={ test_admiral_trait_1 test_admiral_trait_2 }\n";
	input << "\t\t\tskill=5\n";
	input << "\t\t\tattack_skill=4\n";
	input << "\t\t\tdefense_skill=3\n";
	input << "\t\t\tmaneuvering_skill=2\n";
	input << "\t\t\tcoordination_skill=6\n";
	input << "\t\t\tlegacy_id=0\n";
	input << "\t\t}\n";
	input << "\t}\n";

	const auto character = HoI4::Character::Factory().importCharacter("TAG_test_character_id", input);

	EXPECT_EQ(character.getId(), "TAG_test_character_id");
	EXPECT_EQ(character.getName(), "TAG_test_character_name");

	HoI4::Portrait portraitOne("civilian", "large", "gfx/leaders/TAG/TAG_test_character.dds");
	HoI4::Portrait portraitTwo("army", "small", "gfx/interface/ideas/idea_TAG_test_character.dds");
	EXPECT_EQ(character.getAllowed(),
		 "{\n"
		 "\t\t\thas_dlc = \"La Resistance\"\n"
		 "\t\t}");
	EXPECT_EQ(character.getAllowedCivilWar(),
		 "{\n"
		 "\t\t\ttag = USA\n"
		 "\t\t\thas_government = communism\n"
		 "\t\t}");
	EXPECT_THAT(character.getPortraits(), testing::ElementsAre(portraitOne, portraitTwo));
	ASSERT_TRUE(character.getAdvisorData().has_value());
	EXPECT_EQ(character.getAdvisorData()->getSlot(), "political_advisor");
	EXPECT_EQ(character.getAdvisorData()->getIdeaToken(), "thomas_kinkaid");
	ASSERT_TRUE(character.getAdvisorData()->getAllowed().has_value());
	EXPECT_EQ(character.getAdvisorData()->getAllowed(),
		 "{\n"
		 "\t\t\t\toriginal_tag = USA\n"
		 "\t\t\t}");
	ASSERT_TRUE(character.getCountryLeaderData().has_value());
	EXPECT_EQ(character.getCountryLeaderData()->getIdeology(), "test_ideology");
	EXPECT_THAT(character.getCountryLeaderData()->getTraits(),
		 testing::ElementsAre("test_leader_trait_1", "test_leader_trait_2"));
	ASSERT_TRUE(character.getCommanderData().has_value());
	EXPECT_THAT(character.getCommanderData()->getTraits(),
		 testing::ElementsAre("test_commander_trait_1", "test_commander_trait_2"));
	EXPECT_EQ(character.getCommanderData()->getSkill(), 5);
	EXPECT_EQ(character.getCommanderData()->getAttackSkill(), 7);
	EXPECT_EQ(character.getCommanderData()->getDefenseSkill(), 3);
	EXPECT_EQ(character.getCommanderData()->getPlanningSkill(), 2);
	EXPECT_EQ(character.getCommanderData()->getLogisticsSkill(), 4);
	ASSERT_TRUE(character.getAdmiralData().has_value());
	EXPECT_THAT(character.getAdmiralData()->getTraits(),
		 testing::ElementsAre("test_admiral_trait_1", "test_admiral_trait_2"));
	EXPECT_EQ(character.getAdmiralData()->getSkill(), 5);
	EXPECT_EQ(character.getAdmiralData()->getAttackSkill(), 4);
	EXPECT_EQ(character.getAdmiralData()->getDefenseSkill(), 3);
	EXPECT_EQ(character.getAdmiralData()->getManeuveringSkill(), 2);
	EXPECT_EQ(character.getAdmiralData()->getCoordinationSkill(), 6);
}

TEST(HoI4World_Characters_CharacterFactory, CharacterInstanceCanBeImported)
{
	std::stringstream input;
	input << "={\n";
	input << "\t\tinstance={\n";
	input << "\t\t\tallowed = {\n";
	input << "\t\t\t\thas_dlc = \"La Resistance\"\n";
	input << "\t\t\t}\n";
	input << "\t\t\tname=TAG_test_character_name\n";
	input << "\t\t}\n";
	input << "\t\tinstance={\n";
	input << "\t\t\tallowed = {\n";
	input << "\t\t\t\tNOT = { has_dlc = \"La Resistance\" }\n";
	input << "\t\t\t}\n";
	input << "\t\t\tname=TAG_test_character_name\n";
	input << "\t\t}\n";
	input << "\t}\n";

	const auto character = HoI4::Character::Factory().importCharacter("TAG_test_character_id", input);

	std::stringstream inputOne;
	inputOne << "={\n";
	inputOne << "\t\t\tallowed = {\n";
	inputOne << "\t\t\t\thas_dlc = \"La Resistance\"\n";
	inputOne << "\t\t\t}\n";
	inputOne << "\t\t\tname=TAG_test_character_name\n";
	inputOne << "\t\t}\n";

	std::stringstream inputTwo;
	inputTwo << "={\n";
	inputTwo << "\t\t\tallowed = {\n";
	inputTwo << "\t\t\t\tNOT = { has_dlc = \"La Resistance\" }\n";
	inputTwo << "\t\t\t}\n";
	inputTwo << "\t\t\tname=TAG_test_character_name\n";
	inputTwo << "\t\t}\n";

	const auto instanceOne = HoI4::Character::Factory().importCharacter("instance", inputOne);
	const auto instanceTwo = HoI4::Character::Factory().importCharacter("instance", inputTwo);

	EXPECT_THAT(character.getInstances(), testing::ElementsAre(instanceOne, instanceTwo));
}