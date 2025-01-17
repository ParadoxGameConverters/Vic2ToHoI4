#include "external/common_items/Log.h"
#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/AdjacencyRules.h"
#include "src/HOI4World/States/HoI4State.h"
#include <sstream>



TEST(HoI4World_Map_AdjacencyRules, DefaultAdjacencyRulesCanBeImported)
{
	const std::map<int, HoI4::State> states;
	const auto& adjacencyRules = HoI4::AdjacencyRules(states);

	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tname = \"CANAL\"\n";
	input << "\n";
	input << "\tcontested =\n";
	input << "\t{\n";
	input << "\t\tarmy = no\n";
	input << "\t\tnavy = no\n";
	input << "\t\tsubmarine = no\n";
	input << "\t\ttrade = no\n";
	input << "\t}\n";
	input << "\t\n";
	input << "\trequired_provinces = { 42 1234 }\n";
	input << "\n";
	input << "\tis_disabled = {\n";
	input << "\t\tOR = {\n";
	input << "\t\t\thas_global_flag = CANAL_BLOCKED\n";
	input << "\t\t\thas_country_flag = CANAL_BLOCKED_FOR_COUNTRY\n";
	input << "\t\t\t$STATE = {\n";
	input << "\t\t\t\thas_dynamic_modifier = {\n";
	input << "\t\t\t\t\tmodifier = canal_damaged_modifier\n";
	input << "\t\t\t\t\tscope = THIS\n";
	input << "\t\t\t\t}\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\ttooltip = canal_damaged_tt\n";
	input << "\t}\n";
	input << "\t\t\n";
	input << "\ticon = 7617\n";
	input << "\toffset = { -3 0 -2 }\n";
	input << "}\n";

	const auto& adjacencyRule = std::make_shared<HoI4::AdjacencyRule>(input);

	EXPECT_THAT(adjacencyRules.getRules(), testing::UnorderedElementsAre(testing::Pair("CANAL", adjacencyRule)));
}