#ifndef SOUND_EFFECTS_MAPPER_FACTORY_H
#define SOUND_EFFECTS_MAPPER_FACTORY_H



#include "Parser.h"
#include "SoundEffectMappingFactory.h"
#include "SoundEffectsMapper.h"
#include <memory>



namespace HoI4
{

class SoundEffectsMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<SoundEffectsMapper> getMapper();

  private:
	std::unique_ptr<SoundEffectsMapper> mapper;
	SoundEffectMapping::Factory soundEffectMappingFactory;
};

} // namespace HoI4



#endif // SOUND_EFFECTS_MAPPER_FACTORY_H