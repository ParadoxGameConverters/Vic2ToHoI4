#include "OperativeNamesMappingsFactory.h"
#include "CommonRegexes.h"
#include "OperativeNamesMappingFactory.h"
#include "ParserHelpers.h"



HoI4::OperativeNamesMappings HoI4::OperativeNamesMappings::Factory::getMappings()
{
	OperativeNamesMappings operativeNamesMappings;
	OperativeNamesMappingFactory operativeNamesMappingFactory;

	registerKeyword("link", [this, &operativeNamesMappingFactory, &operativeNamesMappings](std::istream& theStream) {
		auto newMappings = operativeNamesMappingFactory.getMappings(theStream);
		operativeNamesMappings.cultureToNamesSetMap.merge(newMappings);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("DataFiles/OperativeNamesMappings.txt");
	return operativeNamesMappings;
}