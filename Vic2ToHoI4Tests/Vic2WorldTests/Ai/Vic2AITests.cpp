#include "../Vic2ToHoI4/Source/V2World/Ai/Vic2AI.h"
#include "../Vic2ToHoI4/Source/V2World/Ai/AIStrategy.h"
#include "../Vic2ToHoI4/Source/V2World/World.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "gtest/gtest.h"

TEST(Vic2World_Vic2_AI_Tests, AiStrategiesDefaultToEmpty)
{
	std::stringstream input;
	const auto newVic2Ai = Vic2::Vic2AI(input);

	ASSERT_TRUE(newVic2Ai.getStrategies().empty());
}


TEST(Vic2World_Vic2_AI_Tests, AiStrategiesSetWhenGivenInput)
{
	std::stringstream input;
	input << "\tai=\n";
	input << "\t{\n";
	input << "\t\tinitialized=yes\n";
	input << "\t\tconsolidate=yes\n";
	input << "\t\tdate=\"1865.10.22\"\n";
	input << "\t\tstatic=no\n";
	input << "\t\tpersonality=balanced\n";
	input << "\t\tconquer_prov=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=278\n";
	input << "\t\t\tvalue=182\n";
	input << "\t\t}\n";
	input << "\t\trival=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=\"PSA\"\n";
	input << "\t\t\tvalue=30\n";
	input << "\t\t}\n";
	input << "\t\tmilitary_access=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=\"NAV\"\n";
	input << "\t\t\tvalue=50\n";
	input << "\t\t}\n";
	input << "\t}\n";
	const auto newVic2Ai = Vic2::Vic2AI(input);

	for (const auto& aiStrategy: newVic2Ai.getStrategies())
	{
		ASSERT_EQ("threat|antagonize|befriend|protect|rival", aiStrategy.getType());
	}
}

TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesDefaultToEmpty)
{
	std::stringstream input;
	const auto newVic2Ai = Vic2::Vic2AI(input);

	ASSERT_TRUE(newVic2Ai.getConquerStrategies().empty());
}


TEST(Vic2World_Vic2_AI_Tests, ConquerStrategiesSetWhenGivenInput)
{
	std::stringstream input;
	input << "\tai=\n";
	input << "\t{\n";
	input << "\t\tinitialized=yes\n";
	input << "\t\tconsolidate=yes\n";
	input << "\t\tdate=\"1865.10.22\"\n";
	input << "\t\tstatic=no\n";
	input << "\t\tpersonality=balanced\n";
	input << "\t\tconquer_prov=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=278\n";
	input << "\t\t\tvalue=182\n";
	input << "\t\t}\n";
	input << "\t\trival=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=\"PSA\"\n";
	input << "\t\t\tvalue=30\n";
	input << "\t\t}\n";
	input << "\t\tmilitary_access=\n";
	input << "\t\t{\n";
	input << "\t\t\tid=\"NAV\"\n";
	input << "\t\t\tvalue=50\n";
	input << "\t\t}\n";
	input << "\t}\n";
	const auto newVic2Ai = Vic2::Vic2AI(input);

	for (const auto& conquerStrategy: newVic2Ai.getConquerStrategies())
	{
		ASSERT_EQ("conquer_prov", conquerStrategy.getType());
	}
}
