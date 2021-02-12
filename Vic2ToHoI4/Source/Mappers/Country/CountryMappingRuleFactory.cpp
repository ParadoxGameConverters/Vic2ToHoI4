#include "CountryMappingRuleFactory.h"
#include "ParserHelpers.h"



Mappers::CountryMappingRuleFactory::CountryMappingRuleFactory()
{
	registerSetter("vic", vic2);
	registerKeyword("hoi", [this](std::istream& theStream) {
		hoi4.push_back(commonItems::singleString(theStream).getString());
	});
}


std::pair<std::string, std::vector<std::string>> Mappers::CountryMappingRuleFactory::importMapping(
	 std::istream& theStream)
{
	vic2.clear();
	hoi4.clear();
	parseStream(theStream);
	return std::make_pair(vic2, hoi4);
}