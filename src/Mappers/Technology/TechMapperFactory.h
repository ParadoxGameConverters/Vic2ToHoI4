#ifndef TECH_MAPPER_FACTORY_H
#define TECH_MAPPER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Technology/TechMapper.h"
#include "src/Mappers/Technology/TechMappingFactory.h"
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