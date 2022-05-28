#ifndef TECH_MAPPING_FACTORY_H
#define TECH_MAPPING_FACTORY_H



#include "Parser.h"
#include "TechMapping.h"
#include <memory>



namespace Mappers
{

class TechMapping::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<TechMapping> importTechMapping(std::istream& theStream);

  private:
	std::unique_ptr<TechMapping> techMapping;
};

} // namespace Mappers



#endif // TECH_MAPPING_FACTORY_H