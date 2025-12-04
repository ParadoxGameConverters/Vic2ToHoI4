#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Factions/OutFactionGoals.h"
#include <fstream>



using HoI4::FactionGoal;



TEST(OutHoI4_Factions_OutFactionGoals, FactionGoalsAreOutput)
{
	std::filesystem::create_directories("OutHoI4Tests/Factions/common/factions/goals");

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
	theStream << "\t}\n";
	theStream << "\tcompleted = {\n";
	theStream << "\t\tcollection_size = {\n";
	theStream << "\t\t}\n";
	theStream << "\t\t\n";
	theStream << "\t}\n";
	theStream << "\tcomplete_effect = {\n";
	theStream << "\t\tadd_faction_power_projection = 500\n";
	theStream << "\t}\n";
	theStream << "\tai_will_do = {\n";
	theStream << "\t\tbase = 1\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto& theGoal = std::make_shared<FactionGoal>("test_faction_goal", theStream);
	HoI4::outputFactionGoals("OutHoI4Tests/Factions", {theGoal});

	std::ifstream file("OutHoI4Tests/Factions/common/factions/goals/ideological_faction_goals.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

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
	expected << "\t}\n";
	expected << "\tcompleted = {\n";
	expected << "\t\tcollection_size = {\n";
	expected << "\t\t}\n";
	expected << "\t\t\n";
	expected << "\t}\n";
	expected << "\tcomplete_effect = {\n";
	expected << "\t\tadd_faction_power_projection = 500\n";
	expected << "\t}\n";
	expected << "\tai_will_do = {\n";
	expected << "\t\tbase = 1\n";
	expected << "\t}\n";
	expected << "}\n";
	expected << "\n";
	EXPECT_EQ(content, expected.str());
}