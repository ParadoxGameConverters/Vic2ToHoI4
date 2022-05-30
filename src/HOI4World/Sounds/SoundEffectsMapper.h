#ifndef SOUND_EFFECTS_MAPPER_H
#define SOUND_EFFECTS_MAPPER_H


#include <map>

#include "SoundEffectsMapping.h"
#include <set>



namespace HoI4
{

class SoundEffectsMapper
{
  public:
	class Factory;

	std::set<SoundEffectsMapping> getMappings(const std::string& culture);

  private:
	std::map<std::string, std::set<SoundEffectsMapping>> mappings;
};

} // namespace HoI4



#endif // SOUND_EFFECTS_MAPPER_H