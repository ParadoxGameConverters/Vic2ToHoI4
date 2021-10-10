#include "Configuration.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Provinces/ProvinceMapperBuilder.h"
#include "V2World/Military/ArmyBuilder.h"
#include "V2World/World/World.h"
#include "V2World/World/WorldFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Vic2World_World_WorldTests, ProvincesDefaultToEmpty)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getProvinces().empty());
}


TEST(Vic2World_World_WorldTests, ProvincesCanBeAdded)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/TestWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(6, world->getProvinces().size());
	ASSERT_TRUE(world->getProvinces().contains(1));
	ASSERT_TRUE(world->getProvinces().contains(2));
	ASSERT_TRUE(world->getProvinces().contains(3));
	ASSERT_TRUE(world->getProvinces().contains(4));
	ASSERT_TRUE(world->getProvinces().contains(5));
	ASSERT_TRUE(world->getProvinces().contains(6));
}


TEST(Vic2World_World_WorldTests, GetProvinceReturnsNulloptForMissingProvince)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(std::nullopt, world->getProvince(1));
}


TEST(Vic2World_World_WorldTests, GetProvinceReturnsProvince)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/TestWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(1, (*world->getProvince(1))->getNumber());
}


TEST(Vic2World_World_WorldTests, CountriesDefaultToEmpty)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().empty());
}


TEST(Vic2World_World_WorldTests, CountriesCanBeAdded)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(4, world->getCountries().size());
	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_TRUE(world->getCountries().contains("NON"));
	ASSERT_TRUE(world->getCountries().contains("NOT"));
}


TEST(Vic2World_World_WorldTests, InvalidCountriesAreLogged)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	std::cout.rdbuf(stdOutBuf);

	ASSERT_THAT(log.str(),
		 testing::HasSubstr(" [WARNING] Invalid tag ONE\n"
								  " [WARNING] Invalid tag TWO\n"
								  " [WARNING] Invalid tag NON\n"
								  " [WARNING] Invalid tag NOT\n"));
}


TEST(Vic2World_World_WorldTests, EmptyCountriesCanBeRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(4, world->getCountries().size());
	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_TRUE(world->getCountries().contains("NON"));
	ASSERT_TRUE(world->getCountries().contains("NOT"));
	ASSERT_FALSE(world->getCountries().contains("DED"));
}


TEST(Vic2World_World_WorldTests, DiplomacyIsLoggedIfMissing)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	std::cout.rdbuf(stdOutBuf);

	ASSERT_THAT(log.str(), testing::HasSubstr(" [WARNING] Vic2 save had no diplomacy section!\n"));
}


TEST(Vic2World_World_WorldTests, DiplomacyCanBeAdded)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/TestWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(1, world->getDiplomacy().getAgreements().size());
	ASSERT_EQ("test_agreement", world->getDiplomacy().getAgreements()[0].getType());
}


TEST(Vic2World_World_WorldTests, GreatPowersDefaultToEmpty)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getGreatPowers().empty());
}


TEST(Vic2World_World_WorldTests, GreatPowersCanBeAdded)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(1, world->getGreatPowers().size());
	ASSERT_EQ("ONE", world->getGreatPowers()[0]);
}


TEST(Vic2World_World_WorldTests, GreatPowersLoggedIfInvalid)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	std::cout.rdbuf(stdOutBuf);

	ASSERT_THAT(log.str(), testing::HasSubstr(" [WARNING] Great power did not match an existing country!\n"));
}


TEST(Vic2World_World_WorldTests, StateDefinitionsDefaultToEmpty)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getStateDefinitions().getAllProvinces(1).empty());
	ASSERT_TRUE(world->getStateDefinitions().getAllProvinces(2).empty());
}


TEST(Vic2World_World_WorldTests, ProvincesAreAssignedToStates)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	std::cout.rdbuf(stdOutBuf);

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_EQ(1, world->getCountries().at("ONE").getStates().size());
	ASSERT_EQ(1, world->getCountries().at("ONE").getStates()[0].getProvinces().size());
	ASSERT_EQ(1, (*world->getCountries().at("ONE").getStates()[0].getProvinces().begin())->getNumber());
	ASSERT_EQ("test_culture", world->getCountries().at("ONE").getPrimaryCulture());
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_EQ(1, world->getCountries().at("TWO").getStates().size());
	ASSERT_EQ(1, world->getCountries().at("TWO").getStates()[0].getProvinces().size());
	ASSERT_EQ(2, (*world->getCountries().at("TWO").getStates()[0].getProvinces().begin())->getNumber());

	ASSERT_THAT(log.str(),
		 testing::HasSubstr(" [WARNING] Trying to assign province 3 to HUH, but country does not exist.\n"));
}


TEST(Vic2World_World_WorldTests, MissingCulturesAreHandled)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_EQ("test_culture", world->getCountries().at("ONE").getPrimaryCulture());
}


TEST(Vic2World_World_WorldTests, StateDefinitionsCanBeAdded)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(1, world->getStateDefinitions().getAllProvinces(1).size());
	ASSERT_EQ(1, world->getStateDefinitions().getAllProvinces(2).size());
}


TEST(Vic2World_World_WorldTests, LocalisationsDefaultToEmpty)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/BlankWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getLocalisations().getTextInEachLanguage("test_key").empty());
}


TEST(Vic2World_World_WorldTests, LocalisationsDefinitionsCanBeAdded)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_THAT(world->getLocalisations().getTextInEachLanguage("test_key"),
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
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_EQ(1, world->getCountries().at("ONE").getWars().size());
	ASSERT_EQ("ONE", world->getCountries().at("ONE").getWars()[0].getOriginalAttacker());
	ASSERT_TRUE(world->getCountries().at("ONE").isAtWar());
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_TRUE(world->getCountries().at("TWO").isAtWar());
	ASSERT_TRUE(world->getCountries().contains("NON"));
	ASSERT_TRUE(world->getCountries().at("NON").isAtWar());
	ASSERT_TRUE(world->getCountries().contains("NOT"));
	ASSERT_TRUE(world->getCountries().at("NOT").isAtWar());
}


TEST(Vic2World_World_WorldTests, CoresAreAssignedToCountries)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_EQ(1, world->getCountries().at("ONE").getCores().size());
	ASSERT_EQ(1, world->getCountries().at("ONE").getCores()[0]->getNumber());
	ASSERT_TRUE(world->getCountries().contains("NOT"));
	ASSERT_EQ(2, world->getCountries().at("NOT").getCores().size());
	ASSERT_EQ(1, world->getCountries().at("NOT").getCores()[0]->getNumber());
	ASSERT_EQ(2, world->getCountries().at("NOT").getCores()[1]->getNumber());
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_EQ(1, world->getCountries().at("TWO").getCores().size());
	ASSERT_EQ(2, world->getCountries().at("TWO").getCores()[0]->getNumber());
	ASSERT_TRUE(world->getCountries().contains("NON"));
	ASSERT_EQ(4, world->getCountries().at("NON").getCores().size());
	ASSERT_EQ(2, world->getCountries().at("NON").getCores()[0]->getNumber());
	ASSERT_EQ(4, world->getCountries().at("NON").getCores()[1]->getNumber());
	ASSERT_EQ(5, world->getCountries().at("NON").getCores()[2]->getNumber());
	ASSERT_EQ(6, world->getCountries().at("NON").getCores()[3]->getNumber());
}


TEST(Vic2World_World_WorldTests, SimpleLandlessNationsAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_accepted_culture_by_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_EQ(1, world->getCountries().at("ONE").getCores().size());
	ASSERT_EQ(1, world->getCountries().at("ONE").getCores()[0]->getNumber());
	ASSERT_FALSE(world->getCountries().contains("NOT"));
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_EQ(1, world->getCountries().at("TWO").getCores().size());
	ASSERT_EQ(2, world->getCountries().at("TWO").getCores()[0]->getNumber());
	ASSERT_TRUE(world->getCountries().contains("NON"));
	ASSERT_EQ(1, world->getCountries().at("NON").getCores().size());
	ASSERT_EQ(6, world->getCountries().at("NON").getCores()[0]->getNumber());
	ASSERT_FALSE(world->getCountries().contains("DED"));
}


TEST(Vic2World_World_WorldTests, CoresAreKeptIfRemovesetToNone)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_none)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(1);
	ASSERT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NOT"));

	const auto province2 = world->getProvince(2);
	ASSERT_TRUE(province2.has_value());
	EXPECT_TRUE((*province2)->getCores().contains("NON"));
	EXPECT_TRUE((*province2)->getCores().contains("NOT"));

	const auto province4 = world->getProvince(4);
	ASSERT_TRUE(province4.has_value());
	EXPECT_TRUE((*province4)->getCores().contains("NON"));

	const auto province5 = world->getProvince(5);
	ASSERT_TRUE(province5.has_value());
	EXPECT_TRUE((*province5)->getCores().contains("NON"));

	const auto province6 = world->getProvince(6);
	ASSERT_TRUE(province6.has_value());
	EXPECT_TRUE((*province6)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithoutOwnerAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province4 = world->getProvince(4);
	ASSERT_TRUE(province4.has_value());
	EXPECT_FALSE((*province4)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithInvalidOwnerAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(5);
	ASSERT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithTooLowPopulationAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(1);
	ASSERT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NOT"));
}


TEST(Vic2World_World_WorldTests, CoresWithSameCultureAsOwnerAreNotRemovedIfOptionTooLow)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_too_little_culture)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(2);
	ASSERT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NON"));
	EXPECT_TRUE((*province)->getCores().contains("NOT"));

	const auto province6 = world->getProvince(6);
	ASSERT_TRUE(province6.has_value());
	EXPECT_TRUE((*province6)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithSameCultureAsOwnerAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_same_culture_as_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(2);
	ASSERT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithAcceptedCultureAsOwnerAreNotRemovedIfSettingTooLow)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_same_culture_as_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(2);
	ASSERT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NOT"));

	const auto province6 = world->getProvince(6);
	ASSERT_TRUE(province6.has_value());
	EXPECT_TRUE((*province6)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresWithAcceptedCultureAsOwnerAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_accepted_culture_by_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(2);
	ASSERT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NOT"));
}


TEST(Vic2World_World_WorldTests, CoresFromDeadNationAreNotRemovedIfSettingTooLow)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::remove_accepted_culture_by_owner)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(6);
	ASSERT_TRUE(province.has_value());
	EXPECT_TRUE((*province)->getCores().contains("NON"));
}


TEST(Vic2World_World_WorldTests, CoresFromDeadNationAreRemoved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("V2World")
														  .setInputFile("V2World/TestWorld.v2")
														  .setRemoveCores(removeCoresOptions::extreme_removal)
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	const auto province = world->getProvince(6);
	ASSERT_TRUE(province.has_value());
	EXPECT_FALSE((*province)->getCores().contains("NON"));
}

TEST(Vic2World_World_WorldTests, EmployedWorkersAreAssigned)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_EQ(5, world->getCountries().at("ONE").getEmployedWorkers());
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_EQ(0, world->getCountries().at("TWO").getEmployedWorkers());
}


TEST(Vic2World_World_WorldTests, MergingNationsWorks)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("MergeWorld").build())
			  .importWorld(
					*Configuration::Builder().setVic2Path("MergeWorld").setInputFile("MergeWorld/MergeWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_EQ(1, world->getCountries().size());
	ASSERT_TRUE(world->getCountries().contains("FOO"));
	ASSERT_FALSE(world->getCountries().contains("BAR"));
}


TEST(Vic2World_World_WorldTests, ProvinceMappingsAreChecked)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto world = Vic2::World::Factory(*Configuration::Builder().build())
								  .importWorld(*Configuration::Builder().setInputFile("V2World/TestWorld.v2").build(),
										*Mappers::ProvinceMapper::Builder().Build());

	std::cout.rdbuf(stdOutBuf);

	ASSERT_THAT(log.str(),
		 testing::HasSubstr(" [WARNING] No mapping for Vic2 province 1\n"
								  " [WARNING] No mapping for Vic2 province 2\n"
								  " [WARNING] No mapping for Vic2 province 3\n"
								  " [WARNING] No mapping for Vic2 province 4\n"
								  " [WARNING] No mapping for Vic2 province 5\n"));
}


TEST(Vic2World_World_WorldTests, ConquerStrategiesAreConsolidated)
{
	const auto world =
		 Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
			  .importWorld(*Configuration::Builder().setVic2Path("V2World").setInputFile("V2World/TestWorld.v2").build(),
					*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_THAT(world->getCountries().at("ONE").getAI().getConsolidatedStrategies(),
		 testing::UnorderedElementsAre(std::make_pair(std::string("TWO"), 182)));
}


TEST(Vic2World_World_WorldTests, ArmiesAreMovedHome)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("MoveArmiesWorld")
														  .setInputFile("MoveArmiesWorld/MoveArmiesWorld.v2")
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_THAT(world->getCountries().at("ONE").getArmies(),
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
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_TRUE(world->getCountries().contains("NON"));
	ASSERT_THAT(world->getCountries().at("NON").getArmies(),
		 testing::ElementsAre(*Vic2::Army::Builder()
											.setOwner("NON")
											.setName("Not at war country army")
											.setLocation(std::nullopt)
											.Build()));
}


TEST(Vic2World_World_WorldTests, BattlesAreResolved)
{
	const auto world = Vic2::World::Factory(*Configuration::Builder().setVic2Path("V2World").build())
								  .importWorld(*Configuration::Builder()
														  .setVic2Path("ResolveBattlesWorld")
														  .setInputFile("ResolveBattlesWorld/ResolveBattlesWorld.v2")
														  .build(),
										*Mappers::ProvinceMapper::Builder().Build());

	ASSERT_TRUE(world->getCountries().contains("ONE"));
	ASSERT_THAT(world->getCountries().at("ONE").getArmies(),
		 testing::ElementsAre(
			  *Vic2::Army::Builder().setOwner("ONE").setName("No location army").setLocation(std::nullopt).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Only by itself army").setLocation(4).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("First in same-country province").setLocation(2).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Second in same-country province").setLocation(2).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("First in different-country province").setLocation(3).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Non-existent province army").setLocation(5).Build(),
			  *Vic2::Army::Builder().setOwner("ONE").setName("Second non-existent province army").setLocation(5).Build()));
	ASSERT_TRUE(world->getCountries().contains("TWO"));
	ASSERT_THAT(world->getCountries().at("TWO").getArmies(),
		 testing::ElementsAre(*Vic2::Army::Builder()
											.setOwner("TWO")
											.setName("Second in different-country province")
											.setLocation(std::nullopt)
											.Build()));
}