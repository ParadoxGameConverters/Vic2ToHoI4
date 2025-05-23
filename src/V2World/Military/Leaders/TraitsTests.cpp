#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Military/Leaders/Traits.h"
#include "src/V2World/Military/Leaders/TraitsFactory.h"



TEST(Vic2World_Military_Leaders_TraitsTests, MissingTraitsHaveNoEffects)
{
	const auto traits = Vic2::Traits::Factory().LoadTraits(commonItems::ModFilesystem());

	ASSERT_TRUE(traits->getEffectsForTrait("missing_trait").empty());
}


TEST(Vic2World_Military_Leaders_TraitsTests, TraitEffectsAreReturned)
{
	const auto traits = Vic2::Traits::Factory().LoadTraits(commonItems::ModFilesystem());
	const auto effects = traits->getEffectsForTrait("test_trait");

	ASSERT_THAT(effects,
		 testing::UnorderedElementsAre(testing::Pair(std::string("effect_one"), -2.0F),
			  testing::Pair(std::string("effect_two"), -0.05F),
			  testing::Pair(std::string("effect_three"), 0.10F)));
}