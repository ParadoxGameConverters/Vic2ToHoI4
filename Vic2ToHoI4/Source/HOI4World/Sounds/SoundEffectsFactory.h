#ifndef SOUND_EFFECTS_FACTORY_H
#define SOUND_EFFECTS_FACTORY_H



#include "SoundEffect.h"
#include <vector>



namespace HoI4
{

class SoundEffectsFactory
{
  public:
	std::vector<SoundEffect> createSoundEffects();
};

} // namespace HoI4



#endif // SOUND_EFFECTS_FACTORY_H