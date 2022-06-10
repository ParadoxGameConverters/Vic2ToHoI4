#ifndef FACTION_NAME_MAPPER_FACTORY_H
#define FACTION_NAME_MAPPER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/FactionName/FactionNameMapper.h"
#include "src/Mappers/FactionName/FactionNameMappingFactory.h"
#include <memory>



namespace Mappers
{

class FactionNameMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<FactionNameMapper> importFactionNameMapper();

  private:
	FactionNameMappingFactory nameMappingFactory;
	std::unique_ptr<FactionNameMapper> factionNameMapper;
};

} // namespace Mappers



#endif // FACTION_NAME_MAPPER_FACTORY_H