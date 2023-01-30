#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Sounds/SoundEffectsMapperLink.h"
#include "src/HOI4World/Sounds/SoundEffectsMapperLinkFactory.h"



TEST(HoI4World_Sounds_SoundEffectsMapperLink, CulturesDefaultToEmpty)
{
	std::stringstream input;
	const auto soundEffectMapperLink = HoI4::SoundEffectsMapperLink::Factory().getSoundEffectMapperLink(input);

	ASSERT_TRUE(soundEffectMapperLink->getCultures().empty());
}


TEST(HoI4World_Sounds_SoundEffectsMapperLink, CulturesCanBeAdded)
{
	std::stringstream input;
	input << "= { culture = test_culture culture = another_culture }";
	const auto soundEffectMapperLink = HoI4::SoundEffectsMapperLink::Factory().getSoundEffectMapperLink(input);

	ASSERT_EQ(2, soundEffectMapperLink->getCultures().size());
	ASSERT_TRUE(soundEffectMapperLink->getCultures().contains("test_culture"));
	ASSERT_TRUE(soundEffectMapperLink->getCultures().contains("another_culture"));
}


TEST(HoI4World_Sounds_SoundEffectsMapperLink, SoundsDefaultToEmpty)
{
	std::stringstream input;
	const auto soundEffectMapperLink = HoI4::SoundEffectsMapperLink::Factory().getSoundEffectMapperLink(input);

	ASSERT_TRUE(soundEffectMapperLink->getSounds().empty());
}


TEST(HoI4World_Sounds_SoundEffectsMapperLink, SoundsCanBeAdded)
{
	std::stringstream input;
	input << "= { sound = test_sound sound = another_sound }";
	const auto soundEffectMapperLink = HoI4::SoundEffectsMapperLink::Factory().getSoundEffectMapperLink(input);

	ASSERT_EQ(2, soundEffectMapperLink->getSounds().size());
	ASSERT_TRUE(soundEffectMapperLink->getSounds().contains("test_sound"));
	ASSERT_TRUE(soundEffectMapperLink->getSounds().contains("another_sound"));
}