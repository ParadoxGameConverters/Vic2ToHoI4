#include "../../Vic2ToHoI4/Source/V2World/Pops/Pop.h"
#include "../../Vic2ToHoI4/Source/V2World/Pops/PopFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Pops_PopTests, SupportForMissingIssueIsZero)
{
	std::stringstream input;
	const auto pop = Vic2::Pop::Factory(Vic2::Issues({})).getPop("",input);

	ASSERT_NEAR(0.0, pop->getIssueSupport("missing_issue"), 0.001);
}


TEST(Vic2World_Pops_PopTests, SupportForIssuesCanBeReturned)
{
	std::stringstream input;
	input << "{\n";
	input << "\tissues={\n";
	input << "42=87.125\n";
	input << "\t}";
	input << "}";
	const auto pop = Vic2::Pop::Factory(Vic2::Issues({{42, "learn_the_question"}})).getPop("", input);

	ASSERT_NEAR(87.125, pop->getIssueSupport("learn_the_question"), 0.001);
}