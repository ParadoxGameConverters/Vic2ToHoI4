#include "SoundEffectsFactory.h"
#include "../../V2World/Country.h"



std::vector<HoI4::SoundEffect> HoI4::SoundEffectsFactory::createSoundEffects(
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	std::set<std::string>
		 germanCultures{"north_german", "south_german", "german", "swiss", "amerikaner", "sudreicher", "schwarzreicher"};
	std::vector<HoI4::SoundEffect> soundEffects;

	for (const auto& [tag, country]: countries)
	{
		if (germanCultures.count(country->getSourceCountry().getPrimaryCulture()))
		{
			soundEffects.push_back(SoundEffect{tag + "_infantry_idle", {"de_Idle_001", "de_Idle_002"}});
		}
	}

	return soundEffects;
}