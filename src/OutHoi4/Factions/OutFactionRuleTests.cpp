#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Factions/OutFactionRule.h"



TEST(OutHoI4World_Factions_FactionRule, CallToWarRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = call_to_war_rules\n";
	theStream << "\ttrigger = {\n";
	theStream << "\t\tis_faction_leader = yes\n";
	theStream << "\t}\n";
	theStream << "\tmodifier = {\n";
	theStream << "\t\tpolitical_power_factor = -0.1\n";
	theStream << "\t}\n";
	theStream << "\teffect = {\n";
	theStream << "\t\tadd_stability = -0.05\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t\tmodifier = { \n";
	theStream << "\t\t\tadd = 2\n";
	theStream << "\t\t\tis_faction_leader = yes\n";
	theStream << "\t\t\tNOT = { has_government = democratic }\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("call_to_war_rule_faction_leader_only", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "call_to_war_rule_faction_leader_only = {\n";
	expected << "\ttype = call_to_war_rules\n";
	expected << "\ttrigger = {\n";
	expected << "\t\tis_faction_leader = yes\n";
	expected << "\t}\n";
	expected << "\tmodifier = {\n";
	expected << "\t\tpolitical_power_factor = -0.1\n";
	expected << "\t}\n";
	expected << "\teffect = {\n";
	expected << "\t\tadd_stability = -0.05\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t\tmodifier = { \n";
	expected << "\t\t\tadd = 2\n";
	expected << "\t\t\tis_faction_leader = yes\n";
	expected << "\t\t\tNOT = { has_government = democratic }\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, ChangeLeaderRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = change_leader_rules\n";
	theStream << "\ttrigger = {\n";
	theStream << "\t\talways = no\n";
	theStream << "\t}\n";
	theStream << "\tavailable = {\n";
	theStream << "\t\tfaction_manifest_fulfillment > 0.66\n";
	theStream << "\t}\n";
	theStream << "\n";
	theStream << "\tcan_remove = { \n";
	theStream << "\t\tfaction_manifest_fulfillment < 0.5 \n";
	theStream << "\t}\n";
	theStream << "\n";
	theStream << "\tmodifier = {\n";
	theStream << "\t\tresearch_sharing_per_country_bonus_factor = -0.25\n";
	theStream << "\t\tsurrender_limit = -0.05\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t\tmodifier = {  \n";
	theStream << "\t\t\tadd = 5\n";
	theStream << "\t\t\thas_government = fascism\n";
	theStream << "\t\t\tis_faction_leader = yes \n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("change_leader_rule_never", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "change_leader_rule_never = {\n";
	expected << "\ttype = change_leader_rules\n";
	expected << "\tavailable = {\n";
	expected << "\t\tfaction_manifest_fulfillment > 0.66\n";
	expected << "\t}\n";
	expected << "\tcan_remove = { \n";
	expected << "\t\tfaction_manifest_fulfillment < 0.5 \n";
	expected << "\t}\n";
	expected << "\ttrigger = {\n";
	expected << "\t\talways = no\n";
	expected << "\t}\n";
	expected << "\tmodifier = {\n";
	expected << "\t\tresearch_sharing_per_country_bonus_factor = -0.25\n";
	expected << "\t\tsurrender_limit = -0.05\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t\tmodifier = {  \n";
	expected << "\t\t\tadd = 5\n";
	expected << "\t\t\thas_government = fascism\n";
	expected << "\t\t\tis_faction_leader = yes \n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, DismissalRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = dismissal_rules\n";
	theStream << "\tvisible = { has_government = communism }\n";
	theStream << "\tdismiss_member_trigger = {\n";
	theStream << "\t\thas_added_tension_amount > 0.1\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t\tmodifier = {  \n";
	theStream << "\t\t\tadd = 1\n";
	theStream << "\t\t\thas_government = democratic\n";
	theStream << "\t\t\tis_faction_leader = yes \n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("dismissal_rule_world_tension", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "dismissal_rule_world_tension = {\n";
	expected << "\ttype = dismissal_rules\n";
	expected << "\tvisible = { has_government = communism }\n";
	expected << "\tdismiss_member_trigger = {\n";
	expected << "\t\thas_added_tension_amount > 0.1\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t\tmodifier = {  \n";
	expected << "\t\t\tadd = 1\n";
	expected << "\t\t\thas_government = democratic\n";
	expected << "\t\t\tis_faction_leader = yes \n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, GovernmentInExileRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = member_rules\n";
	theStream << "\tgovernment_in_exile_allowed_trigger = {\n";
	theStream << "\t\talways = yes\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t\tmodifier = {  \n";
	theStream << "\t\t\tadd = 1\n";
	theStream << "\t\t\thas_faction_template = faction_template_the_little_entente\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("government_in_exile_allowed", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "government_in_exile_allowed = {\n";
	expected << "\ttype = member_rules\n";
	expected << "\tgovernment_in_exile_allowed_trigger = {\n";
	expected << "\t\talways = yes\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t\tmodifier = {  \n";
	expected << "\t\t\tadd = 1\n";
	expected << "\t\t\thas_faction_template = faction_template_the_little_entente\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, JoiningRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = joining_rules\n";
	theStream << "\tvisible = {\n";
	theStream << "\t\tNOT = { has_government = fascism }\n";
	theStream << "\t}\n";
	theStream << "\tavailable = {\n";
	theStream << "\t}\n";
	theStream << "\tcan_remove = {\n";
	theStream << "\t}\n";
	theStream << "\ttrigger = {\n";
	theStream << "\t\tNOT = {\n";
	theStream << "\t\t\thas_government = fascism\n";
	theStream << "\t\t}\n";
	theStream << "\t\tIF = {\n";
	theStream << "\t\t\tlimit = { NOT = { has_rule = can_join_opposite_factions } }\n";
	theStream << "\t\t\thas_government = FROM\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "\tmodifier= {\n";
	theStream << "\t\tsubjects_autonomy_gain = -0.05\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t\tmodifier = {\n";
	theStream << "\t\t\tadd = 1\n";
	theStream << "\t\t\tNOT = { has_government = fascism }\n";
	theStream << "\t\t}\n";
	theStream << "\t\tmodifier = {\n";
	theStream << "\t\t\tadd = 1\n";
	theStream << "\t\t\thas_government = communism\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("joining_rule_non_fascist", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "joining_rule_non_fascist = {\n";
	expected << "\ttype = joining_rules\n";
	expected << "\tvisible = {\n";
	expected << "\t\tNOT = { has_government = fascism }\n";
	expected << "\t}\n";
	expected << "\tavailable = {\n";
	expected << "\t}\n";
	expected << "\tcan_remove = {\n";
	expected << "\t}\n";
	expected << "\ttrigger = {\n";
	expected << "\t\tNOT = {\n";
	expected << "\t\t\thas_government = fascism\n";
	expected << "\t\t}\n";
	expected << "\t\tIF = {\n";
	expected << "\t\t\tlimit = { NOT = { has_rule = can_join_opposite_factions } }\n";
	expected << "\t\t\thas_government = FROM\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "\tmodifier = {\n";
	expected << "\t\tsubjects_autonomy_gain = -0.05\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t\tmodifier = {\n";
	expected << "\t\t\tadd = 1\n";
	expected << "\t\t\tNOT = { has_government = fascism }\n";
	expected << "\t\t}\n";
	expected << "\t\tmodifier = {\n";
	expected << "\t\t\tadd = 1\n";
	expected << "\t\t\thas_government = communism\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, ManpowerContributionRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = contribution_rule\n";
	theStream << "\tavailable = {\n";
	theStream << "\t\thas_faction_military_unlocked = yes\n";
	theStream << "\t}\n";
	theStream << "\teffect = {\n";
	theStream << "\t\tset_faction_member_upgrade_min = {\n";
	theStream << "\t\t\tupgrade = faction_manpower_sharing1\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("manpower_contribution_small", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "manpower_contribution_small = {\n";
	expected << "\ttype = contribution_rule\n";
	expected << "\tavailable = {\n";
	expected << "\t\thas_faction_military_unlocked = yes\n";
	expected << "\t}\n";
	expected << "\teffect = {\n";
	expected << "\t\tset_faction_member_upgrade_min = {\n";
	expected << "\t\t\tupgrade = faction_manpower_sharing1\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, PeaceRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = peace_conference_rules\n";
	theStream << "\tvisible = { original_tag = JAP }\n";
	theStream << "\tcan_remove = {\n";
	theStream << "\t\tfaction_manifest_fulfillment > 0.95\n";
	theStream << "\t}\n";
	theStream << "\tpeace_action_modifiers = {\n";
	theStream << "\t\tfaction_rule_modifier_encourage_chinese_states\n";
	theStream << "\t}\n";
	theStream << "\tmodifier = {\n";
	theStream << "\t\tcustom_modifier_tooltip = faction_rule_modifier_encourage_chinese_states_tt\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("faction_peace_china_focus", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "faction_peace_china_focus = {\n";
	expected << "\ttype = peace_conference_rules\n";
	expected << "\tvisible = { original_tag = JAP }\n";
	expected << "\tcan_remove = {\n";
	expected << "\t\tfaction_manifest_fulfillment > 0.95\n";
	expected << "\t}\n";
	expected << "\tpeace_action_modifiers = {\n";
	expected << "\t\tfaction_rule_modifier_encourage_chinese_states\n";
	expected << "\t}\n";
	expected << "\tmodifier = {\n";
	expected << "\t\tcustom_modifier_tooltip = faction_rule_modifier_encourage_chinese_states_tt\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Factions_FactionRule, WarDeclarationRuleIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = war_declaration_rules\n";
	theStream << "\ttrigger = {\n";
	theStream << "\t\tis_faction_leader = yes\n";
	theStream << "\t}\n";
	theStream << "\tmodifier = {\n";
	theStream << "\t\twar_support_factor = -0.05\n";
	theStream << "\t\tstability_factor = -0.05\n";
	theStream << "\t}\n";
	theStream << "\teffect = {\n";
	theStream << "\t\tadd_stability = -0.05\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 0\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionRule theRule("war_declaration_rule_faction_leader_only", theStream);

	std::stringstream output;
	output << theRule;

	std::stringstream expected;
	expected << "war_declaration_rule_faction_leader_only = {\n";
	expected << "\ttype = war_declaration_rules\n";
	expected << "\ttrigger = {\n";
	expected << "\t\tis_faction_leader = yes\n";
	expected << "\t}\n";
	expected << "\tmodifier = {\n";
	expected << "\t\twar_support_factor = -0.05\n";
	expected << "\t\tstability_factor = -0.05\n";
	expected << "\t}\n";
	expected << "\teffect = {\n";
	expected << "\t\tadd_stability = -0.05\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 0\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}