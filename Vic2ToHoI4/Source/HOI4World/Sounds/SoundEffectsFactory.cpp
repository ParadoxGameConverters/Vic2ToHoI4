#include "SoundEffectsFactory.h"
#include "V2World/Country.h"
#include "SoundEffectsMapperFactory.h"



HoI4::SoundEffectsFactory::SoundEffectsFactory()
{
	soundEffectsMapper = SoundEffectsMapper::Factory{}.getMapper();
}


std::vector<HoI4::SoundEffect> HoI4::SoundEffectsFactory::createSoundEffects(
	 const std::map<std::string, std::shared_ptr<Country>>& countries) const
{
	std::vector<SoundEffect> soundEffects;

	for (const auto& [tag, country]: countries)
	{
		for (const auto& mapping: soundEffectsMapper->getMappings(country->getSourceCountry().getPrimaryCulture()))
		{
			soundEffects.emplace_back(SoundEffect{tag + '_' + mapping.getName(), mapping.getSounds()});
		}
	}

	return soundEffects;
}