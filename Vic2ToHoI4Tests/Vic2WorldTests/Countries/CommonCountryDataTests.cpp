#include "Configuration.h"
#include "V2World/Countries/CommonCountryData.h"
#include "V2World/Countries/CommonCountryDataFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Vic2World_Countries_CommonCountryDataTests, ColorDefaultsToNullopt)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("blankCommonCountryData.txt",
			  {},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_EQ(std::nullopt, commonCountryData->getColor());
}


TEST(Vic2World_Countries_CommonCountryDataTests, ColorCanBeSet)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryTestData.txt",
			  {},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_TRUE(commonCountryData->getColor().has_value());
	const auto expectedColor = std::array{56, 32, 172};
	ASSERT_EQ(expectedColor, commonCountryData->getColor()->getRgbComponents());
}


TEST(Vic2World_Countries_CommonCountryDataTests, ColorCanBeSetFromMod)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryModTestData.txt",
			  {Mod("mod", "mod/")},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_TRUE(commonCountryData->getColor().has_value());
	const auto expectedColor = std::array{10, 20, 30};
	ASSERT_EQ(expectedColor, commonCountryData->getColor()->getRgbComponents());
}


TEST(Vic2World_Countries_CommonCountryDataTests, MissingModUsesVanillaColor)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryTestData.txt",
			  {Mod("missing mod", "missing_mod/")},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_TRUE(commonCountryData->getColor().has_value());
	const auto expectedColor = std::array{56, 32, 172};
	ASSERT_EQ(expectedColor, commonCountryData->getColor()->getRgbComponents());
}


TEST(Vic2World_Countries_CommonCountryDataTests, UnitNamesDefaultToEmpty)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("blankCommonCountryData.txt",
			  {},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_TRUE(commonCountryData->getUnitNames().empty());
}


TEST(Vic2World_Countries_CommonCountryDataTests, UnitNamesCanBeSet)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryTestData.txt",
			  {},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_THAT(commonCountryData->getUnitNames(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"Azerbaijan", "Nader Shah"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
}


TEST(Vic2World_Countries_CommonCountryDataTests, UnitNamesCanBeSetFromMod)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryModTestData.txt",
			  {Mod("mod", "mod/")},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_THAT(commonCountryData->getUnitNames(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"ModDreadOne", "ModDreadTwo"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"ModIronOne", "ModIronTwo"})));
}


TEST(Vic2World_Countries_CommonCountryDataTests, MissingModUsesVanillaUnitNames)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryTestData.txt",
			  {Mod("missing mod", "missing_mod/")},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_THAT(commonCountryData->getUnitNames(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"Azerbaijan", "Nader Shah"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
}


TEST(Vic2World_Countries_CommonCountryDataTests, PartiesDefaultToEmpty)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("blankCommonCountryData.txt",
			  {},
			  *Configuration::Builder().setVic2Path("./").build());

	ASSERT_TRUE(commonCountryData->getParties().empty());
}


TEST(Vic2World_Countries_CommonCountryDataTests, PartiesCanBeSet)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryTestData.txt",
			  {},
			  *Configuration::Builder().setVic2Path("./").build());

	const auto parties = commonCountryData->getParties();
	ASSERT_EQ(2, parties.size());
	ASSERT_EQ("AZB_reactionary", parties[0].getName());
	ASSERT_EQ("AZB_liberal", parties[1].getName());
}


TEST(Vic2World_Countries_CommonCountryDataTests, PartiesCanBeSetFromMod)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryModTestData.txt",
			  {Mod("mod", "mod/")},
			  *Configuration::Builder().setVic2Path("./").build());

	const auto parties = commonCountryData->getParties();
	ASSERT_EQ(2, parties.size());
	ASSERT_EQ("MOD_reactionary", parties[0].getName());
	ASSERT_EQ("MOD_liberal", parties[1].getName());
}


TEST(Vic2World_Countries_CommonCountryDataTests, MissingModUsesVanillaParties)
{
	const auto commonCountryData =
		 Vic2::CommonCountryData::Factory().importCommonCountryData("CommonCountryTestData.txt",
			  {Mod("missing mod", "missing_mod/")},
			  *Configuration::Builder().setVic2Path("./").build());

	const auto parties = commonCountryData->getParties();
	ASSERT_EQ(2, parties.size());
	ASSERT_EQ("AZB_reactionary", parties[0].getName());
	ASSERT_EQ("AZB_liberal", parties[1].getName());
}