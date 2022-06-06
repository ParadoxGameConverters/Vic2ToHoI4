#ifndef IDEOLOGY_MAPPING_FACTORY_H
#define IDEOLOGY_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "IdeologyMapping.h"
#include <memory>



namespace Mappers
{

class IdeologyMappingFactory: commonItems::convenientParser
{
  public:
	IdeologyMappingFactory();
	std::unique_ptr<IdeologyMapping> importIdeologyMapping(std::istream& theStream);

  private:
	std::unique_ptr<IdeologyMapping> ideologyMapping;
};

} // namespace Mappers



#endif // IDEOLOGY_MAPPING_FACTORY_H