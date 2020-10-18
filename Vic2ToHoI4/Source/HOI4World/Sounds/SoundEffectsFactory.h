#ifndef SOUND_EFFECTS_FACTORY_H
#define SOUND_EFFECTS_FACTORY_H



#include "HOI4World/HoI4Country.h"
#include "SoundEffect.h"
#include "SoundEffectsMapper.h"
#include <map>
#include <memory>
#include <vector>



namespace HoI4
{

class SoundEffectsFactory
{
  public:
	SoundEffectsFactory();

	[[nodiscard]] std::vector<SoundEffect> createSoundEffects(
		 const std::map<std::string, std::shared_ptr<Country>>& countries) const;

  private:
	std::unique_ptr<SoundEffectsMapper> soundEffectsMapper;
};

} // namespace HoI4



#endif // SOUND_EFFECTS_FACTORY_H