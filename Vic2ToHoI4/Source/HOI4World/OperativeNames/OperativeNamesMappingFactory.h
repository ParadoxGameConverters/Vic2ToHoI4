#ifndef OPERATIVE_NAMES_MAPPING_FACTORY_H
#define OPERATIVE_NAMES_MAPPING_FACTORY_H



#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

using OperativeNamesMappings = std::map<std::string, std::string>;


class OperativeNamesMappingFactory: commonItems::parser
{
  public:
	OperativeNamesMappingFactory();
	OperativeNamesMappings getMappings(std::istream& theStream);

  private:
	std::string codenames;
	std::vector<std::string> cultures;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_MAPPING_FACTORY_H