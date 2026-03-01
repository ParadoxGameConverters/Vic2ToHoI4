#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Factions/OutFactionRules.h"
#include <fstream>



using HoI4::FactionRule;



TEST(OutHoI4_Factions_OutFactionRules, FactionRulesAreOutput)
{
	std::filesystem::create_directories("OutHoI4Tests/Factions/common/factions/rules");

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\ttype = call_to_war_rules\n";
	theStream << "\tvisible = { has_government = communism }\n";
	theStream << "\tavailable = {\n";
	theStream << "\t\tfaction_manifest_fulfillment > 0.66\n";
	theStream << "\t}\n";
	theStream << "\tcan_remove = {\n";
	theStream << "\t\tfaction_manifest_fulfillment < 0.5\n";
	theStream << "\t}\n";
	theStream << "\ttrigger = {\n";
	theStream << "\t\tis_faction_leader = yes\n";
	theStream << "\t}\n";
	theStream << "\tdismiss_member_trigger = {\n";
	theStream << "\t\thas_added_tension_amount > 0.1\n";
	theStream << "\t}\n";
	theStream << "\tgovernment_in_exile_allowed_trigger = {\n";
	theStream << "\t\talways = yes\n";
	theStream << "\t}\n";
	theStream << "\tpeace_action_modifiers = {\n";
	theStream << "\t\tfaction_rule_modifier_encourage_chinese_states\n";
	theStream << "\t}\n";
	theStream << "\tmodifier = {\n";
	theStream << "\t\tcustom_modifier_tooltip = faction_rule_modifier_encourage_chinese_states_tt\n";
	theStream << "\t}\n";
	theStream << "\teffect = {\n";
	theStream << "\t\tadd_stability = -0.05\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 1\n";
	theStream << "\t}\n";
	theStream << "}";
	FactionRule theRule("test_faction_rule", theStream);
	HoI4::outputFactionRules("OutHoI4Tests/Factions", {theRule});

	std::ifstream file("OutHoI4Tests/Factions/common/factions/rules/ideological_faction_rules.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::stringstream expected;
	expected << "test_faction_rule = {\n";
	expected << "\ttype = call_to_war_rules\n";
	expected << "\tvisible = { has_government = communism }\n";
	expected << "\tavailable = {\n";
	expected << "\t\tfaction_manifest_fulfillment > 0.66\n";
	expected << "\t}\n";
	expected << "\tcan_remove = {\n";
	expected << "\t\tfaction_manifest_fulfillment < 0.5\n";
	expected << "\t}\n";
	expected << "\ttrigger = {\n";
	expected << "\t\tis_faction_leader = yes\n";
	expected << "\t}\n";
	expected << "\tdismiss_member_trigger = {\n";
	expected << "\t\thas_added_tension_amount > 0.1\n";
	expected << "\t}\n";
	expected << "\tgovernment_in_exile_allowed_trigger = {\n";
	expected << "\t\talways = yes\n";
	expected << "\t}\n";
	expected << "\tpeace_action_modifiers = {\n";
	expected << "\t\tfaction_rule_modifier_encourage_chinese_states\n";
	expected << "\t}\n";
	expected << "\tmodifier = {\n";
	expected << "\t\tcustom_modifier_tooltip = faction_rule_modifier_encourage_chinese_states_tt\n";
	expected << "\t}\n";
	expected << "\teffect = {\n";
	expected << "\t\tadd_stability = -0.05\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 1\n";
	expected << "\t}\n";
	expected << "}\n";
	expected << "\n";

	EXPECT_EQ(content, expected.str());
}