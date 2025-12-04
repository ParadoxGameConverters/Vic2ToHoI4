#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Factions/FactionGoal.h"



TEST(HoI4World_Factions_FactionGoal, DefaultNameIsSet)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("default_goal_name", theGoal.getName());
}


TEST(HoI4World_Factions_FactionGoal, NameCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "name = goal_name\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("goal_name", theGoal.getName());
}


TEST(HoI4World_Factions_FactionGoal, DefaultDescriptionIsSet)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("default_goal_desc", theGoal.getDescription());
}


TEST(HoI4World_Factions_FactionGoal, DescriptionCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "description = goal_desc\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("goal_desc", theGoal.getDescription());
}


TEST(HoI4World_Factions_FactionGoal, GroupHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getGroup().has_value());
}


TEST(HoI4World_Factions_FactionGoal, GroupCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "group = FOCUS_FILTER_CONSOLIDATION\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("FOCUS_FILTER_CONSOLIDATION", *theGoal.getGroup());
}


TEST(HoI4World_Factions_FactionGoal, CategoryHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getCategory().has_value());
}


TEST(HoI4World_Factions_FactionGoal, CategoryCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "category = long_term\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("long_term", *theGoal.getCategory());
}


TEST(HoI4World_Factions_FactionGoal, AllowedHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getAllowed().has_value());
}


TEST(HoI4World_Factions_FactionGoal, AllowedCanBeSet)
{
	std::stringstream theStream;
	theStream << "allowed = {\n";
	theStream << "\tis_literally_china = yes\n";
	theStream << "}";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tis_literally_china = yes\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getAllowed());
}


TEST(HoI4World_Factions_FactionGoal, VisibleHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getVisible().has_value());
}


TEST(HoI4World_Factions_FactionGoal, VisibleCanBeSet)
{
	std::stringstream theStream;
	theStream << "visible = {\n";
	theStream << "\tcollection_size = {\n";
	theStream << "\t}\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tcollection_size = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getVisible());
}


TEST(HoI4World_Factions_FactionGoal, LockedGoalDefaultsToFalse)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getLockedGoal());
}


TEST(HoI4World_Factions_FactionGoal, LockedGoalCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "locked_goal = yes\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getLockedGoal());
}


TEST(HoI4World_Factions_FactionGoal, AvailableHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getAvailable().has_value());
}


TEST(HoI4World_Factions_FactionGoal, AvailableCanBeSet)
{
	std::stringstream theStream;
	theStream << "available = {\n";
	theStream << "\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getAvailable());
}


TEST(HoI4World_Factions_FactionGoal, SelectEffectHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getSelectEffect().has_value());
}


TEST(HoI4World_Factions_FactionGoal, SelectEffectCanBeSet)
{
	std::stringstream theStream;
	theStream << "select_effect = {\n";
	theStream << "\tset_temp_variable = { total_techs = 0 }\n";
	theStream << "}";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tset_temp_variable = { total_techs = 0 }\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getSelectEffect());
}


TEST(HoI4World_Factions_FactionGoal, CancelHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getCancel().has_value());
}


TEST(HoI4World_Factions_FactionGoal, CancelCanBeSet)
{
	std::stringstream theStream;
	theStream << "cancel = {\n";
	theStream << "\tFROM = {\n";
	theStream << "\t\thas_country_flag = guardians_of_peace_been_at_war_flag\n";
	theStream << "\t}\n";
	theStream << "}";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tFROM = {\n";
	expectedOutput += "\t\thas_country_flag = guardians_of_peace_been_at_war_flag\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getCancel());
}


TEST(HoI4World_Factions_FactionGoal, AutoCompleteDefaultsToFalse)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getAutoComplete());
}


TEST(HoI4World_Factions_FactionGoal, AutoCompleteCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "auto_complete = yes\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getAutoComplete());
}


TEST(HoI4World_Factions_FactionGoal, CompletedHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getCompleted().has_value());
}


TEST(HoI4World_Factions_FactionGoal, CompletedCanBeSet)
{
	std::stringstream theStream;
	theStream << "completed = {\n";
	theStream << "\tcollection_size = {\n";
	theStream << "\t}\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tcollection_size = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getCompleted());
}


TEST(HoI4World_Factions_FactionGoal, CompleteEffectHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getCompleteEffect().has_value());
}


TEST(HoI4World_Factions_FactionGoal, CompleteEffectCanBeSet)
{
	std::stringstream theStream;
	theStream << "complete_effect = {\n";
	theStream << "\tadd_faction_power_projection = 500\n";
	theStream << "\tcustom_effect_tooltip = generic_skip_one_line_tt\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tadd_faction_power_projection = 500\n";
	expectedOutput += "\tcustom_effect_tooltip = generic_skip_one_line_tt\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getCompleteEffect());
}


TEST(HoI4World_Factions_FactionGoal, AiWillDoHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getAiWillDo().has_value());
}


TEST(HoI4World_Factions_FactionGoal, AiWillDoCanBeSet)
{
	std::stringstream theStream;
	theStream << "ai_will_do = {\n";
	theStream << "\tbase = 1\n";
	theStream << "}";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\tbase = 1\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getAiWillDo());
}


TEST(HoI4World_Factions_FactionGoal, IsManifestDefaultsToFalse)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getIsManifest());
}


TEST(HoI4World_Factions_FactionGoal, IsManifestCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "is_manifest = yes\n";
	theStream << "}";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getIsManifest());
}


TEST(HoI4World_Factions_FactionGoal, RatioProgressHasNoValueByDefault)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_FALSE(theGoal.getRatioProgress().has_value());
}


TEST(HoI4World_Factions_FactionGoal, RatioProgressCanBeSet)
{
	std::stringstream theStream;
	theStream << "ratio_progress = {\n";
	theStream << "\ttotal_amount = 40\n";
	theStream << "}";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	std::string expectedOutput;
	expectedOutput = "= {\n";
	expectedOutput += "\ttotal_amount = 40\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, *theGoal.getRatioProgress());
}