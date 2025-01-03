#include "src/Mappers/Buildings/LandmarksMappingFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Mappers::LandmarksMappingFactory::LandmarksMappingFactory()
{
	registerKeyword("location", [this](std::istream& theStream) {
		landmarksMapping.location = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("built", [this](std::istream& theStream) {
		landmarksMapping.built = commonItems::singleString{theStream}.getString() == "yes";
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


Mappers::LandmarksMapping Mappers::LandmarksMappingFactory::importMapping(std::istream& theStream)
{
	parseStream(theStream);
	clearRegisteredKeywords();
	return {.location = landmarksMapping.location, .built = landmarksMapping.built};
}