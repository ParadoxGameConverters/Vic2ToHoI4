#include "src/Mappers/Ideology/IdeologyMapperFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "src/Mappers/Ideology/IdeologyMappingFactory.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"



Mappers::IdeologyMapper::Factory::Factory()
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		ideologyMapper->ideologyMap.push_back(*ideologyMappingFactory.importIdeologyMapping(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::IdeologyMapper> Mappers::IdeologyMapper::Factory::importIdeologyMapper()
{
	Log(LogLevel::Info) << "\tParsing ideology mappings";

	ideologyMapper = std::make_unique<IdeologyMapper>();
	parseFile("Configurables/IdeologyMappings.txt");
	return std::move(ideologyMapper);
}