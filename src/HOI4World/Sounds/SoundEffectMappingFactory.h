#ifndef SOUND_EFFECT_MAPPING_FACTORY_H
#define SOUND_EFFECT_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "SoundEffectMapping.h"
#include "SoundEffectsMapperLinkFactory.h"
#include <memory>



namespace HoI4
{

class SoundEffectMapping::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<SoundEffectMapping> getSoundEffectMapping(std::istream& theStream);

  private:
	std::unique_ptr<SoundEffectMapping> soundEffectMapping;
	SoundEffectsMapperLink::Factory soundEffectsMapperLinkFactory;
};

} // namespace HoI4



#endif // SOUND_EFFECT_MAPPING_FACTORY_H