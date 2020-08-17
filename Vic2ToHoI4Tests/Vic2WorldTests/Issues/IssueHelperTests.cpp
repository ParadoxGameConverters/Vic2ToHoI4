#include "../../Vic2ToHoI4/Source/V2World/Issues/IssueHelper.h"
#include "gtest/gtest.h"



TEST(Vic2World_Issues_IssueHelperTests, IssuesDefaultsToEmpty)
{
	std::stringstream input;
	Vic2::IssueHelper helper(input);

	ASSERT_TRUE(helper.takeIssues().empty());
}


TEST(Vic2World_Issues_IssueHelperTests, IssuesCanBeAdded)
{
	std::stringstream input;
	input << "\twage_reform = {\n";
	input << "\t\tadministrative = yes\n";
	input << "\t\tnext_step_only = yes\n";
	input << "\t\tno_minimum_wage = {\n";
	input << "\t\t}\n";
	input << "\t\ttrinket_wage = {\n";
	input << "\t\t\tminimum_wage = 0.20\n";
	input << "\t\t\tadministrative_multiplier = 1\n";
	input << "\t\t\tglobal_immigrant_attract = 0.01\n";
	input << "\t\t}\n";
	input << "\t}\n";
	input << "\twork_hours = {\n";
	input << "\t\tadministrative = yes\n";
	input << "\t\tnext_step_only = yes\n";
	input << "\t\tno_work_hour_limit = {\n";
	input << "\t\t}\n";
	input << "\t\tfourteen_hours = {\n";
	input << "\t\t\tfactory_throughput = -0.05\n";
	input << "\t\t\tpoor_luxury_needs = -0.05\n";
	input << "\t\t\tmiddle_luxury_needs = -0.05\n";
	input << "\t\t\tadministrative_multiplier = 1\n";
	input << "\t\t\tglobal_immigrant_attract = 0.01\n";
	input << "\t\t}\n";
	input << "\t}";
	Vic2::IssueHelper helper(input);

	const auto issues = helper.takeIssues();
	ASSERT_EQ(2, issues.size());
	ASSERT_EQ("wage_reform", issues[0]);
	ASSERT_EQ("work_hours", issues[1]);
}