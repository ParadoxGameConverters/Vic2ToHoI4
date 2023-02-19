#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Mappers/Provinces/ProvinceMapperBuilder.h"
#include "src/V2World/Military/ArmyBuilder.h"
#include "src/V2World/World/World.h"
#include "src/V2World/World/WorldFactory.h"



TEST(Vic2World_World_WorldTests, ProvincesDefaultToEmpty)
{
	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getProvinces().empty());
}


TEST(Vic2World_World_WorldTests, ProvincesCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_EQ(6, world->getProvinces().size());
	EXPECT_TRUE(world->getProvinces().contains(1));
	EXPECT_TRUE(world->getProvinces().contains(2));
	EXPECT_TRUE(world->getProvinces().contains(3));
	EXPECT_TRUE(world->getProvinces().contains(4));
	EXPECT_TRUE(world->getProvinces().contains(5));
	EXPECT_TRUE(world->getProvinces().contains(6));
	EXPECT_THAT(world->getMapData().GetNeighbors(3), testing::UnorderedElementsAre(1, 2, 4, 5));
}


TEST(Vic2World_World_WorldTests, GetProvinceReturnsNulloptForMissingProvince)
{
	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_EQ(std::nullopt, world->getProvince(1));
}


TEST(Vic2World_World_WorldTests, GetProvinceReturnsProvince)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_EQ(1, (*world->getProvince(1))->getNumber());
}


TEST(Vic2World_World_WorldTests, CountriesDefaultToEmpty)
{
	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getCountries().empty());
}


TEST(Vic2World_World_WorldTests, CountriesCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_EQ(4, world->getCountries().size());
	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_TRUE(world->getCountries().contains("NON"));
	EXPECT_TRUE(world->getCountries().contains("NOT"));
}


TEST(Vic2World_World_WorldTests, InvalidCountriesAreLogged)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const commonItems::ModFilesystem mod_filesystem_two("", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem_two, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Invalid tag ONE"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Invalid tag TWO"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Invalid tag NON"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Invalid tag NOT"));
}


TEST(Vic2World_World_WorldTests, EmptyCountriesCanBeRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_EQ(4, world->getCountries().size());
	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_TRUE(world->getCountries().contains("NON"));
	EXPECT_TRUE(world->getCountries().contains("NOT"));
	EXPECT_FALSE(world->getCountries().contains("DED"));
}


TEST(Vic2World_World_WorldTests, DiplomacyIsLoggedIfMissing)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr(" [WARNING] Vic2 save had no diplomacy section!\n"));
}


TEST(Vic2World_World_WorldTests, DiplomacyCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_EQ(1, world->getDiplomacy().getAgreements().size());
	EXPECT_EQ("test_agreement", world->getDiplomacy().getAgreements()[0].getType());
}


TEST(Vic2World_World_WorldTests, GreatPowersDefaultToEmpty)
{
	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getGreatPowers().empty());
}


TEST(Vic2World_World_WorldTests, GreatPowersCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_EQ(1, world->getGreatPowers().size());
	EXPECT_EQ("ONE", world->getGreatPowers()[0]);
}


TEST(Vic2World_World_WorldTests, GreatPowersLoggedIfInvalid)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr(" [WARNING] Great power did not match an existing country!\n"));
}


TEST(Vic2World_World_WorldTests, StateDefinitionsDefaultToEmpty)
{
	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getStateDefinitions().getAllProvinces(1).empty());
	EXPECT_TRUE(world->getStateDefinitions().getAllProvinces(2).empty());
}


TEST(Vic2World_World_WorldTests, ProvincesAreAssignedToStates)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_EQ(1, world->getCountries().at("ONE").getStates().size());
	EXPECT_EQ(1, world->getCountries().at("ONE").getStates()[0].getProvinces().size());
	EXPECT_EQ(1, (*world->getCountries().at("ONE").getStates()[0].getProvinces().begin())->getNumber());
	EXPECT_EQ("test_culture", world->getCountries().at("ONE").getPrimaryCulture());
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_EQ(1, world->getCountries().at("TWO").getStates().size());
	EXPECT_EQ(1, world->getCountries().at("TWO").getStates()[0].getProvinces().size());
	EXPECT_EQ(2, (*world->getCountries().at("TWO").getStates()[0].getProvinces().begin())->getNumber());

	EXPECT_THAT(log.str(),
		 testing::HasSubstr(" [WARNING] Trying to assign province 3 to HUH, but country does not exist.\n"));
}


TEST(Vic2World_World_WorldTests, MissingCulturesAreHandled)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_EQ("test_culture", world->getCountries().at("ONE").getPrimaryCulture());
}


TEST(Vic2World_World_WorldTests, StateDefinitionsCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_EQ(1, world->getStateDefinitions().getAllProvinces(1).size());
	EXPECT_EQ(1, world->getStateDefinitions().getAllProvinces(2).size());
}


TEST(Vic2World_World_WorldTests, LocalisationsDefaultToEmpty)
{
	const commonItems::ModFilesystem mod_filesystem("BlankWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("BlankWorld").setInputFile("V2World/BlankWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getLocalisations().getTextInEachLanguage("test_key").empty());
}


TEST(Vic2World_World_WorldTests, LocalisationsDefinitionsCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_THAT(world->getLocalisations().getTextInEachLanguage("test_key"),
		 testing::UnorderedElementsAre(std::make_pair(std::string("english"), std::string("test_english_text")),
			  std::make_pair(std::string("french"), std::string("test_french_text")),
			  std::make_pair(std::string("german"), std::string("test_german_text")),
			  std::make_pair(std::string("polish"), std::string("test_polish_text")),
			  std::make_pair(std::string("spanish"), std::string("test_spanish_text")),
			  std::make_pair(std::string("italian"), std::string("test_italian_text")),
			  std::make_pair(std::string("swedish"), std::string("test_swedish_text")),
			  std::make_pair(std::string("czech"), std::string("test_czech_text")),
			  std::make_pair(std::string("hungarian"), std::string("test_hungarian_text")),
			  std::make_pair(std::string("dutch"), std::string("test_dutch_text")),
			  std::make_pair(std::string("braz_por"), std::string("test_braz_por_text")),
			  std::make_pair(std::string("russian"), std::string("test_russian_text")),
			  std::make_pair(std::string("finnish"), std::string("test_finnish_text"))));
}


TEST(Vic2World_World_WorldTests, WarsCanBeAdded)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_EQ(1, world->getCountries().at("ONE").getWars().size());
	EXPECT_EQ("ONE", world->getCountries().at("ONE").getWars()[0].getOriginalAttacker());
	EXPECT_TRUE(world->getCountries().at("ONE").isAtWar());
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_TRUE(world->getCountries().at("TWO").isAtWar());
	EXPECT_TRUE(world->getCountries().contains("NON"));
	EXPECT_TRUE(world->getCountries().at("NON").isAtWar());
	EXPECT_TRUE(world->getCountries().contains("NOT"));
	EXPECT_TRUE(world->getCountries().at("NOT").isAtWar());
}


TEST(Vic2World_World_WorldTests, CoresAreAssignedToCountries)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_EQ(1, world->getCountries().at("ONE").getCores().size());
	EXPECT_EQ(1, world->getCountries().at("ONE").getCores()[0]->getNumber());
	EXPECT_TRUE(world->getCountries().contains("NOT"));
	EXPECT_EQ(2, world->getCountries().at("NOT").getCores().size());
	EXPECT_EQ(1, world->getCountries().at("NOT").getCores()[0]->getNumber());
	EXPECT_EQ(2, world->getCountries().at("NOT").getCores()[1]->getNumber());
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_EQ(1, world->getCountries().at("TWO").getCores().size());
	EXPECT_EQ(2, world->getCountries().at("TWO").getCores()[0]->getNumber());
	EXPECT_TRUE(world->getCountries().contains("NON"));
	EXPECT_EQ(4, world->getCountries().at("NON").getCores().size());
	EXPECT_EQ(2, world->getCountries().at("NON").getCores()[0]->getNumber());
	EXPECT_EQ(4, world->getCountries().at("NON").getCores()[1]->getNumber());
	EXPECT_EQ(5, world->getCountries().at("NON").getCores()[2]->getNumber());
	EXPECT_EQ(6, world->getCountries().at("NON").getCores()[3]->getNumber());
}


TEST(Vic2World_World_WorldTests, SimpleLandlessNationsAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_accepted_culture_by_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_EQ(1, world->getCountries().at("ONE").getCores().size());
	EXPECT_EQ(1, world->getCountries().at("ONE").getCores()[0]->getNumber());
	EXPECT_FALSE(world->getCountries().contains("NOT"));
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_EQ(1, world->getCountries().at("TWO").getCores().size());
	EXPECT_EQ(2, world->getCountries().at("TWO").getCores()[0]->getNumber());
	EXPECT_TRUE(world->getCountries().contains("NON"));
	EXPECT_EQ(1, world->getCountries().at("NON").getCores().size());
	EXPECT_EQ(6, world->getCountries().at("NON").getCores()[0]->getNumber());
	EXPECT_FALSE(world->getCountries().contains("DED"));
}


TEST(Vic2World_World_WorldTests, CoresAreKeptIfRemovesetToNone)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(1);
	EXPECT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NOT"));

	const auto province2 = world->getProvince(2);
	EXPECT_TRUE(province2.has_value());
	EXPECT_TRUE((*province2)->getCores().contains("NON"));
	EXPECT_TRUE((*province2)->getCores().contains("NOT"));

	const auto province4 = world->getProvince(4);
	EXPECT_TRUE(province4.has_value());
	EXPECT_TRUE((*province4)->getCores().contains("NON"));

	const auto province5 = world->getProvince(5);
	EXPECT_TRUE(province5.has_value());
	EXPECT_TRUE((*province5)->getCores().contains("NON"));

	const auto province6 = world->getProvince(6);
	EXPECT_TRUE(province6.has_value());
	EXPECT_TRUE((*province6)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithoutOwnerAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province4 = world->getProvince(4);
	EXPECT_TRUE(province4.has_value());
	EXPECT_FALSE((*province4)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithInvalidOwnerAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(5);
	EXPECT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithTooLowPopulationAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(1);
	EXPECT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NOT"));
}


TEST(Vic2World_World_WorldTests, CoresWithSameCultureAsOwnerAreNotRemovedIfOptionTooLow)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(2);
	EXPECT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NON"));
	EXPECT_TRUE((*province)->getCores().contains("NOT"));

	const auto province6 = world->getProvince(6);
	EXPECT_TRUE(province6.has_value());
	EXPECT_TRUE((*province6)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithSameCultureAsOwnerAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_same_culture_as_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(2);
	EXPECT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithAcceptedCultureAsOwnerAreNotRemovedIfSettingTooLow)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_same_culture_as_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(2);
	EXPECT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NOT"));

	const auto province6 = world->getProvince(6);
	EXPECT_TRUE(province6.has_value());
	EXPECT_TRUE((*province6)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithAcceptedCultureAsOwnerAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_accepted_culture_by_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(2);
	EXPECT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NOT"));
}


TEST(Vic2World_World_WorldTests, CoresFromDeadNationAreNotRemovedIfSettingTooLow)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_accepted_culture_by_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(6);
	EXPECT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresFromDeadNationAreRemoved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::extreme_removal)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	const auto province = world->getProvince(6);
	EXPECT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NON"));
}

TEST(Vic2World_World_WorldTests, EmployedWorkersAreAssigned)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_EQ(5, world->getCountries().at("ONE").getEmployedWorkers());
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_EQ(0, world->getCountries().at("TWO").getEmployedWorkers());
}


TEST(Vic2World_World_WorldTests, MergingNationsWorks)
{
	const commonItems::ModFilesystem mod_filesystem("MergeWorld", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(
					*Configuration::Builder().setVic2Path("MergeWorld").setInputFile("MergeWorld/MergeWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	EXPECT_EQ(1, world->getCountries().size());
	EXPECT_TRUE(world->getCountries().contains("FOO"));
	EXPECT_FALSE(world->getCountries().contains("BAR"));
}


TEST(Vic2World_World_WorldTests, ProvinceMappingsAreChecked)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] No mapping for Vic2 province 1"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] No mapping for Vic2 province 2"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] No mapping for Vic2 province 3"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] No mapping for Vic2 province 4"));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] No mapping for Vic2 province 5"));
}


TEST(Vic2World_World_WorldTests, UnmappedModProvinceThrowsError)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});

	ASSERT_THROW(Vic2::World::Factory(mod_filesystem, 0.0F)
						  .importWorld(*Configuration::Builder()
												  .setVic2Path("V2World")
												  .setInputFile("V2World/TestWorld.v2")
												  .addVic2Mod(Mod("no_mappings_mod", "no_mappings_mod"))
												  .build(),
								*Mappers::ProvinceMapper::Builder().Build(),
								mod_filesystem),
		 std::runtime_error);
}


TEST(Vic2World_World_WorldTests, ConquerStrategiesAreConsolidated)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world =
		 Vic2::World::Factory(mod_filesystem, 0.0F)
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build(),
					mod_filesystem);

	ASSERT_TRUE(world->getCountries().contains("ONE"));

	const Vic2::StrategyData data{.value = 182, .provinces = std::vector<int>{2}};
	EXPECT_THAT(world->getCountries().at("ONE").getAI().getConsolidatedStrategies(),
		 testing::UnorderedElementsAre(std::make_pair(std::string("TWO"), data)));
}


TEST(Vic2World_World_WorldTests, ArmiesAreMovedHome)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("MoveArmiesWorld")
														  .setInputFile("MoveArmiesWorld/MoveArmiesWorld.v2")
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_THAT(world->getCountries().at("ONE").getArmies(),
		 testing::ElementsAre(
			  *Vic2::Army::Builder().setOwner("ONE").setName("No location army").setLocation(std::nullopt).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Non-existent location army").setLocation(5).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("No-owner province army").setLocation(4).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("In owned territory army").setLocation(2).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("In at-war province army").setLocation(1).Build(),
			  *Vic2::Army::Builder()
					 .setOwner("ONE")
					 .setName("In non-at-war province army")
					 .setLocation(std::nullopt)
					 .Build()));
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_TRUE(world->getCountries().contains("NON"));
	EXPECT_THAT(world->getCountries().at("NON").getArmies(),
		 testing::ElementsAre(*Vic2::Army::Builder()
											.setOwner("NON")
											.setName("Not at war country army")
											.setLocation(std::nullopt)
											.Build()));
}


TEST(Vic2World_World_WorldTests, BattlesAreResolved)
{
	const commonItems::ModFilesystem mod_filesystem("V2World", {});
	const auto world = Vic2::World::Factory(mod_filesystem, 0.0F)
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("ResolveBattlesWorld")
														  .setInputFile("ResolveBattlesWorld/ResolveBattlesWorld.v2")
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build(),
										mod_filesystem);

	EXPECT_TRUE(world->getCountries().contains("ONE"));
	EXPECT_THAT(world->getCountries().at("ONE").getArmies(),
		 testing::ElementsAre(
			  *Vic2::Army::Builder().setOwner("ONE").setName("No location army").setLocation(std::nullopt).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Only by itself army").setLocation(4).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("First in same-country province").setLocation(2).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Second in same-country province").setLocation(2).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("First in different-country province").setLocation(3).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Non-existent province army").setLocation(5).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Second non-existent province army").setLocation(5).Build()));
	EXPECT_TRUE(world->getCountries().contains("TWO"));
	EXPECT_THAT(world->getCountries().at("TWO").getArmies(),
		 testing::ElementsAre(*Vic2::Army::Builder()
											.setOwner("TWO")
											.setName("Second in different-country province")
											.setLocation(std::nullopt)
											.Build()));
}