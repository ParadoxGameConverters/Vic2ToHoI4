#include "SoundEffectsMapper.h"


HoI4::SoundEffectsMapper::SoundEffectsMapper()
{
	mappings.insert(std::make_pair("north_german",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
	mappings.insert(std::make_pair("south_german",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
	mappings.insert(std::make_pair("german",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
	mappings.insert(std::make_pair("swiss",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
	mappings.insert(std::make_pair("amerikaner",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
	mappings.insert(std::make_pair("sudreicher",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
	mappings.insert(std::make_pair("schwarzreicher",
		 std::set<SoundEffectsMapping>{SoundEffectsMapping{"_infantry_idle", {"de_Idle_001", "de_Idle_002"}}}));
}



std::set<HoI4::SoundEffectsMapping> HoI4::SoundEffectsMapper::getMappings(const std::string& culture)
{
	if (const auto& mapping = mappings.find(culture); mapping != mappings.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}
