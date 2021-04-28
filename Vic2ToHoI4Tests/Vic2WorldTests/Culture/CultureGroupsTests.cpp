#include "V2World/Culture/CultureGroups.h"
#include "V2World/Culture/CultureGroupsFactory.h"
#include "V2World/Mods/ModBuilder.h"
#include "gtest/gtest.h"
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
		 *Configuration::Builder()
				.setVic2ModPath("./ModCultures")
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("ModOne").build())
				.build());

	ASSERT_EQ("mod_one_group", cultureGroups->getGroup("matched_mod_one_culture"));
}


TEST(Vic2World_CultureGroupsTests, OnlyFinalModCulturesCanBeMatched)
{
	const auto cultureGroups = Vic2::CultureGroups::Factory().getCultureGroups(
		 *Configuration::Builder()
				.setVic2Path("./BaseCultures")
				.setVic2ModPath("./ModCultures")
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("ModOne").build())
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("ModTwo").build())
				.build());

	ASSERT_NE("base_game_group", cultureGroups->getGroup("matched_culture"));
	ASSERT_NE("mod_one_group", cultureGroups->getGroup("matched_mod_one_culture"));
	ASSERT_EQ("mod_two_group", cultureGroups->getGroup("matched_mod_two_culture"));
}