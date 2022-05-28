#include "FlagsToIdeasMapper.h"



std::optional<std::string> Mappers::FlagsToIdeasMapper::getIdea(const std::string& flag) const
{
	const auto mapping = mappings.find(flag);
	if (mapping == mappings.end())
	{
		return std::nullopt;
	}

	return mapping->second;
}