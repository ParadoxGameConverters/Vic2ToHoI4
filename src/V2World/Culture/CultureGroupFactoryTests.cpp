#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Culture/CultureGroupFactory.h"
#include <sstream>



TEST(Vic2World_CultureGroupFactoryTests, GroupDefaultsToEmpy)
{
	std::stringstream input;

	const auto culture_group = Vic2::CultureGroupFactory().GetCultureGroup(input);
	EXPECT_TRUE(culture_group.cultures.empty());
	EXPECT_FALSE(culture_group.union_tag.has_value());
}


TEST(Vic2World_CultureGroupFactoryTests, ItemsAreImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tculture_one = {}\n";
	input << "\tculture_two = {}\n";
	input << "\tunion = TAG\n";
	input << "}";

	const auto culture_group = Vic2::CultureGroupFactory().GetCultureGroup(input);
	EXPECT_THAT(culture_group.cultures, testing::ElementsAre("culture_one", "culture_two"));
	ASSERT_TRUE(culture_group.union_tag.has_value());
	EXPECT_EQ(culture_group.union_tag.value(), "TAG");
}