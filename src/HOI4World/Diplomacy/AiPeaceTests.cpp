#include "src/HOI4World/Diplomacy/AIPeace.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Diplomacy_AiPeaceTests, nameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	ASSERT_EQ(aiPeace.getName(), "name");
}


TEST(HoI4World_Diplomacy_AiPeaceTests, everythingOutputsDefault)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tannex_randomness = 0\n";
	expectedOutput << "\tliberate_randomness = 0\n";
	expectedOutput << "\tpuppet_randomness = 0\n";
	expectedOutput << "\ttake_states_randomness = 0\n";
	expectedOutput << "\tforce_government_randomness = 0\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\tpuppet_all \n";
	expectedOutput << "\tpuppet_state \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, itemsCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tenable = { enable_condition }\n";
	input << "\tannex_randomness = 5\n";
	input << "\tliberate_randomness = 6\n";
	input << "\tpuppet_randomness = 7\n";
	input << "\ttake_states_randomness = 8\n";
	input << "\tforce_government_randomness = 9\n";
	input << "\tannex = { annex_condition }\n";
	input << "\tliberate = { liberate_condition }\n";
	input << "\tpuppet = { puppet_condition }\n";
	input << "\tpuppet_all = { puppet_all_condition }\n";
	input << "\tpuppet_state = { puppet_state_condition }\n";
	input << "\ttake_states = { take_states_condition }\n";
	input << "\tforce_government = { force_government_condition }\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tenable = { enable_condition }\n";
	expectedOutput << "\tannex_randomness = 5\n";
	expectedOutput << "\tliberate_randomness = 6\n";
	expectedOutput << "\tpuppet_randomness = 7\n";
	expectedOutput << "\ttake_states_randomness = 8\n";
	expectedOutput << "\tforce_government_randomness = 9\n";
	expectedOutput << "\tannex = { annex_condition }\n";
	expectedOutput << "\tliberate = { liberate_condition }\n";
	expectedOutput << "\tpuppet = { puppet_condition }\n";
	expectedOutput << "\tpuppet_all = { puppet_all_condition }\n";
	expectedOutput << "\tpuppet_state = { puppet_state_condition }\n";
	expectedOutput << "\ttake_states = { take_states_condition }\n";
	expectedOutput << "\tforce_government = { force_government_condition }\n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, enableCanBeChanged)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tenable = { enable_condition }\n";
	input << "}";
	HoI4::AiPeace aiPeace("name", input);
	aiPeace.replaceEnable("= { enable_condition }");

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tenable = { enable_condition }\n";
	expectedOutput << "\tannex_randomness = 0\n";
	expectedOutput << "\tliberate_randomness = 0\n";
	expectedOutput << "\tpuppet_randomness = 0\n";
	expectedOutput << "\ttake_states_randomness = 0\n";
	expectedOutput << "\tforce_government_randomness = 0\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\tpuppet_all \n";
	expectedOutput << "\tpuppet_state \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}