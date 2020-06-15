#include "../../../Vic2ToHoI4/Source/Configuration.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateDefinitionsFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_States_StateDefinitionsFactoryTests, ProvincesInStateAreImported)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	const std::set<int> expectedProvinces{1, 2, 3};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateIdsAreImported)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	ASSERT_EQ("VANILLA_STATE", stateDefinitions->getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateCapitalsAreImported)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	ASSERT_EQ(1, stateDefinitions->getCapitalProvince("VANILLA_STATE"));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, ProvincesInStateAreImportedFromMod)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {"test_mod"},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	const std::set<int> expectedProvinces{4, 5, 6};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(4));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateIdsAreImportedFromMod)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {"test_mod"},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	ASSERT_EQ("MOD_STATE", stateDefinitions->getStateID(4));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, StateCapitalsAreImportedFromMod)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {"test_mod"},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	ASSERT_EQ(4, stateDefinitions->getCapitalProvince("MOD_STATE"));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaProvincesInStateAreNotImportedIfModImported)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {"test_mod"},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	const std::set<int> expectedProvinces{};
	ASSERT_EQ(expectedProvinces, stateDefinitions->getAllProvinces(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaStateIdsAreNotImportedIfModImported)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {"test_mod"},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	ASSERT_EQ(std::nullopt, stateDefinitions->getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsFactoryTests, VanillaStateCapitalsAreNotImportedIfModImported)
{
	const Configuration testConfiguration("",
		 "",
		 "",
		 "./",
		 {"test_mod"},
		 0.0f,
		 0.0f,
		 0.0f,
		 0.0f,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);

	const auto stateDefinitions = Vic2::StateDefinitions::Factory{}.getStateDefinitions(testConfiguration);

	ASSERT_EQ(std::nullopt, stateDefinitions->getCapitalProvince("VANILLA_STATE"));
}