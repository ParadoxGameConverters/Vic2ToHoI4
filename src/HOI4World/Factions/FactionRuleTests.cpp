#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Factions/FactionRule.h"



TEST(HoI4World_Factions_FactionRule, DefaultTypeIsSet)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_EQ("default_rule_type", theRule.getType());
}


TEST(HoI4World_Factions_FactionRule, TypeCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "type = rule_type\n";
	theStream << "}\n";
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_EQ("rule_type", theRule.getType());
}


TEST(HoI4World_Factions_FactionRule, VisibleHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getVisible().has_value());
}


TEST(HoI4World_Factions_FactionRule, VisibleCanBeSet)
{
	std::stringstream theStream;
	theStream << "visible = { has_government = democratic }\n";
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_EQ("= { has_government = democratic }", *theRule.getVisible());
}


TEST(HoI4World_Factions_FactionRule, AvailableHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getAvailable().has_value());
}


TEST(HoI4World_Factions_FactionRule, AvailableCanBeSet)
{
	std::stringstream theStream;
	theStream << "available = {\n";
	theStream << "\thas_government = fascism\n";
	theStream << "}\n";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\thas_government = fascism\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getAvailable());
}


TEST(HoI4World_Factions_FactionRule, CanRemoveHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getCanRemove().has_value());
}


TEST(HoI4World_Factions_FactionRule, CanRemoveCanBeSet)
{
	std::stringstream theStream;
	theStream << "can_remove = {\n";
	theStream << "\tfaction_manifest_fulfillment > 0.95\n";
	theStream << "}";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tfaction_manifest_fulfillment > 0.95\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getCanRemove());
}


TEST(HoI4World_Factions_FactionRule, TriggerHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getTrigger().has_value());
}


TEST(HoI4World_Factions_FactionRule, TriggerCanBeSet)
{
	std::stringstream theStream;
	theStream << "trigger = {\n";
	theStream << "\tis_faction_leader = yes\n";
	theStream << "}";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tis_faction_leader = yes\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getTrigger());
}


TEST(HoI4World_Factions_FactionRule, DismissMemberTriggerHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getDismissMemberTrigger().has_value());
}


TEST(HoI4World_Factions_FactionRule, DismissMemberTriggerCanBeSet)
{
	std::stringstream theStream;
	theStream << "dismiss_member_trigger = {\n";
	theStream << "\thas_added_tension_amount > 0.1\n";
	theStream << "}\n";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\thas_added_tension_amount > 0.1\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getDismissMemberTrigger());
}


TEST(HoI4World_Factions_FactionRule, GovernmentInExileAllowedTriggerHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getGovernmentInExileAllowedTrigger().has_value());
}


TEST(HoI4World_Factions_FactionRule, GovernmentInExileAllowedTriggerCanBeSet)
{
	std::stringstream theStream;
	theStream << "government_in_exile_allowed_trigger = {\n";
	theStream << "\talways = yes\n";
	theStream << "}";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\talways = yes\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getGovernmentInExileAllowedTrigger());
}


TEST(HoI4World_Factions_FactionRule, PeaceActionModifiersHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getPeaceActionModifiers().has_value());
}


TEST(HoI4World_Factions_FactionRule, PeaceActionModifiersCanBeSet)
{
	std::stringstream theStream;
	theStream << "peace_action_modifiers = {\n";
	theStream << "\tfaction_rule_modifier_encourage_take_claimed_states\n";
	theStream << "}";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tfaction_rule_modifier_encourage_take_claimed_states\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getPeaceActionModifiers());
}


TEST(HoI4World_Factions_FactionRule, ModifierHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getModifier().has_value());
}


TEST(HoI4World_Factions_FactionRule, ModifierCanBeSet)
{
	std::stringstream theStream;
	theStream << "modifier = {\n";
	theStream << "\tpolitical_power_factor = -0.1\n";
	theStream << "}\n";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tpolitical_power_factor = -0.1\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getModifier());
}


TEST(HoI4World_Factions_FactionRule, EffectHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getEffect().has_value());
}


TEST(HoI4World_Factions_FactionRule, EffectCanBeSet)
{
	std::stringstream theStream;
	theStream << "effect = {\n";
	theStream << "\tset_faction_member_upgrade_min = {\n";
	theStream << "\t\tupgrade = faction_manpower_sharing1\n";
	theStream << "\t}\n";
	theStream << "}";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tset_faction_member_upgrade_min = {\n";
	expectedOutput += "\t\tupgrade = faction_manpower_sharing1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getEffect());
}


TEST(HoI4World_Factions_FactionRule, AiWillDoHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionRule theRule("test_rule", theStream);

	EXPECT_FALSE(theRule.getAiWillDo().has_value());
}


TEST(HoI4World_Factions_FactionRule, AiWillDoCanBeSet)
{
	std::stringstream theStream;
	theStream << "ai_will_do = {\n";
	theStream << "\tbase = 1\n";
	theStream << "}";
	HoI4::FactionRule theRule("test_rule", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tbase = 1\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theRule.getAiWillDo());
}