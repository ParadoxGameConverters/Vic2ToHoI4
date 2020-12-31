#include "FlagsToIdeasMapper.h"
#include "FlagToIdeaMapping.h"



mappers::FlagsToIdeasMapper::FlagsToIdeasMapper(std::istream& theStream)
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		FlagToIdeaMapping theMapping(theStream);
		mappings.insert(std::make_pair(theMapping.getFlag(), theMapping.getIdea()));
	});

	parseStream(theStream);
}


std::optional<std::string> mappers::FlagsToIdeasMapper::getIdea(const std::string& flag) const
{
	auto mapping = mappings.find(flag);
	if (mapping == mappings.end())
	{
		return {};
	}
	else
	{
		return mapping->second;
	}
}