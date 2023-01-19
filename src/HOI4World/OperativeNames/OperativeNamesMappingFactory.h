#ifndef OPERATIVE_NAMES_MAPPING_FACTORY_H
#define OPERATIVE_NAMES_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>



namespace HoI4
{

using RawOperativeNamesMappings = std::map<std::string, std::string>;


class OperativeNamesMappingFactory: commonItems::parser
{
  public:
	OperativeNamesMappingFactory();
	RawOperativeNamesMappings getMappings(std::istream& theStream);

  private:
	std::string codenames;
	std::vector<std::string> cultures;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_MAPPING_FACTORY_H