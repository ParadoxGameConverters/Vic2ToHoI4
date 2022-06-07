#include "src/V2World/Military/Leaders/TraitGroup.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>


TEST(Vic2World_Military_Leaders_TraitGroupTests, TraitsDefaultsToEmpty)
{
	std::stringstream input;

	Vic2::TraitGroup group(input);
	const auto traits = group.takeTraits();

	ASSERT_TRUE(traits.empty());
}


TEST(Vic2World_Military_Leaders_TraitGroupTests, TraitsCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trelentless = {\n";
	input << "\t\tattack = 2\n";
	input << "\t}\n";
	input << "\tactive_p = {\n";
	input << "\t\tspeed = 0.05\n";
	input << "\t}\n";
	input << "}";

	Vic2::TraitGroup group(input);
	const auto traits = group.takeTraits();

	ASSERT_THAT(traits,
		 testing::UnorderedElementsAre(testing::Pair(std::string("relentless"), Vic2::TraitEffects{{"attack", 2.0F}}),
			  testing::Pair(std::string("active_p"), Vic2::TraitEffects{{"speed", 0.05F}})));
}