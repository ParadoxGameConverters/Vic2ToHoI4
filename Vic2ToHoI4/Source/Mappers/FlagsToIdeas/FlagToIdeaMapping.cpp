#include "FlagToIdeaMapping.h"
#include "ParserHelpers.h"



mappers::FlagToIdeaMapping::FlagToIdeaMapping(std::istream& theStream)
{
	registerKeyword("flag", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString theFlag(theStream);
		flag = theFlag.getString();
	});
	registerKeyword("idea", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString theIdea(theStream);
		idea = theIdea.getString();
	});

	parseStream(theStream);
}