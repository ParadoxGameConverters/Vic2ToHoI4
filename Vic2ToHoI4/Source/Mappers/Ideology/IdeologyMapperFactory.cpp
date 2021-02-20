#include "IdeologyMapperFactory.h"
#include "CommonRegexes.h"
#include "IdeologyMappingFactory.h"
#include "ParserHelpers.h"



Mappers::IdeologyMapper::Factory::Factory()
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		ideologyMapper->ideologyMap.push_back(*ideologyMappingFactory.importIdeologyMapping(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::IdeologyMapper> Mappers::IdeologyMapper::Factory::importIdeologyMapper()
{
	ideologyMapper = std::make_unique<IdeologyMapper>();
	parseFile("Configurables/IdeologyMappings.txt");
	return std::move(ideologyMapper);
}