#include "src/OutHoi4/Characters/OutAdvisorData.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(OutHoI4World_Characters_OutAdvisorDataTests, AdvisorDataIsOutput)
{
	const HoI4::AdvisorData advisor_data("",
		 "",
		 std::nullopt,
		 std::nullopt,
		 "",
		 std::nullopt,
		 std::nullopt,
		 {},
		 std::nullopt,
		 std::nullopt,
		 std::nullopt);

	std::stringstream output;
	output << advisor_data;

	std::stringstream expected;
	expected << "\t\tadvisor={\n";
	expected << "\t\t\tslot = \n";
	expected << "\t\t\tidea_token = \n";
	expected << "\t\t\tallowed = \n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Characters_OutAdvisorDataTests, TraitsAreOutput)
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

	std::stringstream output;
	output << advisor_data;

	std::stringstream expected;
	expected << "\t\tadvisor={\n";
	expected << "\t\t\tslot = political_advisor\n";
	expected << "\t\t\tidea_token = thomas_kinkaid\n";
	expected << "\t\t\tledger = army\n";
	expected << "\t\t\tavailable = {\n";
	expected << "\t\t\t\tif = {\n";
	expected << "\t\t\t\t\tlimit = {\n";
	expected << "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n";
	expected << "\t\t\t\t\t}\n";
	expected << "\t\t\t\t\thas_completed_focus = USA_reach_out_to_the_ware_group\n";
	expected << "\t\t\t\t}\n";
	expected << "\t\t\t\tNOT = {\n";
	expected << "\t\t\t\t\thas_idea = USA_henry_morgenthau\n";
	expected << "\t\t\t\t}\n";
	expected << "\t\t\t}\n";
	expected << "\t\t\tallowed = {\n";
	expected << "\t\t\t\toriginal_tag = USA\n";
	expected << "\t\t\t}\n";
	expected << "\t\t\tvisible = {\n";
	expected << "\t\t\t\thas_dlc = \"Man the Guns\"\n";
	expected << "\t\t\t}\n";
	expected << "\t\t\tresearch_bonus = {\n";
	expected << "\t\t\t\tnuclear = 0.150\n";
	expected << "\t\t\t}\n";
	expected << "\t\t\ttraits = {\n";
	expected << "\t\t\t\tnuclear_scientist\n";
	expected << "\t\t\t\ttrait_two\n";
	expected << "\t\t\t}\n";
	expected << "\t\t\tcost = 100\n";
	expected << "\t\t\tdo_effect = {\n";
	expected << "\t\t\t\tNOT = {\n";
	expected << "\t\t\t\t\thas_government = communism\n";
	expected << "\t\t\t\t}\n";
	expected << "\t\t\t}\n";
	expected << "\t\t\tai_will_do = {\n";
	expected << "\t\t\t\tfactor = 10.000\n";
	expected << "\t\t\t\tmodifier = {\n";
	expected << "\t\t\t\t\tis_historical_focus_on = yes\n";
	expected << "\t\t\t\t\thas_game_rule = {\n";
	expected << "\t\t\t\t\t\trule = USA_ai_behavior\n";
	expected << "\t\t\t\t\t\toption = default\n";
	expected << "\t\t\t\t\t}\n";
	expected << "\t\t\t\t\tfactor = 0.000\n";
	expected << "\t\t\t\t}\n";
	expected << "\t\t\t\tmodifier = {\n";
	expected << "\t\t\t\t\tis_historical_focus_on = yes\n";
	expected << "\t\t\t\t\tNOT = {\n";
	expected << "\t\t\t\t\t\thas_dlc = \"Man the Guns\"\n";
	expected << "\t\t\t\t\t}\n";
	expected << "\t\t\t\t\tfactor = 0.000\n";
	expected << "\t\t\t\t}\n";
	expected << "\t\t\t}\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}