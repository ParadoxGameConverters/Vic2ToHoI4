#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Issues/IssuesFactory.h"
#include <sstream>



TEST(Vic2World_Issues_IssuesFactoryTests, IssuesDefaultToEmpty)
{
	const commonItems::ModFilesystem mod_filesystem("./EmptyIssues", {});
	const auto issues = Vic2::Issues::Factory().GetIssues(mod_filesystem);

	ASSERT_TRUE(issues->getIssueName(1).empty());
}


TEST(Vic2World_Issues_IssuesFactoryTests, IssuesCanBeImported)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto issues = Vic2::Issues::Factory().GetIssues(mod_filesystem);

	ASSERT_EQ("protectionism", issues->getIssueName(1));
	ASSERT_EQ("free_trade", issues->getIssueName(2));
	ASSERT_EQ("laissez_faire", issues->getIssueName(3));
	ASSERT_EQ("interventionism", issues->getIssueName(4));
	ASSERT_EQ("yes_slavery", issues->getIssueName(5));
	ASSERT_EQ("no_slavery", issues->getIssueName(6));
	ASSERT_EQ("none_voting", issues->getIssueName(7));
	ASSERT_EQ("landed_voting", issues->getIssueName(8));
}