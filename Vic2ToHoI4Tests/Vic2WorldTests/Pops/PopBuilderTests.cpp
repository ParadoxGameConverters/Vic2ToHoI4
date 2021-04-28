#include "V2World/Pops/PopBuilder.h"
#include "gtest/gtest.h"



TEST(Vic2World_Pops_PopBuilderTests, TypeDefaultsToEmpty)
{
	const auto pop = Vic2::Pop::Builder().build();

	ASSERT_TRUE(pop->getType().empty());
}


TEST(Vic2World_Pops_PopBuilderTests, TypeCanBeSet)
{
	const auto pop = Vic2::Pop::Builder().setType("test_type").build();

	ASSERT_EQ("test_type", pop->getType());
}


TEST(Vic2World_Pops_PopBuilderTests, CultureDefaultsToNoCulture)
{
	const auto pop = Vic2::Pop::Builder().build();

	ASSERT_EQ("no_culture", pop->getCulture());
}


TEST(Vic2World_Pops_PopBuilderTests, CultureCanBeSet)
{
	const auto pop = Vic2::Pop::Builder().setCulture("test_culture").build();

	ASSERT_EQ("test_culture", pop->getCulture());
}


TEST(Vic2World_Pops_PopBuilderTests, SizeDefaultsToEmpty)
{
	const auto pop = Vic2::Pop::Builder().build();

	ASSERT_EQ(0, pop->getSize());
}


TEST(Vic2World_Pops_PopBuilderTests, SizeCanBeSet)
{
	const auto pop = Vic2::Pop::Builder().setSize(42).build();

	ASSERT_EQ(42, pop->getSize());
}


TEST(Vic2World_Pops_PopBuilderTests, LiteracyDefaultsToEmpty)
{
	const auto pop = Vic2::Pop::Builder().build();

	ASSERT_NEAR(0.0, pop->getLiteracy(), 0.0001);
}


TEST(Vic2World_Pops_PopBuilderTests, LiteracyCanBeSet)
{
	const auto pop = Vic2::Pop::Builder().setLiteracy(0.42).build();

	ASSERT_NEAR(0.42, pop->getLiteracy(), 0.0001);
}


TEST(Vic2World_Pops_PopBuilderTests, MilitancyDefaultsToEmpty)
{
	const auto pop = Vic2::Pop::Builder().build();

	ASSERT_NEAR(0.0, pop->getMilitancy(), 0.0001);
}


TEST(Vic2World_Pops_PopBuilderTests, MilitancyCanBeSet)
{
	const auto pop = Vic2::Pop::Builder().setMilitancy(0.42).build();

	ASSERT_NEAR(0.42, pop->getMilitancy(), 0.0001);
}