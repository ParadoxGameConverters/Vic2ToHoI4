#ifndef COUNTRY_NAME_MAPPING_FACTORY_H
#define COUNTRY_NAME_MAPPING_FACTORY_H



#include "CountryNameMapping.h"
#include "Parser.h"
#include <memory>


namespace mappers
{

class CountryNameMappingFactory: commonItems::parser
{
  public:
	CountryNameMappingFactory();
	std::unique_ptr<CountryNameMapping> importMapping(std::istream& theStream);

  private:
	std::unique_ptr<CountryNameMapping> countryNameMapping;
};

} // namespace mappers



#endif // COUNTRY_NAME_MAPPING_FACTORY_H