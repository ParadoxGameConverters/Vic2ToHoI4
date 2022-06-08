#ifndef SOUND_EFFECT_MAPPING_H
#define SOUND_EFFECT_MAPPING_H


#include <vector>

#include "src/HOI4World/Sounds/SoundEffectsMapperLink.h"



namespace HoI4
{

class SoundEffectMapping
{
  public:
	class Factory;
	[[nodiscard]] const auto& getLinks() const { return links; }

  private:
	std::vector<SoundEffectsMapperLink> links;
};

} // namespace HoI4



#endif // SOUND_EFFECT_MAPPING_H