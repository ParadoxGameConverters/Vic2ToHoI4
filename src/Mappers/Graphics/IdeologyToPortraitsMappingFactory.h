#ifndef IDEOLOGY_TO_PORTRAITS_MAPPING_FACTORY_H
#define IDEOLOGY_TO_PORTRAITS_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>
#include <vector>



namespace Mappers
{

class IdeologyToPortraitsMappingFactory: commonItems::parser
{
  public:
	IdeologyToPortraitsMappingFactory();

	std::map<std::string, std::vector<std::string>> importMapping(std::istream& theStream);

  private:
	std::map<std::string, std::vector<std::string>> theMap;
};

} // namespace Mappers



#endif // IDEOLOGY_TO_PORTRAITS_MAPPING_FACTORY_H