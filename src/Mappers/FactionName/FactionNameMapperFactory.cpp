#include "FactionNameMapperFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"



Mappers::FactionNameMapper::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		factionNameMapper->mappings.push_back(*nameMappingFactory.importMapping(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::FactionNameMapper> Mappers::FactionNameMapper::Factory::importFactionNameMapper()
{
	factionNameMapper = std::make_unique<FactionNameMapper>();
	parseFile("./Configurables/factions_mappings.txt");
	Log(LogLevel::Info) << "\tLoaded " << factionNameMapper->mappings.size() << " Faction Name Mappings";
	return std::move(factionNameMapper);
}