#include "SoundEffectsMapper.h"



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
