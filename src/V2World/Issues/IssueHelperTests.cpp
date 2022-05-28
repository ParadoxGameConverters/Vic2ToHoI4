#include "V2World/Issues/IssueHelper.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Issues_IssueHelperTests, IssuesDefaultsToEmpty)
{
	std::stringstream input;
	Vic2::IssueHelper helper(input);

	ASSERT_TRUE(helper.takeIssues().empty());
}


TEST(Vic2World_Issues_IssueHelperTests, IssuesCanBeAdded)
{
	std::stringstream input;
	input << "\t\tno_minimum_wage = {\n";
	input << "\t\t}\n";
	input << "\t\ttrinket_wage = {\n";
	input << "\t\t\tminimum_wage = 0.20\n";
	input << "\t\t\tadministrative_multiplier = 1\n";
	input << "\t\t\tglobal_immigrant_attract = 0.01\n";
	input << "\t\t}\n";
	Vic2::IssueHelper helper(input);

	const auto issues = helper.takeIssues();
	ASSERT_EQ(2, issues.size());
	ASSERT_EQ("no_minimum_wage", issues[0]);
	ASSERT_EQ("trinket_wage", issues[1]);
}


TEST(Vic2World_Issues_IssueHelperTests, AdministrativeIsIgnored)
{
	std::stringstream input;
	input << "\t\tadministrative = yes\n";
	input << "\t\tno_minimum_wage = {\n";
	input << "\t\t}\n";
	input << "\t\ttrinket_wage = {\n";
	input << "\t\t\tminimum_wage = 0.20\n";
	input << "\t\t\tadministrative_multiplier = 1\n";
	input << "\t\t\tglobal_immigrant_attract = 0.01\n";
	input << "\t\t}\n";
	Vic2::IssueHelper helper(input);

	const auto issues = helper.takeIssues();
	ASSERT_EQ(2, issues.size());
	ASSERT_EQ("no_minimum_wage", issues[0]);
	ASSERT_EQ("trinket_wage", issues[1]);
}


TEST(Vic2World_Issues_IssueHelperTests, NextStepOnlyIsIgnored)
{
	std::stringstream input;
	input << "\t\tnext_step_only = yes\n";
	input << "\t\tno_minimum_wage = {\n";
	input << "\t\t}\n";
	input << "\t\ttrinket_wage = {\n";
	input << "\t\t\tminimum_wage = 0.20\n";
	input << "\t\t\tadministrative_multiplier = 1\n";
	input << "\t\t\tglobal_immigrant_attract = 0.01\n";
	input << "\t\t}\n";
	Vic2::IssueHelper helper(input);

	const auto issues = helper.takeIssues();
	ASSERT_EQ(2, issues.size());
	ASSERT_EQ("no_minimum_wage", issues[0]);
	ASSERT_EQ("trinket_wage", issues[1]);
}