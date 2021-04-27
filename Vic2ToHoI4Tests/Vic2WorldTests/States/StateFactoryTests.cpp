#include "Configuration.h"
#include "V2World/Pops/PopBuilder.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "V2World/States/StateDefinitions.h"
#include "V2World/States/StateDefinitionsBuilder.h"
#include "V2World/States/StateFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_States_StateFactoryTests, GetStateSetsOwner)
{
	std::stringstream input;
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_EQ("TAG", state->getOwner());
}


TEST(Vic2World_States_StateFactoryTests, GetUnownedStateSetsEmptyOwner)
{
	const auto state = Vic2::State::Factory().getUnownedState({}, *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_TRUE(state->getOwner().empty());
}


TEST(Vic2World_States_StateFactoryTests, ProvinceNumbersDefaultsEmpty)
{
	std::stringstream input;
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_TRUE(state->getProvinceNumbers().empty());
}


TEST(Vic2World_States_StateFactoryTests, ProvinceNumbersDefaultsEmptyInUnowned)
{
	std::stringstream input;
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_TRUE(state->getProvinceNumbers().empty());
}


TEST(Vic2World_States_StateFactoryTests, GetStateSetsProvinceNumbers)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_EQ(std::set{42}, state->getProvinceNumbers());
}


TEST(Vic2World_States_StateFactoryTests, GetUnownedStateSetsProvinceNumbers)
{
	const auto state =
		 Vic2::State::Factory().getUnownedState({{42, nullptr}}, *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_EQ(std::set{42}, state->getProvinceNumbers());
}


TEST(Vic2World_States_StateFactoryTests, GetUnownedStateSetsProvinces)
{
	const auto state =
		 Vic2::State::Factory().getUnownedState({{42, nullptr}}, *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_EQ(1, state->getProvinces().size());
	ASSERT_TRUE(state->getProvinces().contains(nullptr));
}


TEST(Vic2World_States_StateFactoryTests, StateIdDefaultsToEmpty)
{
	std::stringstream input;
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_TRUE(state->getStateID().empty());
}


TEST(Vic2World_States_StateFactoryTests, StateIdDefaultsToEmptyInUnowned)
{
	const auto state = Vic2::State::Factory().getUnownedState({}, *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_TRUE(state->getStateID().empty());
}

TEST(Vic2World_States_StateFactoryTests, GetStateSetsStateId)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = Vic2::State::Factory().getState(input,
		 "TAG",
		 *Vic2::StateDefinitions::Builder{}.setProvinceToIDMap({{42, "TEST_STATE"}}).build());

	ASSERT_EQ("TEST_STATE", state->getStateID());
}


TEST(Vic2World_States_StateFactoryTests, GetUnownedStateSetsStateId)
{
	const auto state = Vic2::State::Factory().getUnownedState({{42, nullptr}},
		 *Vic2::StateDefinitions::Builder{}.setProvinceToIDMap({{42, "TEST_STATE"}}).build());

	ASSERT_EQ("TEST_STATE", state->getStateID());
}


TEST(Vic2World_States_StateFactoryTests, EmptyStateIsNotPartial)
{
	std::stringstream input;
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_FALSE(state->isPartialState());
}


TEST(Vic2World_States_StateFactoryTests, EmptyUnownedStateIsNotPartial)
{
	const auto state = Vic2::State::Factory().getUnownedState({}, *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_FALSE(state->isPartialState());
}


TEST(Vic2World_States_StateFactoryTests, StateWithAllProvincesIsNotPartial)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 43 }\n";
	input << "}\n";
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_FALSE(state->isPartialState());
}


TEST(Vic2World_States_StateFactoryTests, UnownedStateWithAllProvincesIsNotPartial)
{
	const auto state = Vic2::State::Factory().getUnownedState({{42, nullptr}, {43, nullptr}},
		 *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_FALSE(state->isPartialState());
}


TEST(Vic2World_States_StateFactoryTests, StateWithMissingProvincesIsPartial)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 43 }\n";
	input << "}\n";
	const auto state = Vic2::State::Factory().getState(input,
		 "TAG",
		 *Vic2::StateDefinitions::Builder{}.setStateMap({{42, {43, 44}}, {43, {42, 44}}, {44, {42, 43}}}).build());

	ASSERT_TRUE(state->isPartialState());
}


TEST(Vic2World_States_StateFactoryTests, UnownedStateWithMissingProvincesIsPartial)
{
	const auto state = Vic2::State::Factory().getUnownedState({{42, nullptr}},
		 *Vic2::StateDefinitions::Builder{}.setStateMap({{42, {43}}, {43, {42}}}).build());

	ASSERT_TRUE(state->isPartialState());
}


TEST(Vic2World_States_StateFactoryTests, CapitalProvinceDefaultsToNullopt)
{
	std::stringstream input;
	const auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_EQ(std::nullopt, state->getCapitalProvince());
}


TEST(Vic2World_States_StateFactoryTests, CapitalProvinceDefaultsToNulloptInUnowned)
{
	const auto state = Vic2::State::Factory().getUnownedState({}, *Vic2::StateDefinitions::Builder{}.build());

	ASSERT_EQ(std::nullopt, state->getCapitalProvince());
}


TEST(Vic2World_States_StateFactoryTests, GetStateSetsCapitalProvince)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = Vic2::State::Factory().getState(input,
		 "TAG",
		 *Vic2::StateDefinitions::Builder{}
				.setProvinceToIDMap({{42, "TEST_STATE"}})
				.setStateToCapitalMap({{"TEST_STATE", 42}})
				.build());

	ASSERT_EQ(42, state->getCapitalProvince());
}


TEST(Vic2World_States_StateFactoryTests, GetUnownedStateSetsCapitalProvince)
{
	const auto state = Vic2::State::Factory().getUnownedState({{42, nullptr}},
		 *Vic2::StateDefinitions::Builder{}
				.setProvinceToIDMap({{42, "TEST_STATE"}})
				.setStateToCapitalMap({{"TEST_STATE", 42}})
				.build());

	ASSERT_EQ(42, state->getCapitalProvince());
}


TEST(Vic2World_States_StateFactoryTests, BuildingLevelIsImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "\tstate_buildings = {\n";
	input << "\t\tlevel = 2\n";
	input << "\t}\n";
	input << "}\n";
	auto state = Vic2::State::Factory().getState(input, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(42)
								  .setPops({*Vic2::Pop::Builder{}.setType("craftsmen").setSize(50000).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(20000, state->getEmployedWorkers());
}