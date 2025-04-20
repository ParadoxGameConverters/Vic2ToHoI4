#include "src/Mappers/Technology/TechMapperFactory.h"



Mappers::TechMapper::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		techMapper->techMappings.push_back(*techMappingFactory.importTechMapping(theStream));
	});
}


std::unique_ptr<Mappers::TechMapper> Mappers::TechMapper::Factory::importTechMapper()
{
	techMapper = std::make_unique<TechMapper>();
	parseFile(std::filesystem::path("Configurables/tech_mappings.txt"));
	return std::move(techMapper);
}