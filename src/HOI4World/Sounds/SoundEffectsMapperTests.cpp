#include "src/HOI4World/Sounds/SoundEffectsMapper.h"
#include "src/HOI4World/Sounds/SoundEffectsMapperFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Sounds_SoundEffectsMapper, UnmatchedEffectsAreEmpty)
{
	const auto soundEffectMapper = HoI4::SoundEffectsMapper::Factory().getMapper();

	ASSERT_TRUE(soundEffectMapper->getMappings("").empty());
}


TEST(HoI4World_Sounds_SoundEffectsMapper, EffectsCanBeMatched)
{
	const auto soundEffectMapper = HoI4::SoundEffectsMapper::Factory().getMapper();

	ASSERT_EQ(1, soundEffectMapper->getMappings("test_culture").size());
	ASSERT_EQ("test_effect", (*soundEffectMapper->getMappings("test_culture").begin()).getName());
	const std::set<std::string> expected{"test_sound"};
	ASSERT_EQ(expected, (*soundEffectMapper->getMappings("test_culture").begin()).getSounds());
}