#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Issues/IssueCategoryHelper.h"
#include <sstream>


TEST(Vic2World_Issues_IssueCategoryHelperTests, IssuesDefaultsToEmpty)
{
	std::stringstream input;
	Vic2::IssueCategoryHelper helper(input);

	ASSERT_TRUE(helper.takeIssues().empty());
}


TEST(Vic2World_Issues_IssueCategoryHelperTests, IssuesCanBeAdded)
{
	std::stringstream input;
	input << "\ttrade_policy = {\n";
	input << "\t\tprotectionism = {\n";
	input << "\t\t\tmax_tariff = 1\n";
	input << "\t\t\tmin_tariff = -0.25\n";
	input << "\t\t}\n";
	input << "\t\tfree_trade = {\n";
	input << "\t\t\tmax_tariff = 0.25\n";
	input << "\t\t\tmin_tariff = -1\n";
	input << "\t\t}\n";
	input << "\t}\n";
	input << "\treligious_policy = {\n";
	input << "\t\tpro_atheism = {\n";
	input << "\t\t\t#no effect\n";
	input << "\t\t}\n";
	input << "\t\tsecularized = {\n";
	input << "\t\t\t#no effect\n";
	input << "\t\t}\n";
	input << "\t\tpluralism = {\n";
	input << "\t\t\t#no effect\n";
	input << "\t\t}\n";
	input << "\t\tmoralism = {\n";
	input << "\t\t\t#no effect\n";
	input << "\t\t}\n";
	input << "\t}";
	Vic2::IssueCategoryHelper helper(input);

	const auto issues = helper.takeIssues();
	ASSERT_EQ(6, issues.size());
	ASSERT_EQ("protectionism", issues[0]);
	ASSERT_EQ("free_trade", issues[1]);
	ASSERT_EQ("pro_atheism", issues[2]);
	ASSERT_EQ("secularized", issues[3]);
	ASSERT_EQ("pluralism", issues[4]);
	ASSERT_EQ("moralism", issues[5]);
}