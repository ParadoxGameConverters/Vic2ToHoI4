#include "src/Mappers/FlagsToIdeas/FlagToIdeaMappingFactory.h"
#include "external/common_items/ParserHelpers.h"



Mappers::FlagToIdeaMapping::Factory::Factory()
{
	registerKeyword("flag", [this](std::istream& theStream) {
		flagToIdeaMapping->flag = commonItems::singleString(theStream).getString();
	});
	registerKeyword("idea", [this](std::istream& theStream) {
		flagToIdeaMapping->idea = commonItems::singleString(theStream).getString();
	});
}


std::unique_ptr<Mappers::FlagToIdeaMapping> Mappers::FlagToIdeaMapping::Factory::importFlagToIdeaMapping(
	 std::istream& theStream)
{
	flagToIdeaMapping = std::make_unique<FlagToIdeaMapping>();
	parseStream(theStream);
	return std::move(flagToIdeaMapping);
}