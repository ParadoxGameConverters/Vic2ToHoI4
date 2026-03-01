#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Factions/OutFactionGoal.h"



TEST(OutHoI4World_Factions_FactionGoal, FactionGoalIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\tname = goal_name\n";
	theStream << "\tdescription = goal_desc\n";
	theStream << "\tgroup = FOCUS_FILTER_CONSOLIDATION\n";
	theStream << "\tcategory = long_term\n";
	theStream << "\tvisible = {\n";
	theStream << "\t\tcollection_size = {\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "\tlocked_goal = yes\n";
	theStream << "\tavailable = {\n";
	theStream << "\n";
	theStream << "\t}\n";
	theStream << "\tcompleted = {\n";
	theStream << "\t\tcollection_size = {\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "\tcomplete_effect = {\n";
	theStream << "\t\tadd_faction_power_projection = 500\n";
	theStream << "\t\tcustom_effect_tooltip = generic_skip_one_line_tt\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 1\n";
	theStream << "\t}\n";
	theStream << "}\n";
	const HoI4::FactionGoal theGoal("test_faction_goal", theStream);

	std::stringstream output;
	output << theGoal;

	std::stringstream expected;
	expected << "test_faction_goal = {\n";
	expected << "\tname = goal_name\n";
	expected << "\tdescription = goal_desc\n";
	expected << "\tgroup = FOCUS_FILTER_CONSOLIDATION\n";
	expected << "\tcategory = long_term\n";
	expected << "\tvisible = {\n";
	expected << "\t\tcollection_size = {\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "\tlocked_goal = yes\n";
	expected << "\tavailable = {\n";
	expected << "\n";
	expected << "\t}\n";
	expected << "\tcompleted = {\n";
	expected << "\t\tcollection_size = {\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "\tcomplete_effect = {\n";
	expected << "\t\tadd_faction_power_projection = 500\n";
	expected << "\t\tcustom_effect_tooltip = generic_skip_one_line_tt\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 1\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}

TEST(OutHoI4World_Factions_FactionGoal, ManifestIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\tname = goal_name\n";
	theStream << "\tdescription = goal_desc\n";
	theStream << "\tis_manifest = yes\n";
	theStream << "\tratio_progress = {\n";
	theStream << "\t\ttotal_amount = 40\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::FactionGoal theGoal("test_manifest", theStream);

	std::stringstream output;
	output << theGoal;

	std::stringstream expected;
	expected << "test_manifest = {\n";
	expected << "\tname = goal_name\n";
	expected << "\tdescription = goal_desc\n";
	expected << "\tis_manifest = yes\n";
	expected << "\tratio_progress = {\n";
	expected << "\t\ttotal_amount = 40\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}