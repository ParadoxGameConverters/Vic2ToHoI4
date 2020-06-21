#include "../../../Vic2ToHoI4/Source/Configuration.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateDefinitions.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_States_StateFactoryTests: public testing::Test
{
  protected:
	Vic2World_States_StateFactoryTests();
	Vic2::State::Factory factory;

	std::unique_ptr<Vic2::StateDefinitions> stateDefinitions;
};


Vic2World_States_StateFactoryTests::Vic2World_States_StateFactoryTests()
{
	std::map<int, std::set<int>> stateMap{{42, {43}}, {43, {42}}};
	std::map<int, std::string> provinceToIDMap{{42, "TEST_STATE"}};
	std::map<std::string, int> stateToCapitalMap{{"TEST_STATE", 42}};
	stateDefinitions = std::make_unique<Vic2::StateDefinitions>(stateMap, provinceToIDMap, stateToCapitalMap);
}


TEST_F(Vic2World_States_StateFactoryTests, GetStateSetsOwner)
{
	std::stringstream input;
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_EQ("TAG", state->getOwner());
}


TEST_F(Vic2World_States_StateFactoryTests, GetUnownedStateSetsEmptyOwner)
{
	const auto state = factory.getUnownedState({}, *stateDefinitions);

	ASSERT_TRUE(state->getOwner().empty());
}


TEST_F(Vic2World_States_StateFactoryTests, ProvinceNumbersDefaultsEmpty)
{
	std::stringstream input;
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_TRUE(state->getProvinceNumbers().empty());
}


TEST_F(Vic2World_States_StateFactoryTests, ProvinceNumbersDefaultsEmptyInUnowned)
{
	std::stringstream input;
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_TRUE(state->getProvinceNumbers().empty());
}


TEST_F(Vic2World_States_StateFactoryTests, GetStateSetsProvinceNumbers)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_EQ(std::set<int>{42}, state->getProvinceNumbers());
}


TEST_F(Vic2World_States_StateFactoryTests, GetUnownedStateSetsProvinceNumbers)
{
	const auto state = factory.getUnownedState({{42, nullptr}}, *stateDefinitions);

	ASSERT_EQ(std::set<int>{42}, state->getProvinceNumbers());
}


TEST_F(Vic2World_States_StateFactoryTests, GetUnownedStateSetsProvinces)
{
	const auto state = factory.getUnownedState({{42, nullptr}}, *stateDefinitions);

	ASSERT_EQ(1, state->getProvinces().size());
	ASSERT_TRUE(state->getProvinces().count(nullptr));
}


TEST_F(Vic2World_States_StateFactoryTests, StateIdDefaultsToEmpty)
{
	std::stringstream input;
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_TRUE(state->getStateID().empty());
}


TEST_F(Vic2World_States_StateFactoryTests, StateIdDefaultsToEmptyInUnowned)
{
	const auto state = factory.getUnownedState({}, *stateDefinitions);

	ASSERT_TRUE(state->getStateID().empty());
}

TEST_F(Vic2World_States_StateFactoryTests, GetStateSetsStateId)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_EQ("TEST_STATE", state->getStateID());
}


TEST_F(Vic2World_States_StateFactoryTests, GetUnownedStateSetsStateId)
{
	const auto state = factory.getUnownedState({{42, nullptr}}, *stateDefinitions);

	ASSERT_EQ("TEST_STATE", state->getStateID());
}


TEST_F(Vic2World_States_StateFactoryTests, EmptyStateIsNotPartial)
{
	std::stringstream input;
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_FALSE(state->isPartialState());
}


TEST_F(Vic2World_States_StateFactoryTests, EmptyUnownedStateIsNotPartial)
{
	const auto state = factory.getUnownedState({}, *stateDefinitions);

	ASSERT_FALSE(state->isPartialState());
}


TEST_F(Vic2World_States_StateFactoryTests, StateWithAllProvincesIsNotPartial)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 43 }\n";
	input << "}\n";
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_FALSE(state->isPartialState());
}


TEST_F(Vic2World_States_StateFactoryTests, UnownedStateWithAllProvincesIsNotPartial)
{
	const auto state = factory.getUnownedState({{42, nullptr}, {43, nullptr}}, *stateDefinitions);

	ASSERT_FALSE(state->isPartialState());
}


TEST_F(Vic2World_States_StateFactoryTests, StateWithMissingProvincesIsPartial)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_TRUE(state->isPartialState());
}


TEST_F(Vic2World_States_StateFactoryTests, UnownedStateWithMissingProvincesIsPartial)
{
	const auto state = factory.getUnownedState({{42, nullptr}}, *stateDefinitions);

	ASSERT_TRUE(state->isPartialState());
}


TEST_F(Vic2World_States_StateFactoryTests, CapitalProvinceDefaultsToNullopt)
{
	std::stringstream input;
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_EQ(std::nullopt, state->getCapitalProvince());
}


TEST_F(Vic2World_States_StateFactoryTests, CapitalProvinceDefaultsToNulloptInUnowned)
{
	const auto state = factory.getUnownedState({}, *stateDefinitions);

	ASSERT_EQ(std::nullopt, state->getCapitalProvince());
}


TEST_F(Vic2World_States_StateFactoryTests, GetStateSetsCapitalProvince)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 42 }\n";
	input << "}\n";
	const auto state = factory.getState(input, "TAG", *stateDefinitions);

	ASSERT_EQ(42, state->getCapitalProvince());
}


TEST_F(Vic2World_States_StateFactoryTests, GetUnownedStateSetsCapitalProvince)
{
	const auto state = factory.getUnownedState({{42, nullptr}}, *stateDefinitions);

	ASSERT_EQ(42, state->getCapitalProvince());
}