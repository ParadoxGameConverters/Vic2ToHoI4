#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/States/StateDefinitions.h"
#include "src/V2World/States/StateDefinitionsBuilder.h"



TEST(Vic2World_States_StateDefinitionsTests, GetAllProvincesReturnsNoProvincesForMissingState)
{
	const auto stateDefinitions = *Vic2::StateDefinitions::Builder().build();

	ASSERT_TRUE(stateDefinitions.getAllProvinces(1).empty());
}


TEST(Vic2World_States_StateDefinitionsTests, GetAllProvincesReturnsProvincesForMatchedState)
{
	const auto stateDefinitions =
		 *Vic2::StateDefinitions::Builder().setStateMap(std::map<int, std::set<int>>{{1, {1, 2, 3}}}).build();

	ASSERT_EQ(static_cast<std::set<int>>(std::set{1, 2, 3}), stateDefinitions.getAllProvinces(1));
}


TEST(Vic2World_States_StateDefinitionsTests, GetStateIdReturnsNulloptForUnmatchedProvince)
{
	const auto stateDefinitions = *Vic2::StateDefinitions::Builder().build();

	ASSERT_EQ(std::nullopt, stateDefinitions.getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsTests, GetStateIdReturnsStateIdForMatchedProvince)
{
	const auto stateDefinitions = *Vic2::StateDefinitions::Builder().setProvinceToIDMap({{1, "STATE_1"}}).build();

	ASSERT_EQ("STATE_1", stateDefinitions.getStateID(1));
}


TEST(Vic2World_States_StateDefinitionsTests, GetCapitalProvinceReturnsNulloptForUnmatchedStateId)
{
	const auto stateDefinitions = *Vic2::StateDefinitions::Builder().build();

	ASSERT_EQ(std::nullopt, stateDefinitions.getCapitalProvince("STATE_1"));
}


TEST(Vic2World_States_StateDefinitionsTests, GetCapitalProvinceReturnsCapitalForMatchedStateId)
{
	const auto stateDefinitions = *Vic2::StateDefinitions::Builder().setStateToCapitalMap({{"STATE_1", 1}}).build();

	ASSERT_EQ(1, stateDefinitions.getCapitalProvince("STATE_1"));
}