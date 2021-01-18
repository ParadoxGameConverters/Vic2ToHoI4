#include "FlagsToIdeasMapperFactory.h"
#include "FlagToIdeaMapping.h"
#include "ParserHelpers.h"



Mappers::FlagsToIdeasMapper::Factory::Factory()
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		const auto theMapping = factory.importFlagToIdeaMapping(theStream);
		flagsToIdeaMapper->mappings.insert(std::make_pair(theMapping->getFlag(), theMapping->getIdea()));
	});
}


std::unique_ptr<Mappers::FlagsToIdeasMapper> Mappers::FlagsToIdeasMapper::Factory::getFlagsToIdeaMapper(
	 std::istream& theStream)
{
	flagsToIdeaMapper = std::make_unique<FlagsToIdeasMapper>();
	parseStream(theStream);
	return std::move(flagsToIdeaMapper);
}