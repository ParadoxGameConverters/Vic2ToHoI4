#include "src/V2World/Culture/CultureGroupFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(Vic2World_CultureGroupFactoryTests, GroupDefaultsToEmpy)
{
	std::stringstream input;

	const auto cultureGroup = Vic2::CultureGroupFactory().getCultureGroup(input);
	ASSERT_TRUE(cultureGroup.empty());
}


TEST(Vic2World_CultureGroupFactoryTests, NonCultureItemsAreIgnored)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tunion = {}\n";
	input << "\tleader = {}\n";
	input << "\tunit = {}\n";
	input << "\tis_overseas = {}\n";
	input << "}";

	const auto cultureGroup = Vic2::CultureGroupFactory().getCultureGroup(input);
	ASSERT_TRUE(cultureGroup.empty());
}


TEST(Vic2World_CultureGroupFactoryTests, CulturesAreImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tculture_one = {}\n";
	input << "\tculture_two = {}\n";
	input << "}";

	const auto cultureGroup = Vic2::CultureGroupFactory().getCultureGroup(input);
	ASSERT_EQ(2, cultureGroup.size());
	ASSERT_EQ("culture_one", cultureGroup[0]);
	ASSERT_EQ("culture_two", cultureGroup[1]);
}