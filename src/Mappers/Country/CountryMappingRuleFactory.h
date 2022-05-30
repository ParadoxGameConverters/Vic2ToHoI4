#ifndef COUNTRY_MAPPING_RULE_FACTORY_H
#define COUNTRY_MAPPING_RULE_FACTORY_H



#include "ConvenientParser.h"
#include <string>



namespace Mappers
{

class CountryMappingRuleFactory: commonItems::convenientParser
{
  public:
	CountryMappingRuleFactory();

	std::pair<std::string, std::string> importMapping(std::istream& theStream);

  private:
	std::string vic2;
	std::string hoi4;
};

} // namespace Mappers



#endif // COUNTRY_MAPPING_RULE_FACTORY_H