#include "../../../Vic2ToHoI4/Source/V2World/States/StateDefinitions.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_StateDefinitionsTests, GetAllProvincesReturnsNoProvincesForMissingState)
{
	const Vic2::StateDefinitions stateDefinitions(std::map<int, std::set<int>>{},
		 std::map<int, std::string>{},
		 std::map<std::string, int>{});

	ASSERT_TRUE(stateDefinitions.getAllProvinces(1).empty());
}


TEST(Vic2World_StateDefinitionsTests, GetAllProvincesReturnsProvincesForMatchedState)
{
	const Vic2::StateDefinitions stateDefinitions(std::map<int, std::set<int>>{{1, {1, 2, 3}}},
		 std::map<int, std::string>{},
		 std::map<std::string, int>{});

	ASSERT_EQ(static_cast<std::set<int>>(std::set<int>{1, 2, 3}), stateDefinitions.getAllProvinces(1));
}


TEST(Vic2World_StateDefinitionsTests, GetStateIdReturnsNulloptForUnmatchedProvince)
{
	const Vic2::StateDefinitions stateDefinitions(std::map<int, std::set<int>>{},
		 std::map<int, std::string>{},
		 std::map<std::string, int>{});

	ASSERT_EQ(std::nullopt, stateDefinitions.getStateID(1));
}


TEST(Vic2World_StateDefinitionsTests, GetStateIdReturnsStateIdForMatchedProvince)
{
	const Vic2::StateDefinitions stateDefinitions(std::map<int, std::set<int>>{},
		 std::map<int, std::string>{{1, "STATE_1"}},
		 std::map<std::string, int>{});

	ASSERT_EQ("STATE_1", stateDefinitions.getStateID(1));
}


TEST(Vic2World_StateDefinitionsTests, GetCapitalProvinceReturnsNulloptForUnmatchedStateId)
{
	const Vic2::StateDefinitions stateDefinitions(std::map<int, std::set<int>>{},
		 std::map<int, std::string>{},
		 std::map<std::string, int>{});

	ASSERT_EQ(std::nullopt, stateDefinitions.getCapitalProvince("STATE_1"));
}


TEST(Vic2World_StateDefinitionsTests, GetCapitalProvinceReturnsCapitalForMatchedStateId)
{
	const Vic2::StateDefinitions stateDefinitions(std::map<int, std::set<int>>{},
		 std::map<int, std::string>{},
		 std::map<std::string, int>{{"STATE_1", 1}});

	ASSERT_EQ(1, stateDefinitions.getCapitalProvince("STATE_1"));
}