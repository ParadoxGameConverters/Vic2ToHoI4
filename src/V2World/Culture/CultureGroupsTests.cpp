#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Culture/CultureGroups.h"
#include "src/V2World/Culture/CultureGroupsFactory.h"
#include <sstream>



TEST(Vic2World_CultureGroupsTests, UnmatchedCultureReturnsNullopt)
{
	const commonItems::ModFilesystem mod_filesystem("", {});
	const auto culture_groups = Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem);

	EXPECT_EQ(std::nullopt, culture_groups->getGroup("unmatched_culture"));
}


TEST(Vic2World_CultureGroupsTests, BaseGameCulturesCanBeMatched)
{
	const commonItems::ModFilesystem mod_filesystem("./BaseCultures", {});
	const auto culture_groups = Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem);

	EXPECT_EQ("base_game_group", culture_groups->getGroup("matched_culture"));
}