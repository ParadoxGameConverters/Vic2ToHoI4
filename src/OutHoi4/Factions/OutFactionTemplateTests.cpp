#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Factions/OutFactionTemplate.h"



TEST(OutHoI4World_Factions_FactionTemplate, CallToWarTemplateIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\tname = Allies\n";
	theStream << "\ticon = GFX_faction_icon_allies\n";
	theStream << "\tmanifest = faction_manifest_defense_of_democracy_allies\n";
	theStream << "\tgoals = {\n";
	theStream << "\t\tfaction_goal_air_superiority\n";
	theStream << "\t}\n";
	theStream << "\tdefault_rules = {\n";
	theStream << "\t\tchange_leader_rule_industry\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionTemplate theTemplate("faction_template_allies", theStream);

	std::stringstream output;
	output << theTemplate;

	std::stringstream expected;
	expected << "faction_template_allies = {\n";
	expected << "\tname = Allies\n";
	expected << "\ticon = GFX_faction_icon_allies\n";
	expected << "\tmanifest = faction_manifest_defense_of_democracy_allies\n";
	expected << "\tgoals = {\n";
	expected << "\t\tfaction_goal_air_superiority\n";
	expected << "\t}\n";
	expected << "\tdefault_rules = {\n";
	expected << "\t\tchange_leader_rule_industry\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}