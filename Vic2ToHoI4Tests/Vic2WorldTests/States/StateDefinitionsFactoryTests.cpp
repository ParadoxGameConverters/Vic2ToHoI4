#include "Configuration.h"
#include "V2World/Mods/ModBuilder.h"
#include "V2World/States/StateDefinitionsFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_States_StateDefinitionsFactoryTests, ProvincesInStateAreImported)
{
	const auto configuration = Configuration::Builder().setVic2Path("./").build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	const std::set<int> expectedProvinces{1, 2, 3};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateIdsAreImported)
{
	const auto configuration = Configuration::Builder().setVic2Path("./").build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ("VANILLA_STATE", stateDefinitions->getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateCapitalsAreImported)
{
	const auto configuration = Configuration::Builder().setVic2Path("./").build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ(1, stateDefinitions->getCapitalProvince("VANILLA_STATE"));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, ProvincesInStateAreImportedFromMod)
{
	const auto configuration = Configuration::Builder()
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	const std::set<int> expectedProvinces{4, 5, 6};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(4));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateIdsAreImportedFromMod)
{
	const auto configuration = Configuration::Builder()
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ("MOD_STATE", stateDefinitions->getStateID(4));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateCapitalsAreImportedFromMod)
{
	const auto configuration = Configuration::Builder()
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ(4, stateDefinitions->getCapitalProvince("MOD_STATE"));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaProvincesInStateAreNotImportedIfModImported)
{
	const auto configuration = Configuration::Builder()
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	const std::set<int> expectedProvinces{};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaStateIdsAreNotImportedIfModImported)
{
	const auto configuration = Configuration::Builder()
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ(std::nullopt, stateDefinitions->getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaStateCapitalsAreNotImportedIfModImported)
{
	const auto configuration = Configuration::Builder()
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ(std::nullopt, stateDefinitions->getCapitalProvince("VANILLA_STATE"));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaProvincesInStateAreImportedIfModNotImported)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./")
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("empty_test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	const std::set<int> expectedProvinces{1, 2, 3};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaStateIdsAreImportedIfModNotImported)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./")
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("empty_test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ("VANILLA_STATE", stateDefinitions->getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaStateCapitalsAreImportedIfModNotImported)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./")
											 .setVic2ModPath("./mod")
											 .addVic2Mod(*Vic2::Mod::Builder().setDirectory("empty_test_mod").build())
											 .build();
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(*configuration);

	ASSERT_EQ(1, stateDefinitions->getCapitalProvince("VANILLA_STATE"));
}