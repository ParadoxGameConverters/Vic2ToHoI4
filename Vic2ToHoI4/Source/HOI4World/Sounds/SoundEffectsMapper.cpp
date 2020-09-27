#include "SoundEffectsMapper.h"



std::set<HoI4::SoundEffectsMapping> HoI4::SoundEffectsMapper::getMappings(const std::string& culture)
{
	std::set<std::string>
		 germanCultures{"north_german", "south_german", "german", "swiss", "amerikaner", "sudreicher", "schwarzreicher"};

	if (germanCultures.count(culture))
	{
		return {SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}};
	}
	else
	{
		return {};
	}
}
