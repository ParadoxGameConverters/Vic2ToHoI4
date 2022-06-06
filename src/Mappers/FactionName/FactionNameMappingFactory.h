#ifndef FACTION_NAME_MAPPING_FACTORY_H
#define FACTION_NAME_MAPPING_FACTORY_H



#include "FactionNameMapping.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>


namespace Mappers
{

class FactionNameMappingFactory: commonItems::parser
{
  public:
	FactionNameMappingFactory();
	std::unique_ptr<FactionNameMapping> importMapping(std::istream& theStream);

  private:
	std::unique_ptr<FactionNameMapping> factionNameMapping;
};

} // namespace Mappers



#endif // FACTION_NAME_MAPPING_FACTORY_H