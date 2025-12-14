#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Factions/OutFactionTemplates.h"
#include <fstream>



using HoI4::FactionTemplate;



TEST(OutHoI4_Factions_OutFactionTemplates, FactionTemplatesAreOutput)
{
	std::filesystem::create_directories("OutHoI4Tests/Factions/common/factions/templates");

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
	FactionTemplate theTemplate("faction_template_allies", theStream);
	HoI4::outputFactionTemplates("OutHoI4Tests/Factions", {theTemplate});

	std::ifstream file("OutHoI4Tests/Factions/common/factions/templates/ideological_faction_templates.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

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
	expected << "\n";

	EXPECT_EQ(content, expected.str());
}