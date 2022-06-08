#ifndef COUNTRY_NAME_MAPPING_FACTORY_H
#define COUNTRY_NAME_MAPPING_FACTORY_H



#include "src/Mappers/CountryName/CountryNameMapping.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>


namespace Mappers
{

class CountryNameMappingFactory: commonItems::parser
{
  public:
	CountryNameMappingFactory();
	std::unique_ptr<CountryNameMapping> importMapping(std::istream& theStream);

  private:
	std::unique_ptr<CountryNameMapping> countryNameMapping;
};

} // namespace Mappers



#endif // COUNTRY_NAME_MAPPING_FACTORY_H