#ifndef UNIT_NAMES_FACTORY_H
#define UNIT_NAMES_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>
#include <vector>



namespace Vic2
{


class UnitNamesFactory: commonItems::parser
{
  public:
	UnitNamesFactory();
	std::map<std::string, std::vector<std::string>> importUnitNames(std::istream& theStream);

  private:
	std::map<std::string, std::vector<std::string>> unitNames;
};


} // namespace Vic2



#endif // UNIT_NAMES_FACTORY_H