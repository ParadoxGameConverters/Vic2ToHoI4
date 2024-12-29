#include "src/Mappers/Buildings/LandmarksMapper.h"

std::optional<int> Mappers::LandmarksMapper::getLocation(const std::string& landmark) const
{
	for (const auto& mapping: mappings)
	{
		if (mapping.building == landmark)
		{
			return mapping.location;
		}
	}

	return std::nullopt;
}

bool Mappers::LandmarksMapper::getBuilt(const std::string& landmark) const
{
	for (const auto& mapping: mappings)
	{
		if (mapping.building == landmark)
		{
			return mapping.built;
		}
	}

	return false;
}