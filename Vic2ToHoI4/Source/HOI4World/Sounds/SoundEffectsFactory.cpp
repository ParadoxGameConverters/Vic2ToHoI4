#include "SoundEffectsFactory.h"
#include "../../V2World/Country.h"



std::vector<HoI4::SoundEffect> HoI4::SoundEffectsFactory::createSoundEffects(
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	std::vector<HoI4::SoundEffect> soundEffects;

	for (const auto& [tag, country]: countries)
	{
		for (const auto& mapping: soundEffectsMapper.getMappings(country->getSourceCountry().getPrimaryCulture()))
		{
			soundEffects.push_back(SoundEffect{tag + mapping.getName(), mapping.getSounds()});
		}
	}

	return soundEffects;
}