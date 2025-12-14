#include "external/common_items/external/googletest/googlemock/test/gmock-matchers_test.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Factions/FactionTemplate.h"



TEST(HoI4World_Factions_FactionTemplate, DefaultNameIsSet)
{
	std::stringstream theStream;
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_EQ("default_template_name", theTemplate.getName());
}


TEST(HoI4World_Factions_FactionTemplate, NameCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "name = template_name\n";
	theStream << "}\n";
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_EQ("template_name", theTemplate.getName());
}


TEST(HoI4World_Factions_FactionTemplate, DefaultIconIsSet)
{
	std::stringstream theStream;
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_EQ("GFX_faction_logo_generic", theTemplate.getIcon());
}


TEST(HoI4World_Factions_FactionTemplate, IconCanBeSet)
{
	std::stringstream theStream;
	theStream << "icon = GFX_faction_icon_allies\n";
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_EQ("GFX_faction_icon_allies", theTemplate.getIcon());
}


TEST(HoI4World_Factions_FactionTemplate, DefaultManifestIsSet)
{
	std::stringstream theStream;
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_EQ("faction_manifest_regional_expansionism", theTemplate.getManifest());
}


TEST(HoI4World_Factions_FactionTemplate, ManifestCanBeSet)
{
	std::stringstream theStream;
	theStream << "manifest = faction_manifest_defense_of_democracy_allies\n";
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_EQ("faction_manifest_defense_of_democracy_allies", theTemplate.getManifest());
}


TEST(HoI4World_Factions_FactionTemplate, GoalsDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_TRUE(theTemplate.getGoals().empty());
}


TEST(HoI4World_Factions_FactionTemplate, GoalsCanBeSet)
{
	std::stringstream theStream;
	theStream << "\tgoals = {\n";
	theStream << "\t\tfaction_goal_air_superiority\n";
	theStream << "\t\tfaction_goal_rule_the_waves\n";
	theStream << "\t}";
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_THAT(theTemplate.getGoals(),
		 testing::ElementsAre("faction_goal_air_superiority", "faction_goal_rule_the_waves"));
}


TEST(HoI4World_Factions_FactionTemplate, GoalCanBeRemoved)
{
	std::stringstream theStream;
	theStream << "\tgoals = {\n";
	theStream << "\t\tfaction_goal_air_superiority\n";
	theStream << "\t\tfaction_goal_rule_the_waves\n";
	theStream << "\t}";
	HoI4::FactionTemplate theTemplate("test_template", theStream);
	theTemplate.removeGoal("faction_goal_air_superiority");

	EXPECT_THAT(theTemplate.getGoals(), testing::ElementsAre("faction_goal_rule_the_waves"));
}


TEST(HoI4World_Factions_FactionTemplate, RulesDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionTemplate theTemplate("test_template", theStream);

	EXPECT_TRUE(theTemplate.getRules().empty());
}


TEST(HoI4World_Factions_FactionTemplate, RulesCanBeSet)
{
	std::stringstream theStream;
	theStream << "\tdefault_rules = {\n";
	theStream << "\t\tjoining_rule_non_fascist\n";
	theStream << "\t\tjoining_rule_has_no_offensive_war\n";
	theStream << "\t}\n";
	HoI4::FactionTemplate theTemplate("test_template", theStream);


	EXPECT_THAT(theTemplate.getRules(),
		 testing::ElementsAre("joining_rule_non_fascist", "joining_rule_has_no_offensive_war"));
}


TEST(HoI4World_Factions_FactionTemplate, RuleCanBeAdded)
{
	std::stringstream theStream;
	theStream << "\tdefault_rules = {\n";
	theStream << "\t\tjoining_rule_non_fascist\n";
	theStream << "\t}\n";
	HoI4::FactionTemplate theTemplate("test_template", theStream);
	theTemplate.addRule("joining_rule_has_no_offensive_war");


	EXPECT_THAT(theTemplate.getRules(),
		 testing::ElementsAre("joining_rule_non_fascist", "joining_rule_has_no_offensive_war"));
}


TEST(HoI4World_Factions_FactionTemplate, RuleCanBeRemoved)
{
	std::stringstream theStream;
	theStream << "\tdefault_rules = {\n";
	theStream << "\t\tjoining_rule_non_fascist\n";
	theStream << "\t\tjoining_rule_has_no_offensive_war\n";
	theStream << "\t}\n";
	HoI4::FactionTemplate theTemplate("test_template", theStream);
	theTemplate.removeRule("joining_rule_non_fascist");


	EXPECT_THAT(theTemplate.getRules(), testing::ElementsAre("joining_rule_has_no_offensive_war"));
}