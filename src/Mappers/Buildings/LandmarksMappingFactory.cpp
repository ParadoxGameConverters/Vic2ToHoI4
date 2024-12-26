#include "src/Mappers/Buildings/LandmarksMappingFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Mappers::LandmarksMappingFactory::LandmarksMappingFactory()
{
	registerKeyword("building", [this](std::istream& theStream) {
		landmarksMapping->building = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("location", [this](std::istream& theStream) {
		landmarksMapping->location = commonItems::singleInt{theStream}.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::LandmarksMapping> Mappers::LandmarksMappingFactory::importMapping(std::istream& theStream)
{
	landmarksMapping = std::make_unique<LandmarksMapping>();
	parseStream(theStream);
	return std::move(landmarksMapping);
}