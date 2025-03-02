#include "src/HOI4World/OperativeNames/OperativeNamesMappingsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/OperativeNames/OperativeNamesMappingFactory.h"



HoI4::OperativeNamesMappings HoI4::OperativeNamesMappings::Factory::getMappings()
{
	OperativeNamesMappings operativeNamesMappings;
	OperativeNamesMappingFactory operativeNamesMappingFactory;

	registerKeyword("link", [this, &operativeNamesMappingFactory, &operativeNamesMappings](std::istream& theStream) {
		auto newMappings = operativeNamesMappingFactory.getMappings(theStream);
		operativeNamesMappings.cultureToNamesSetMap.merge(newMappings);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(std::filesystem::path("Configurables/OperativeNamesMappings.txt"));
	return operativeNamesMappings;
}