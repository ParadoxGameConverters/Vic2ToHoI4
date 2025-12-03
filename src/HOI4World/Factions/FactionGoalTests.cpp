#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Factions/FactionGoal.h"



TEST(HoI4World_Factions_FactionGoal, NameDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getName().empty());
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


TEST(HoI4World_Factions_FactionGoal, DescriptionDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getDescription().empty());
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


TEST(HoI4World_Factions_FactionGoal, GroupDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getGroup().empty());
}


TEST(HoI4World_Factions_FactionGoal, GroupCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "group = FOCUS_FILTER_CONSOLIDATION\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("FOCUS_FILTER_CONSOLIDATION", theGoal.getGroup());
}


TEST(HoI4World_Factions_FactionGoal, CategoryDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getCategory().empty());
}


TEST(HoI4World_Factions_FactionGoal, CategoryCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "category = long_term\n";
	theStream << "}\n";
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_EQ("long_term", theGoal.getCategory());
}


TEST(HoI4World_Factions_FactionGoal, VisibleDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getVisible().empty());
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

	EXPECT_EQ(expectedOutput, theGoal.getVisible());
}


TEST(HoI4World_Factions_FactionGoal, LockedGaolDefaultsToFalse)
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


TEST(HoI4World_Factions_FactionGoal, AvailableDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getAvailable().empty());
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

	EXPECT_EQ(expectedOutput, theGoal.getAvailable());
}


TEST(HoI4World_Factions_FactionGoal, CompletedDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getCompleted().empty());
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

	EXPECT_EQ(expectedOutput, theGoal.getCompleted());
}


TEST(HoI4World_Factions_FactionGoal, CompleteEffectDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getCompleteEffect().empty());
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

	EXPECT_EQ(expectedOutput, theGoal.getCompleteEffect());
}


TEST(HoI4World_Factions_FactionGoal, AiWillDoDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getAiWillDo().empty());
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

	EXPECT_EQ(expectedOutput, theGoal.getAiWillDo());
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


TEST(HoI4World_Factions_FactionGoal, RatioProgressDefaultsToEmpty)
{
	std::stringstream theStream;
	HoI4::FactionGoal theGoal("test_goal", theStream);

	EXPECT_TRUE(theGoal.getRatioProgress().empty());
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

	EXPECT_EQ(expectedOutput, theGoal.getRatioProgress());
}