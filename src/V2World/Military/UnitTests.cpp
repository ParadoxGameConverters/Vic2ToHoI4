#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Military/Unit.h"
#include "src/V2World/Military/UnitFactory.h"
#include <gmock/gmock-matchers.h>
#include <sstream>


TEST(Vic2World_Military_UnitTests, NameDefaultsToEmpty)
{
	std::stringstream input;
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_TRUE(unit->getName().empty());
}


TEST(Vic2World_Military_UnitTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_EQ("test_name", unit->getName());
}


TEST(Vic2World_Military_UnitTests, TypeDefaultsToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";

	const std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	const auto unit = Vic2::Unit::Factory().getUnit(input);
	std::cout.rdbuf(stdOutBuf);

	ASSERT_TRUE(unit->getType().empty());
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Regiment or Ship test_name has no type"));
}


TEST(Vic2World_Military_UnitTests, TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttype = test_type\n";
	input << "}";
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_EQ("test_type", unit->getType());
}


TEST(Vic2World_Military_UnitTests, StrengthDefaultsToZero)
{
	std::stringstream input;
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_EQ(0.0, unit->getStrength());
}


TEST(Vic2World_Military_UnitTests, StrengthCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tstrength = 4.200\n";
	input << "}";
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_NEAR(4.2, unit->getStrength(), 0.0001);
}


TEST(Vic2World_Military_UnitTests, OrganizationDefaultsToZero)
{
	std::stringstream input;
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_EQ(0.0, unit->getOrganization());
}


TEST(Vic2World_Military_UnitTests, OrganizationCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\torganisation = 42.00\n";
	input << "}";
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_NEAR(42.0, unit->getOrganization(), 0.0001);
}


TEST(Vic2World_Military_UnitTests, ExperienceDefaultsToZero)
{
	std::stringstream input;
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_EQ(0.0, unit->getExperience());
}


TEST(Vic2World_Military_UnitTests, ExperienceCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\texperience = 0.42\n";
	input << "}";
	const auto unit = Vic2::Unit::Factory().getUnit(input);

	ASSERT_NEAR(0.42, unit->getExperience(), 0.0001);
}