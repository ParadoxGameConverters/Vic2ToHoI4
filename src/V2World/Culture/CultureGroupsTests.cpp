#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Culture/CultureGroups.h"
#include "src/V2World/Culture/CultureGroupsFactory.h"
#include "gmock/gmock-matchers.h"
#include <sstream>



TEST(Vic2World_CultureGroupsTests, UnmatchedCultureReturnsNullopt)
{
	const Vic2::CultureGroups culture_groups;

	EXPECT_EQ(std::nullopt, culture_groups.GetGroup("unmatched_culture"));
}


TEST(Vic2World_CultureGroupsTests, BaseGameCulturesCanBeMatched)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseCultures"), {});
	const auto culture_groups = Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem);

	EXPECT_EQ("base_game_group", culture_groups->GetGroup("matched_culture"));
}


TEST(Vic2World_CultureGroupsTests, UnionCountriesCanBeIdentified)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseCultures"), {});
	const auto culture_groups = Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem);

	EXPECT_TRUE(culture_groups->IsUnionCountry("TAG"));
}


TEST(Vic2World_CultureGroupsTests, NonUnionCountriesCanBeIdentified)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseCultures"), {});
	const auto culture_groups = Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem);

	EXPECT_FALSE(culture_groups->IsUnionCountry("NON"));
}


TEST(Vic2World_CultureGroupsTests, UnionCulturesAreImported)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseCultures"), {});
	const auto culture_groups = Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem);

	EXPECT_THAT(culture_groups->GetUnionCultures("NON"), testing::UnorderedElementsAre());
	EXPECT_THAT(culture_groups->GetUnionCultures("TAG"), testing::UnorderedElementsAre("matched_culture"));
}