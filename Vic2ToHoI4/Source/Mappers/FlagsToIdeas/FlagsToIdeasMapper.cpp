#include "FlagsToIdeasMapper.h"
#include "FlagToIdeaMapping.h"
#include "FlagToIdeaMappingFactory.h"



mappers::FlagsToIdeasMapper::FlagsToIdeasMapper(std::istream& theStream)
{
	Mappers::FlagToIdeaMapping::Factory factory;
	registerKeyword("mapping", [this, &factory](std::istream& theStream) {
		auto theMapping = factory.importFlagToIdeaMapping(theStream);
		mappings.insert(std::make_pair(theMapping->getFlag(), theMapping->getIdea()));
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