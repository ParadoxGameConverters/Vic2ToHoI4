#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Military/Army.h"
#include "src/V2World/Military/ArmyFactory.h"
#include <gmock/gmock-matchers.h>
#include <sstream>


TEST(Vic2World_Military_ArmyTests, NameDefaultsToEmpty)
{
	std::stringstream input;
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_TRUE(army->getName().empty());
}


TEST(Vic2World_Military_ArmyTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_EQ("test_name", army->getName());
}


TEST(Vic2World_Military_ArmyTests, OwnerIsAsSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";
	const auto army = Vic2::Army::Factory().getArmy("TAG", input);

	ASSERT_EQ("TAG", army->getOwner());
}


TEST(Vic2World_Military_ArmyTests, LocationDefaultsToNullopt)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";

	const std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	const auto army = Vic2::Army::Factory().getArmy("", input);
	std::cout.rdbuf(stdOutBuf);

	ASSERT_FALSE(army->getLocation());
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Army or Navy test_name has no location"));
}


TEST(Vic2World_Military_ArmyTests, LocationCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlocation = 42\n";
	input << "}";
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_EQ(42, army->getLocation());
}


TEST(Vic2World_Military_ArmyTests, LocationCanBeChanged)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlocation = 42\n";
	input << "}";
	auto army = Vic2::Army::Factory().getArmy("", input);
	army->setLocation(144);

	ASSERT_EQ(144, army->getLocation());
}


TEST(Vic2World_Military_ArmyTests, UnitsDefaultsToEmpty)
{
	std::stringstream input;
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_TRUE(army->getUnits().empty());
}


TEST(Vic2World_Military_ArmyTests, UnitsCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tregiment = {\n";
	input << "\t\tname = test_regiment\n";
	input << "\t}\n";
	input << "\tship = {\n";
	input << "\t\tname = test_ship\n";
	input << "\t}\n";
	input << "}";
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_EQ(2, army->getUnits().size());
	ASSERT_EQ("test_regiment", army->getUnits()[0].getName());
	ASSERT_EQ("test_ship", army->getUnits()[1].getName());
}


TEST(Vic2World_Military_ArmyTests, TransportedArmiesDefaultsToEmpty)
{
	std::stringstream input;
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_TRUE(army->getTransportedArmies().empty());
}


TEST(Vic2World_Military_ArmyTests, TransportedArmiesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tarmy = {\n";
	input << "\t\tregiment = {\n";
	input << "\t\t\tname = test_regiment\n";
	input << "\t\t}\n";
	input << "\t}\n";
	input << "}";
	const auto army = Vic2::Army::Factory().getArmy("", input);

	ASSERT_EQ(1, army->getTransportedArmies().size());
	ASSERT_EQ(1, army->getTransportedArmies()[0].getUnits().size());
	ASSERT_EQ("test_regiment", army->getTransportedArmies()[0].getUnits()[0].getName());
}