#ifndef CULTURE_GROUP_FACTORY_H
#define CULTURE_GROUP_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include <string>
#include <vector>



namespace Vic2
{

class CultureGroupFactory: commonItems::parser
{
  public:
	CultureGroupFactory();

	[[nodiscard]] std::vector<std::string> getCultureGroup(std::istream& theStream);

  private:
	std::vector<std::string> cultureGroup;
};

} // namespace Vic2



#endif // CULTURE_GROUP_FACTORY_H