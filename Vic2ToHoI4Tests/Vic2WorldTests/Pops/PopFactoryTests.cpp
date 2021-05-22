#include "V2World/Issues/IssuesBuilder.h"
#include "V2World/Pops/PopFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_Pops_PopFactoryTests: public testing::Test
{
  protected:
	Vic2World_Pops_PopFactoryTests(): popFactory(Vic2::Issues()) {}

	Vic2::Pop::Factory popFactory;
};



TEST_F(Vic2World_Pops_PopFactoryTests, DefaultsAreSet)
{
	std::stringstream input;
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_EQ("test_type", pop.getType());
	EXPECT_EQ("no_culture", pop.getCulture());
	EXPECT_EQ(0, pop.getSize());
	EXPECT_DOUBLE_EQ(0.0, pop.getLiteracy());
	EXPECT_DOUBLE_EQ(0.0, pop.getMilitancy());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\ttest_culture=test_religion\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_EQ("test_culture", pop.getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureIsNotSetToCon)
{
	std::stringstream input;
	input << "{\n";
	input << "\tcon=whatever\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_EQ("no_culture", pop.getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureIsNotSetToId)
{
	std::stringstream input;
	input << "{\n";
	input << "\tid=whatever\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_EQ("no_culture", pop.getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureIsOnlySetOnce)
{
	std::stringstream input;
	input << "{\n";
	input << "\ttest_culture=test_religion\n";
	input << "\ttest_culture_two=test_religion_two\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_EQ("test_culture", pop.getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, SizecanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tsize=12345\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_EQ(12345, pop.getSize());
}


TEST_F(Vic2World_Pops_PopFactoryTests, LiteracyCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tliteracy=0.42\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_DOUBLE_EQ(0.42, pop.getLiteracy());
}


TEST_F(Vic2World_Pops_PopFactoryTests, MilitancyCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tmil=0.42\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	EXPECT_DOUBLE_EQ(0.42, pop.getMilitancy());
}


TEST_F(Vic2World_Pops_PopFactoryTests, IssueWithNonIntegerIssueNumberLogsWarning)
{
	std::stringstream input;
	input << "{\n";
	input << "\tissues = {\n";
	input << "\tnot_an_int=87.125\n";
	input << "\t}\n";
	input << "}";

	const std::stringstream log;
	auto* const stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto pop = popFactory.getPop("test_type", input);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_EQ(" [WARNING] Poorly formatted pop issue: not_an_int=87.125\n", log.str());
}


TEST_F(Vic2World_Pops_PopFactoryTests, IssueWithNonFloatIssueSupportLogsWarning)
{
	std::stringstream input;
	input << "{\n";
	input << "\tissues = {\n";
	input << "\t42=not_a_float\n";
	input << "\t}\n";
	input << "}";

	const std::stringstream log;
	auto* const stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto pop = popFactory.getPop("test_type", input);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_EQ(" [WARNING] Poorly formatted pop issue: 42=not_a_float\n", log.str());
}


TEST(Vic2World_Pops_PopTests, IssuesCanBeImported)
{
	std::stringstream input;
	input << "{\n";
	input << "\tissues={\n";
	input << "1=87.125\n";
	input << "\t}";
	input << "}";
	const auto pop =
		 Vic2::Pop::Factory(*Vic2::Issues::Builder().addIssueName("learn_the_question").build()).getPop("", input);

	EXPECT_FLOAT_EQ(87.125F, pop.getIssueSupport("learn_the_question"));
}