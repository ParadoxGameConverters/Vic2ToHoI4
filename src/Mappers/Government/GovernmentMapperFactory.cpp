#include "GovernmentMapperFactory.h"
#include "CommonRegexes.h"
#include "GovernmentMappingFactory.h"
#include "Log.h"
#include "ParserHelpers.h"



Mappers::GovernmentMapper::Factory::Factory()
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		governmentMapper->governmentMap.push_back(*governmentMappingFactory.importMapping(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::GovernmentMapper> Mappers::GovernmentMapper::Factory::importGovernmentMapper()
{
	Log(LogLevel::Info) << "\tParsing governments mappings";

	governmentMapper = std::make_unique<GovernmentMapper>();
	parseFile("Configurables/GovernmentMappings.txt");
	return std::move(governmentMapper);
}