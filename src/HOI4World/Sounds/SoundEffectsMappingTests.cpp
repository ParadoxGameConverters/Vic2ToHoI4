#include "src/HOI4World/Sounds/SoundEffectsMapping.h"
#include "gtest/gtest.h"



TEST(HoI4World_Sounds_SoundEffectsMapping, NameCanBeSet)
{
	const HoI4::SoundEffectsMapping soundEffectsMapping("test_name", {});

	ASSERT_EQ("test_name", soundEffectsMapping.getName());
}


TEST(HoI4World_Sounds_SoundEffectsMapping, SoundsCanBeSet)
{
	const HoI4::SoundEffectsMapping soundEffectsMapping("", {"sound_one", "sound_two"});

	const std::set<std::string> expected{"sound_one", "sound_two"};
	ASSERT_EQ(expected, soundEffectsMapping.getSounds());
}


TEST(HoI4World_Sounds_SoundEffectsMapping, SortOrderIsFromName)
{
	const HoI4::SoundEffectsMapping soundEffectsMapping("test_name", {});
	const HoI4::SoundEffectsMapping soundEffectsMapping2("test_name2", {});

	ASSERT_LT(soundEffectsMapping, soundEffectsMapping2);
}