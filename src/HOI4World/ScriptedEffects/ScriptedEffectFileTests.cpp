#include "HOI4World/ScriptedEffects/ScriptedEffectFile.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ScriptedEffects_ScriptedEffectFileTests, EffectsDefaultToZero)
{
	const auto theEffects = HoI4::ScriptedEffectFile().getScriptedEffects("ScriptedEffects/empty_effects_file.txt");

	ASSERT_TRUE(theEffects.empty());
}


TEST(HoI4World_ScriptedEffects_ScriptedEffectFileTests, EffectsCanBeImported)
{
	const auto theEffects = HoI4::ScriptedEffectFile().getScriptedEffects("ScriptedEffects/effects_file.txt");

	ASSERT_EQ(2, theEffects.size());
	ASSERT_EQ("effect_one", theEffects[0].getName());
	ASSERT_EQ("effect_two", theEffects[1].getName());
}