#include "HOI4World/Diplomacy/AIPeace.h"
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
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, enableCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tenable = { enable_condition }\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

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
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
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
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, annexRandomnessCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tannex_randomness = 5\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tannex_randomness = 5\n";
	expectedOutput << "\tliberate_randomness = 0\n";
	expectedOutput << "\tpuppet_randomness = 0\n";
	expectedOutput << "\ttake_states_randomness = 0\n";
	expectedOutput << "\tforce_government_randomness = 0\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, liberateRandomnessCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tliberate_randomness = 5\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tannex_randomness = 0\n";
	expectedOutput << "\tliberate_randomness = 5\n";
	expectedOutput << "\tpuppet_randomness = 0\n";
	expectedOutput << "\ttake_states_randomness = 0\n";
	expectedOutput << "\tforce_government_randomness = 0\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, puppetRandomnessCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpuppet_randomness = 5\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tannex_randomness = 0\n";
	expectedOutput << "\tliberate_randomness = 0\n";
	expectedOutput << "\tpuppet_randomness = 5\n";
	expectedOutput << "\ttake_states_randomness = 0\n";
	expectedOutput << "\tforce_government_randomness = 0\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, takeStatesRandomnessCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttake_states_randomness = 5\n";
	input << "}";
	const HoI4::AiPeace aiPeace("name", input);

	std::stringstream output;
	output << aiPeace;

	std::stringstream expectedOutput;
	expectedOutput << "name = {\n";
	expectedOutput << "\tannex_randomness = 0\n";
	expectedOutput << "\tliberate_randomness = 0\n";
	expectedOutput << "\tpuppet_randomness = 0\n";
	expectedOutput << "\ttake_states_randomness = 5\n";
	expectedOutput << "\tforce_government_randomness = 0\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, forceGovernmentRandomnessCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tforce_government_randomness = 5\n";
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
	expectedOutput << "\tforce_government_randomness = 5\n";
	expectedOutput << "\tannex \n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, annexCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tannex = { annex_condition }\n";
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
	expectedOutput << "\tannex = { annex_condition }\n";
	expectedOutput << "\tliberate \n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, liberateCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tliberate = { liberate_condition }\n";
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
	expectedOutput << "\tliberate = { liberate_condition }\n";
	expectedOutput << "\tpuppet \n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, puppetCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpuppet = { puppet_condition }\n";
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
	expectedOutput << "\tpuppet = { puppet_condition }\n";
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, takeStatesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttake_states = { take_states_condition }\n";
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
	expectedOutput << "\ttake_states = { take_states_condition }\n";
	expectedOutput << "\tforce_government \n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_AiPeaceTests, forceGovernmentCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tforce_government = { force_government_condition }\n";
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
	expectedOutput << "\ttake_states \n";
	expectedOutput << "\tforce_government = { force_government_condition }\n";
	expectedOutput << "}";

	ASSERT_EQ(expectedOutput.str(), output.str());
}