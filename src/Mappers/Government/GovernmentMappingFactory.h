#ifndef GOVERNMENT_MAPPING_FACTORY_H
#define GOVERNMENT_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "GovernmentMapping.h"
#include <memory>



namespace Mappers
{

class GovernmentMappingFactory: commonItems::convenientParser
{
  public:
	GovernmentMappingFactory();
	std::unique_ptr<GovernmentMapping> importMapping(std::istream& theStream);

  private:
	std::unique_ptr<GovernmentMapping> governmentMapping;
};

} // namespace Mappers



#endif // GOVERNMENT_MAPPING_FACTORY_H