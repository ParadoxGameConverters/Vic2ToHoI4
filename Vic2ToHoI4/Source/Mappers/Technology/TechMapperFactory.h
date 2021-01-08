#ifndef TECH_MAPPER_FACTORY_H
#define TECH_MAPPER_FACTORY_H



#include "Parser.h"
#include "TechMapper.h"
#include "TechMappingFactory.h"
#include <memory>



namespace Mappers
{

class TechMapper::Factory: commonItems::parser
{
  public:
	Factory();

	std::unique_ptr<TechMapper> importTechMapper();

  private:
	TechMapping::Factory techMappingFactory;

	std::unique_ptr<TechMapper> techMapper;
};

} // namespace Mappers



#endif // TECH_MAPPER_FACTORY_H