#ifndef SOUND_EFFECTS_MAPPER_LINK_FACTORY_H
#define SOUND_EFFECTS_MAPPER_LINK_FACTORY_H



#include "Parser.h"
#include "SoundEffectsMapperLink.h"
#include <memory>



namespace HoI4
{

class SoundEffectsMapperLink::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<SoundEffectsMapperLink> getSoundEffectMapperLink(std::istream& theStream);

  private:
	std::unique_ptr<SoundEffectsMapperLink> soundEffectMapperLink;
};

} // namespace HoI4



#endif // SOUND_EFFECTS_MAPPER_LINK_FACTORY_H