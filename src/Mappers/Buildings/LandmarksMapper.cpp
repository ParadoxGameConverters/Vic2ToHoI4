#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"



Mappers::LandmarksMapper::LandmarksMapper()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		mappings[name] = Mappers::LandmarksMappingFactory().importMapping(theStream);
	});
	parseFile("./Configurables/LandmarksMappings.txt");
	clearRegisteredKeywords();
}

std::set<int> Mappers::LandmarksMapper::getLocations(const std::string& landmark) const
{
	if (mappings.contains(landmark))
	{
		return mappings.at(landmark).locations;
	}

	return {};
}

bool Mappers::LandmarksMapper::getBuilt(const std::string& landmark) const
{
	if (mappings.contains(landmark))
	{
		return mappings.at(landmark).built;
	}

	return false;
}