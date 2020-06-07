#include "../../Vic2ToHoI4/Source/V2World/Pops/PopFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_Pops_PopFactoryTests: public testing::Test
{
	protected:
	Vic2World_Pops_PopFactoryTests(): popFactory(Vic2::Issues({})) {}

		Vic2::Pop::Factory popFactory;
};



TEST_F(Vic2World_Pops_PopFactoryTests, TypeCanBeSet)
{
	std::stringstream input;
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ("test_type", pop->getType());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureDefaultsToNoCulture)
{
	std::stringstream input;
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ("no_culture", pop->getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\ttest_culture=test_religion\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ("test_culture", pop->getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureIsNotSetToCon)
{
	std::stringstream input;
	input << "{\n";
	input << "\tcon=whatever\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ("no_culture", pop->getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, CultureIsNotSetToId)
{
	std::stringstream input;
	input << "{\n";
	input << "\tid=whatever\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ("no_culture", pop->getCulture());
}


TEST_F(Vic2World_Pops_PopFactoryTests, SizeDefaultsToZero)
{
	std::stringstream input;
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ(0, pop->getSize());
}


TEST_F(Vic2World_Pops_PopFactoryTests, SizecanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tsize=12345\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_EQ(12345, pop->getSize());
}


TEST_F(Vic2World_Pops_PopFactoryTests, LiteracyDefaultsToZero)
{
	std::stringstream input;
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_NEAR(0.0, pop->getLiteracy(), 0.0001);
}


TEST_F(Vic2World_Pops_PopFactoryTests, LiteracyCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tliteracy=0.42\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_NEAR(0.42, pop->getLiteracy(), 0.0001);
}


TEST_F(Vic2World_Pops_PopFactoryTests, MilitancyDefaultsToZero)
{
	std::stringstream input;
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_NEAR(0.0, pop->getMilitancy(), 0.0001);
}


TEST_F(Vic2World_Pops_PopFactoryTests, MilitancyCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tmil=0.42\n";
	input << "}";
	const auto pop = popFactory.getPop("test_type", input);

	ASSERT_NEAR(0.42, pop->getMilitancy(), 0.0001);
}