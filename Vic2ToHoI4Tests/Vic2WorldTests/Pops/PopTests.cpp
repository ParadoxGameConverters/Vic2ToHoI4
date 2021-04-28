#include "V2World/Pops/Pop.h"
#include "V2World/Pops/PopBuilder.h"
#include "gtest/gtest.h"



TEST(Vic2World_Pops_PopTests, SupportForMissingIssueIsZero)
{
	const auto pop = Vic2::Pop::Builder().build();

	ASSERT_NEAR(0.0, pop->getIssueSupport("missing_issue"), 0.001);
}


TEST(Vic2World_Pops_PopTests, SupportForIssuesCanBeReturned)
{
	const auto pop = Vic2::Pop::Builder().setIssues({{"learn_the_question", 87.125f}}).build();

	ASSERT_NEAR(87.125, pop->getIssueSupport("learn_the_question"), 0.001);
}