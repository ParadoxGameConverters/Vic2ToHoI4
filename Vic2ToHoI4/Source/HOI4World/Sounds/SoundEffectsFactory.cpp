#include "SoundEffectsFactory.h"



std::vector<HoI4::SoundEffect> HoI4::SoundEffectsFactory::createSoundEffects()
{
	return std::vector<HoI4::SoundEffect>{SoundEffect{"TAG_infantry_idle", {"de_Idle_001", "de_Idle_002"}}};
}