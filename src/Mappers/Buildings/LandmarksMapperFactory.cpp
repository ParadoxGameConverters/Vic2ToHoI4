#include "src/Mappers/Buildings/LandmarksMapperFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Mappers::LandmarksMapper::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		landmarksMapper->mappings.push_back(*landmarksMappingFactory.importMapping(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::LandmarksMapper> Mappers::LandmarksMapper::Factory::importLandmarksMapper()
{
	landmarksMapper = std::make_unique<LandmarksMapper>();
	parseFile("./Configurables/LandmarksMappings.txt");
	return std::move(landmarksMapper);
}