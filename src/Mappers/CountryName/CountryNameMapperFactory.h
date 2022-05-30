#ifndef COUNTRY_NAME_MAPPER_FACTORY_H
#define COUNTRY_NAME_MAPPER_FACTORY_H



#include "CountryNameMapper.h"
#include "CountryNameMappingFactory.h"
#include "Parser.h"
#include <memory>



namespace Mappers
{

class CountryNameMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CountryNameMapper> importCountryNameMapper();

  private:
	CountryNameMappingFactory nameMappingFactory;
	std::unique_ptr<CountryNameMapper> countryNameMapper;
};

} // namespace Mappers



#endif // COUNTRY_NAME_MAPPER_FACTORY_H