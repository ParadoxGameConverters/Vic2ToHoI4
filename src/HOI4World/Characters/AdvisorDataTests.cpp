#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/AdvisorData.h"
#include "src/HOI4World/Characters/AdvisorDataFactory.h"
#include <sstream>



TEST(HoI4World_Characters_AdvisorData, ItemsAreAsSet)
{
	const HoI4::AdvisorData advisor_data("",
		 "",
		 std::nullopt,
		 std::nullopt,
		 std::nullopt,
		 std::nullopt,
		 std::nullopt,
		 {},
		 std::nullopt,
		 std::nullopt,
		 std::nullopt);

	EXPECT_TRUE(advisor_data.getSlot().empty());
	EXPECT_TRUE(advisor_data.getIdeaToken().empty());
	EXPECT_FALSE(advisor_data.getLedger().has_value());
	EXPECT_FALSE(advisor_data.getAvailable().has_value());
	EXPECT_FALSE(advisor_data.getAllowed().has_value());
	EXPECT_FALSE(advisor_data.getVisible().has_value());
	EXPECT_FALSE(advisor_data.getResearchBonus().has_value());
	EXPECT_TRUE(advisor_data.getTraits().empty());
	EXPECT_FALSE(advisor_data.getCost().has_value());
	EXPECT_FALSE(advisor_data.getDoEffect().has_value());
	EXPECT_FALSE(advisor_data.getAiWillDo().has_value());
}


TEST(HoI4World_Characters_AdvisorData, TraitsCanBeSet)
{
	const HoI4::AdvisorData advisor_data("political_advisor",
		 "thomas_kinkaid",
		 "army",
		 "{\n"
		 "\t\t\t\tif = {\n"
		 "\t\t\t\t\tlimit = {\n"
		 "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\thas_completed_focus = USA_reach_out_to_the_ware_group\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_idea = USA_henry_morgenthau\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}",
		 "{\n"
		 "\t\t\t\toriginal_tag = USA\n"
		 "\t\t\t}",
		 "{\n"
		 "\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t}",
		 "{\n"
		 "\t\t\t\tnuclear = 0.150\n"
		 "\t\t\t}",
		 {"nuclear_scientist", "trait_two"},
		 100.0F,
		 "{\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_government = communism\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}",
		 "{\n"
		 "\t\t\t\tfactor = 10.000\n"
		 "\t\t\t\tmodifier = {\n"
		 "\t\t\t\t\tis_historical_focus_on = yes\n"
		 "\t\t\t\t\thas_game_rule = {\n"
		 "\t\t\t\t\t\trule = USA_ai_behavior\n"
		 "\t\t\t\t\t\toption = default\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tfactor = 0.000\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tmodifier = {\n"
		 "\t\t\t\t\tis_historical_focus_on = yes\n"
		 "\t\t\t\t\tNOT = {\n"
		 "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tfactor = 0.000\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");

	EXPECT_EQ(advisor_data.getSlot(), "political_advisor");
	EXPECT_EQ(advisor_data.getIdeaToken(), "thomas_kinkaid");
	ASSERT_TRUE(advisor_data.getLedger().has_value());
	EXPECT_EQ(advisor_data.getLedger(), "army");
	ASSERT_TRUE(advisor_data.getAvailable().has_value());
	EXPECT_EQ(*advisor_data.getAvailable(),
		 "{\n"
		 "\t\t\t\tif = {\n"
		 "\t\t\t\t\tlimit = {\n"
		 "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\thas_completed_focus = USA_reach_out_to_the_ware_group\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_idea = USA_henry_morgenthau\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getAllowed().has_value());
	EXPECT_EQ(advisor_data.getAllowed(),
		 "{\n"
		 "\t\t\t\toriginal_tag = USA\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getVisible().has_value());
	EXPECT_EQ(*advisor_data.getVisible(),
		 "{\n"
		 "\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getResearchBonus().has_value());
	EXPECT_EQ(*advisor_data.getResearchBonus(),
		 "{\n"
		 "\t\t\t\tnuclear = 0.150\n"
		 "\t\t\t}");
	EXPECT_THAT(advisor_data.getTraits(), testing::ElementsAre("nuclear_scientist", "trait_two"));
	ASSERT_TRUE(advisor_data.getCost().has_value());
	EXPECT_EQ(*advisor_data.getCost(), 100.0F);
	ASSERT_TRUE(advisor_data.getDoEffect().has_value());
	EXPECT_EQ(*advisor_data.getDoEffect(),
		 "{\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_government = communism\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getAiWillDo().has_value());
	EXPECT_EQ(*advisor_data.getAiWillDo(),
		 "{\n"
		 "\t\t\t\tfactor = 10.000\n"
		 "\t\t\t\tmodifier = {\n"
		 "\t\t\t\t\tis_historical_focus_on = yes\n"
		 "\t\t\t\t\thas_game_rule = {\n"
		 "\t\t\t\t\t\trule = USA_ai_behavior\n"
		 "\t\t\t\t\t\toption = default\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tfactor = 0.000\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tmodifier = {\n"
		 "\t\t\t\t\tis_historical_focus_on = yes\n"
		 "\t\t\t\t\tNOT = {\n"
		 "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tfactor = 0.000\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");
}


TEST(HoI4World_Characters_AdvisorData, ImportedItemsAreDefaulted)
{
	std::stringstream input;

	const HoI4::AdvisorData advisor_data = HoI4::AdvisorDataFactory().importAdvisorData(input);

	EXPECT_TRUE(advisor_data.getSlot().empty());
	EXPECT_TRUE(advisor_data.getIdeaToken().empty());
	EXPECT_FALSE(advisor_data.getLedger().has_value());
	EXPECT_FALSE(advisor_data.getAvailable().has_value());
	EXPECT_FALSE(advisor_data.getAllowed().has_value());
	EXPECT_FALSE(advisor_data.getVisible().has_value());
	EXPECT_FALSE(advisor_data.getResearchBonus().has_value());
	EXPECT_TRUE(advisor_data.getTraits().empty());
	EXPECT_FALSE(advisor_data.getCost().has_value());
	EXPECT_FALSE(advisor_data.getDoEffect().has_value());
	EXPECT_FALSE(advisor_data.getAiWillDo().has_value());
}


TEST(HoI4World_Characters_AdvisorData, ImportedItemsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tslot = political_advisor\n";
	input << "\t\t\tidea_token = thomas_kinkaid\n";
	input << "\t\t\tledger = army\n";
	input << "\t\t\tavailable = {\n";
	input << "\t\t\t\tif = {\n";
	input << "\t\t\t\t\tlimit = {\n";
	input << "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n";
	input << "\t\t\t\t\t}\n";
	input << "\t\t\t\t\thas_completed_focus = USA_reach_out_to_the_ware_group\n";
	input << "\t\t\t\t}\n";
	input << "\t\t\t\tNOT = {\n";
	input << "\t\t\t\t\thas_idea = USA_henry_morgenthau\n";
	input << "\t\t\t\t}\n";
	input << "\t\t\t}\n";
	input << "\t\t\tallowed = {\n";
	input << "\t\t\t\toriginal_tag = USA\n";
	input << "\t\t\t}\n";
	input << "\t\t\tvisible = {\n";
	input << "\t\t\t\thas_dlc = \"Man the Guns\"\n";
	input << "\t\t\t}\n";
	input << "\t\t\tresearch_bonus = {\n";
	input << "\t\t\t\tnuclear = 0.150\n";
	input << "\t\t\t}\n";
	input << "\t\t\ttraits = {\n";
	input << "\t\t\t\tnuclear_scientist\n";
	input << "\t\t\t\ttrait_two\n";
	input << "\t\t\t}\n";
	input << "\t\t\tcost = 100\n";
	input << "\t\t\tdo_effect = {\n";
	input << "\t\t\t\tNOT = {\n";
	input << "\t\t\t\t\thas_government = communism\n";
	input << "\t\t\t\t}\n";
	input << "\t\t\t}\n";
	input << "\t\t\tai_will_do = {\n";
	input << "\t\t\t\tfactor = 10.000\n";
	input << "\t\t\t\tmodifier = {\n";
	input << "\t\t\t\t\tis_historical_focus_on = yes\n";
	input << "\t\t\t\t\thas_game_rule = {\n";
	input << "\t\t\t\t\t\trule = USA_ai_behavior\n";
	input << "\t\t\t\t\t\toption = default\n";
	input << "\t\t\t\t\t}\n";
	input << "\t\t\t\t\tfactor = 0.000\n";
	input << "\t\t\t\t}\n";
	input << "\t\t\t\tmodifier = {\n";
	input << "\t\t\t\t\tis_historical_focus_on = yes\n";
	input << "\t\t\t\t\tNOT = {\n";
	input << "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n";
	input << "\t\t\t\t\t}\n";
	input << "\t\t\t\t\tfactor = 0.000\n";
	input << "\t\t\t\t}\n";
	input << "\t\t\t}";
	input << "\t\t}";

	const HoI4::AdvisorData advisor_data = HoI4::AdvisorDataFactory().importAdvisorData(input);

	EXPECT_EQ(advisor_data.getSlot(), "political_advisor");
	EXPECT_EQ(advisor_data.getIdeaToken(), "thomas_kinkaid");
	ASSERT_TRUE(advisor_data.getLedger().has_value());
	EXPECT_EQ(advisor_data.getLedger(), "army");
	ASSERT_TRUE(advisor_data.getAvailable().has_value());
	EXPECT_EQ(*advisor_data.getAvailable(),
		 "{\n"
		 "\t\t\t\tif = {\n"
		 "\t\t\t\t\tlimit = {\n"
		 "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\thas_completed_focus = USA_reach_out_to_the_ware_group\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_idea = USA_henry_morgenthau\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getAllowed().has_value());
	EXPECT_EQ(advisor_data.getAllowed(),
		 "{\n"
		 "\t\t\t\toriginal_tag = USA\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getVisible().has_value());
	EXPECT_EQ(*advisor_data.getVisible(),
		 "{\n"
		 "\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getResearchBonus().has_value());
	EXPECT_EQ(*advisor_data.getResearchBonus(),
		 "{\n"
		 "\t\t\t\tnuclear = 0.150\n"
		 "\t\t\t}");
	EXPECT_THAT(advisor_data.getTraits(), testing::ElementsAre("nuclear_scientist", "trait_two"));
	ASSERT_TRUE(advisor_data.getCost().has_value());
	EXPECT_EQ(*advisor_data.getCost(), 100.0F);
	ASSERT_TRUE(advisor_data.getDoEffect().has_value());
	EXPECT_EQ(*advisor_data.getDoEffect(),
		 "{\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_government = communism\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");
	ASSERT_TRUE(advisor_data.getAiWillDo().has_value());
	EXPECT_EQ(*advisor_data.getAiWillDo(),
		 "{\n"
		 "\t\t\t\tfactor = 10.000\n"
		 "\t\t\t\tmodifier = {\n"
		 "\t\t\t\t\tis_historical_focus_on = yes\n"
		 "\t\t\t\t\thas_game_rule = {\n"
		 "\t\t\t\t\t\trule = USA_ai_behavior\n"
		 "\t\t\t\t\t\toption = default\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tfactor = 0.000\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tmodifier = {\n"
		 "\t\t\t\t\tis_historical_focus_on = yes\n"
		 "\t\t\t\t\tNOT = {\n"
		 "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tfactor = 0.000\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}");
}