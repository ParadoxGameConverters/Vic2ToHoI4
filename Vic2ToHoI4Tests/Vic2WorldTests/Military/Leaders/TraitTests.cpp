#include "V2World/Military/Leaders/Trait.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>


TEST(Vic2World_Military_Leaders_TraitTests, TraitEffectsDefaultsToEmpty)
{
	std::stringstream input;
	const auto traitEffects = Vic2::getTraitEffects(input);

	ASSERT_TRUE(traitEffects.empty());
}


TEST(Vic2World_Military_Leaders_TraitTests, TraitEffectsCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdefence = -2\n";
	input << "\torganisation = -0.05\n";
	input << "\tspeed = 0.10\n";
	input << "}";
	const auto traitEffects = Vic2::getTraitEffects(input);

	ASSERT_THAT(traitEffects,
		 testing::UnorderedElementsAre(testing::Pair(std::string("defence"), -2.0F),
			  testing::Pair(std::string("organisation"), -0.05F),
			  testing::Pair(std::string("speed"), 0.10F)));
}


TEST(Vic2World_Military_Leaders_TraitTests, BadTraitEffectAmountsAreLogged)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdefence = foo\n";
	input << "}";

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	const auto traitEffects = Vic2::getTraitEffects(input);
	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] Trait effect amount couldn't be parsed\n", log.str());
}