#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Pops/Pop.h"



using Vic2::Pop;
using Vic2::PopOptions;



TEST(Vic2World_Pops_PopTests, SupportForMissingIssueIsZero)
{
	const auto pop = Pop();

	EXPECT_FLOAT_EQ(0.0F, pop.getIssueSupport("missing_issue"));
}


TEST(Vic2World_Pops_PopTests, SupportForIssuesCanBeReturned)
{
	const auto pop = Pop(PopOptions{.popIssues{{"learn_the_question", 87.125F}}});

	EXPECT_FLOAT_EQ(87.125F, pop.getIssueSupport("learn_the_question"));
}