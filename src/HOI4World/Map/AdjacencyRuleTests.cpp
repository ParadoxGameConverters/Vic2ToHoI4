#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/AdjacencyRule.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/V2World/States/StateBuilder.h"
#include <sstream>



TEST(HoI4World_Map_AdjacencyRule, NameDefaultsToEmpty)
{
	std::stringstream input;
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_EQ("", adjacencyRule.getName());
}


TEST(HoI4World_Map_AdjacencyRule, NameCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tname = \"CANAL\"\n";
	input << "}\n";
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_EQ("CANAL", adjacencyRule.getName());
}

TEST(HoI4World_Map_AdjacencyRule, RulesDefaultToEmpty)
{
	std::stringstream input;
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_TRUE(adjacencyRule.getRules().empty());
}


TEST(HoI4World_Map_AdjacencyRule, RuleCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tcontested =\n";
	input << "\t{\n";
	input << "\t\tarmy = no\n";
	input << "\t\tnavy = no\n";
	input << "\t\tsubmarine = no\n";
	input << "\t\ttrade = no\n";
	input << "\t}\n";
	input << "}\n";
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_TRUE(adjacencyRule.getRules().contains("contested"));
}

TEST(HoI4World_Map_AdjacencyRule, RequiredProvincesDefaultToEmpty)
{
	std::stringstream input;
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_TRUE(adjacencyRule.getRequiredProvinces().empty());
}


TEST(HoI4World_Map_AdjacencyRule, RequiredProvincesCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\trequired_provinces = { 42 }\n";
	input << "}\n";
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);
	const auto& provinces = adjacencyRule.getRequiredProvinces();

	EXPECT_FALSE(std::find(provinces.begin(), provinces.end(), 42) == provinces.end());
}

TEST(HoI4World_Map_AdjacencyRule, IsDisabledStrDefaultsToNullopt)
{
	std::stringstream input;
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_EQ(std::nullopt, adjacencyRule.getIsDisabledStr());
}


TEST(HoI4World_Map_AdjacencyRule, IsDisabledStrCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tis_disabled = {\n";
	input << "\t\thas_global_flag = CANAL_BLOCKED\n";
	input << "\t}\n";
	input << "}\n";
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	ASSERT_TRUE(adjacencyRule.getIsDisabledStr());

	std::stringstream expectedOutput;
	expectedOutput << "= {\n";
	expectedOutput << "\t\thas_global_flag = CANAL_BLOCKED\n";
	expectedOutput << "\t}";

	EXPECT_EQ(expectedOutput.str(), *adjacencyRule.getIsDisabledStr());
}


TEST(HoI4World_Map_AdjacencyRule, IsDisabledStrCanBeUpdated)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tis_disabled = {\n";
	input << "\t\t$STATE = { }\n";
	input << "\t}\n";
	input << "\ticon = 42\n";
	input << "}\n";
	auto adjacencyRule = HoI4::AdjacencyRule(input);

	ASSERT_TRUE(adjacencyRule.getIsDisabledStr());

	const auto& sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 123, "TAG");
	theState.addProvince(42);
	std::map<int, HoI4::State> states = {{123, theState}};
	adjacencyRule.updateIsDisabledStr(states);

	std::stringstream expectedOutput;
	expectedOutput << "= {\n";
	expectedOutput << "\t\t123 = { }\n";
	expectedOutput << "\t}";

	EXPECT_EQ(expectedOutput.str(), *adjacencyRule.getIsDisabledStr());
}


TEST(HoI4World_Map_AdjacencyRule, IconDefaultsToZero)
{
	std::stringstream input;
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_EQ(0, adjacencyRule.getIcon());
}


TEST(HoI4World_Map_AdjacencyRule, IconCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\ticon = 42\n";
	input << "}\n";
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_EQ(42, adjacencyRule.getIcon());
}

TEST(HoI4World_Map_AdjacencyRule, OffsetDefaultsToEmpty)
{
	std::stringstream input;
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);

	EXPECT_TRUE(adjacencyRule.getOffset().empty());
}


TEST(HoI4World_Map_AdjacencyRule, OffsetCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toffset = { -3 0 -2 }\n";
	input << "}\n";
	const auto& adjacencyRule = HoI4::AdjacencyRule(input);
	const auto& offset = adjacencyRule.getOffset();

	EXPECT_EQ(3, offset.size());
	EXPECT_FALSE(std::find(offset.begin(), offset.end(), -3.0f) == offset.end());
	EXPECT_FALSE(std::find(offset.begin(), offset.end(), 0.0f) == offset.end());
	EXPECT_FALSE(std::find(offset.begin(), offset.end(), -2.0f) == offset.end());
}