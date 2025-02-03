#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"



Mappers::LandmarksMapper::LandmarksMapper()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		mappings[name] = Mappers::LandmarksMappingFactory().importMapping(theStream);
	});
	parseFile(std::filesystem::path("./Configurables/LandmarksMappings.txt"));
	clearRegisteredKeywords();
}

std::optional<int> Mappers::LandmarksMapper::getLocation(const std::string& landmark) const
{
	if (mappings.contains(landmark))
	{
		return mappings.at(landmark).location;
	}

	return std::nullopt;
}

bool Mappers::LandmarksMapper::getBuilt(const std::string& landmark) const
{
	if (mappings.contains(landmark))
	{
		return mappings.at(landmark).built;
	}

	return false;
}