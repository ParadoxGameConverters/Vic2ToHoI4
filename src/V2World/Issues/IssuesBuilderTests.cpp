#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Issues/IssuesBuilder.h"
#include <sstream>



TEST(Vic2World_Issues_IssuesBuilderTests, IssuesDefaultToEmpty)
{
	const auto issues = Vic2::Issues::Builder().build();

	ASSERT_TRUE(issues->getIssueName(1).empty());
}


TEST(Vic2World_Issues_IssuesBuilderTests, IssuesCanBeSet)
{
	const auto issues = Vic2::Issues::Builder().setIssueNames({"issue_1", "issue_2"}).build();

	ASSERT_EQ("issue_1", issues->getIssueName(1));
	ASSERT_EQ("issue_2", issues->getIssueName(2));
}


TEST(Vic2World_Issues_IssuesBuilderTests, IssuesCanBeAdded)
{
	const auto issues = Vic2::Issues::Builder().addIssueName("issue_1").build();

	ASSERT_EQ("issue_1", issues->getIssueName(1));
}