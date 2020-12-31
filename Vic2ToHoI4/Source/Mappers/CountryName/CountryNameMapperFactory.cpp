#include "CountryNameMapperFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



mappers::CountryNameMapper::Factory::Factory()
{
	registerKeyword("name_mapping", [this](std::istream& theStream) {
		countryNameMapper->mappings.push_back(*nameMappingFactory.importMapping(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<mappers::CountryNameMapper> mappers::CountryNameMapper::Factory::importCountryNameMapper()
{
	countryNameMapper = std::make_unique<CountryNameMapper>();
	parseFile("./Configurables/CountryNamesMappings.txt");
	return std::move(countryNameMapper);
}