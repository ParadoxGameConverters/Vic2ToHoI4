#ifndef SRC_V2WORLD_CULTURE_CULTURE_GROUP_FACTORY_H
#define SRC_V2WORLD_CULTURE_CULTURE_GROUP_FACTORY_H



#include "external/common_items/Parser.h"
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



#endif // SRC_V2WORLD_CULTURE_CULTURE_GROUP_FACTORY_H