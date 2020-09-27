#ifndef SOUND_EFFECTS_MAPPER_H
#define SOUND_EFFECTS_MAPPER_H



#include "SoundEffectsMapping.h"
#include <set>



namespace HoI4
{

class SoundEffectsMapper
{
  public:
	std::set<SoundEffectsMapping> getMappings(const std::string& culture);
};

} // namespace HoI4



#endif // SOUND_EFFECTS_MAPPER_H