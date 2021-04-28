#include "Configuration.h"
#include "V2World/Countries/CommonCountriesDataFactory.h"
#include "V2World/Mods/ModBuilder.h"
#include "gtest/gtest.h"



TEST(Vic2World_Countries_CommonCountriesDataTests, commonCountryDataDefaultsToEmpty)
{
	const auto& [commonCountryData, unused] = Vic2::importCommonCountriesData(
		 *Configuration::Builder().setVic2Path("./missing_common_countries_data/").build());

	ASSERT_TRUE(commonCountryData.empty());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, commonCountryDataCanBeImported)
{
	const auto& [commonCountryData, unused] = Vic2::importCommonCountriesData(
		 *Configuration::Builder().setVic2Path("./vanilla_common_countries_data/").build());

	ASSERT_EQ(2, commonCountryData.size());
	ASSERT_TRUE(commonCountryData.contains("ONE"));
	ASSERT_EQ(2, commonCountryData.at("ONE").getParties().size());
	ASSERT_EQ("ONE_conservative", commonCountryData.at("ONE").getParties()[0].getName());
	ASSERT_EQ("ONE_liberal", commonCountryData.at("ONE").getParties()[1].getName());
	ASSERT_TRUE(commonCountryData.contains("TWO"));
	ASSERT_EQ(2, commonCountryData.at("TWO").getParties().size());
	ASSERT_EQ("TWO_conservative", commonCountryData.at("TWO").getParties()[0].getName());
	ASSERT_EQ("TWO_liberal", commonCountryData.at("TWO").getParties()[1].getName());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, commonCountryDataCanBeImportedFromMods)
{
	const auto& [commonCountryData, unused] = Vic2::importCommonCountriesData(
		 *Configuration::Builder()
				.setVic2Path("./vanilla_common_countries_data/")
				.setVic2ModPath("./")
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("common_countries_mod").build())
				.build());

	ASSERT_EQ(1, commonCountryData.size());
	ASSERT_TRUE(commonCountryData.contains("MOD"));
	ASSERT_EQ(2, commonCountryData.at("MOD").getParties().size());
	ASSERT_EQ("MOD_conservative", commonCountryData.at("MOD").getParties()[0].getName());
	ASSERT_EQ("MOD_liberal", commonCountryData.at("MOD").getParties()[1].getName());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, commonCountryDataDefaultsToVanillaForMissingMods)
{
	const auto& [commonCountryData, unused] =
		 Vic2::importCommonCountriesData(*Configuration::Builder()
														  .setVic2Path("./vanilla_common_countries_data/")
														  .setVic2ModPath("./")
														  .addVic2Mod(*Vic2::Mod::Builder().setDirectory("missing_mod").build())
														  .build());

	ASSERT_EQ(2, commonCountryData.size());
	ASSERT_TRUE(commonCountryData.contains("ONE"));
	ASSERT_EQ(2, commonCountryData.at("ONE").getParties().size());
	ASSERT_EQ("ONE_conservative", commonCountryData.at("ONE").getParties()[0].getName());
	ASSERT_EQ("ONE_liberal", commonCountryData.at("ONE").getParties()[1].getName());
	ASSERT_TRUE(commonCountryData.contains("TWO"));
	ASSERT_EQ(2, commonCountryData.at("TWO").getParties().size());
	ASSERT_EQ("TWO_conservative", commonCountryData.at("TWO").getParties()[0].getName());
	ASSERT_EQ("TWO_liberal", commonCountryData.at("TWO").getParties()[1].getName());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, partiesDefaultToEmpty)
{
	const auto& [unused, parties] = Vic2::importCommonCountriesData(
		 *Configuration::Builder().setVic2Path("./missing_common_countries_data/").build());

	ASSERT_TRUE(parties.empty());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, partiesCanBeImported)
{
	const auto& [unused, parties] = Vic2::importCommonCountriesData(
		 *Configuration::Builder().setVic2Path("./vanilla_common_countries_data/").build());

	ASSERT_EQ(4, parties.size());
	ASSERT_EQ("ONE_conservative", parties[0].getName());
	ASSERT_EQ("ONE_liberal", parties[1].getName());
	ASSERT_EQ("TWO_conservative", parties[2].getName());
	ASSERT_EQ("TWO_liberal", parties[3].getName());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, partiesCanBeImportedFromMods)
{
	const auto& [unused, parties] = Vic2::importCommonCountriesData(
		 *Configuration::Builder()
				.setVic2Path("./vanilla_common_countries_data/")
				.setVic2ModPath("./")
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("common_countries_mod").build())
				.build());

	ASSERT_EQ(2, parties.size());
	ASSERT_EQ("MOD_conservative", parties[0].getName());
	ASSERT_EQ("MOD_liberal", parties[1].getName());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, partiesDefaultToVanillaForMissingMods)
{
	const auto& [unused, parties] =
		 Vic2::importCommonCountriesData(*Configuration::Builder()
														  .setVic2Path("./vanilla_common_countries_data/")
														  .setVic2ModPath("./")
														  .addVic2Mod(*Vic2::Mod::Builder().setDirectory("missing_mod").build())
														  .build());

	ASSERT_EQ(4, parties.size());
	ASSERT_EQ("ONE_conservative", parties[0].getName());
	ASSERT_EQ("ONE_liberal", parties[1].getName());
	ASSERT_EQ("TWO_conservative", parties[2].getName());
	ASSERT_EQ("TWO_liberal", parties[3].getName());
}