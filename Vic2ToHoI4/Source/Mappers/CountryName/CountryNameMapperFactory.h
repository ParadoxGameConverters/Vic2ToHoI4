#ifndef COUNTRY_NAME_MAPPER_FACTORY_H
#define COUNTRY_NAME_MAPPER_FACTORY_H



#include "CountryNameMapper.h"
#include "Parser.h"
#include <memory>
#include "CountryNameMappingFactory.h"



namespace mappers
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

} // namespace mappers



#endif // COUNTRY_NAME_MAPPER_FACTORY_H