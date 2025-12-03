#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Factions/FactionGoals.h"
#include <ranges>


TEST(HoI4World_Factions_FactionGoals, FactionGoalsCanBeImported)
{
	HoI4::FactionGoals goals;
	goals.importFactionGoals(std::filesystem::path("Configurables") / "faction_goals.txt");

	std::stringstream output;
	for (const auto& goal: goals.getFactionGoals() | std::views::values)
	{
		output << *goal;
	}

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
	expected << "}\n";
	expected << "\n";

	EXPECT_EQ(output.str(), expected.str());
}