#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Factions/FactionRuleGroups.h"
#include "src/OutHoi4/Factions/OutFactionRuleGroups.h"
#include <fstream>



using HoI4::FactionRuleGroups;



TEST(OutHoI4_Factions_OutFactionRuleGroups, FactionRuleGroupsAreOutput)
{
	std::filesystem::create_directories("OutHoI4Tests/Factions/common/factions/rules/groups");

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\trules = {\n";
	theStream << "\t\tmanpower_contribution_small\n";
	theStream << "\t\tmanpower_contribution_medium\n";
	theStream << "\t\tmanpower_contribution_high\n";
	theStream << "\t}\n";
	theStream << "}";
	FactionRuleGroups groupRules(theStream);

	std::map<std::string, std::vector<std::string>> theRuleGroup;
	theRuleGroup.emplace("rule_group_manpower", groupRules.getRules());

	HoI4::outputFactionRuleGroups("OutHoI4Tests/Factions", theRuleGroup);

	std::ifstream file("OutHoI4Tests/Factions/common/factions/rules/groups/rule_groups.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::stringstream expected;
	expected << "rule_group_manpower = {\n";
	expected << "\trules = {\n";
	expected << "\t\tmanpower_contribution_small\n";
	expected << "\t\tmanpower_contribution_medium\n";
	expected << "\t\tmanpower_contribution_high\n";
	expected << "\t}\n";
	expected << "}\n";
	expected << "\n";

	EXPECT_EQ(content, expected.str());
}