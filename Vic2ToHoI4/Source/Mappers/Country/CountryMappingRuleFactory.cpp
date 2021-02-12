#include "CountryMappingRuleFactory.h"



Mappers::CountryMappingRuleFactory::CountryMappingRuleFactory()
{
	registerSetter("vic", vic2);
	registerSetter("hoi", hoi4);
}


std::pair<std::string, std::string> Mappers::CountryMappingRuleFactory::importMapping(std::istream& theStream)
{
	vic2.clear();
	hoi4.clear();
	parseStream(theStream);
	return std::make_pair(vic2, hoi4);
}