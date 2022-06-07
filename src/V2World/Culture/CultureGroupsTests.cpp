#include "src/V2World/Culture/CultureGroups.h"
#include "src/V2World/Culture/CultureGroupsFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(Vic2World_CultureGroupsTests, UnmatchedCultureReturnsNullopt)
{
	const auto cultureGroups = Vic2::CultureGroups::Factory().getCultureGroups(*Configuration::Builder().build());

	ASSERT_EQ(std::nullopt, cultureGroups->getGroup("unmatched_culture"));
}


TEST(Vic2World_CultureGroupsTests, BaseGameCulturesCanBeMatched)
{
	const auto cultureGroups =
		 Vic2::CultureGroups::Factory().getCultureGroups(*Configuration::Builder().setVic2Path("./BaseCultures").build());

	ASSERT_EQ("base_game_group", cultureGroups->getGroup("matched_culture"));
}


TEST(Vic2World_CultureGroupsTests, ModCulturesCanBeMatched)
{
	const auto cultureGroups = Vic2::CultureGroups::Factory().getCultureGroups(
		 *Configuration::Builder().addVic2Mod(Mod("ModOne", "ModCultures/ModOne/")).build());

	ASSERT_EQ("mod_one_group", cultureGroups->getGroup("matched_mod_one_culture"));
}


TEST(Vic2World_CultureGroupsTests, OnlyFinalModCulturesCanBeMatched)
{
	const auto cultureGroups =
		 Vic2::CultureGroups::Factory().getCultureGroups(*Configuration::Builder()
																				.setVic2Path("./BaseCultures")
																				.addVic2Mod(Mod("ModOne", "ModCultures/ModOne/"))
																				.addVic2Mod(Mod("ModTwo", "ModCultures/ModTwo/"))
																				.build());

	ASSERT_NE("base_game_group", cultureGroups->getGroup("matched_culture"));
	ASSERT_NE("mod_one_group", cultureGroups->getGroup("matched_mod_one_culture"));
	ASSERT_EQ("mod_two_group", cultureGroups->getGroup("matched_mod_two_culture"));
}