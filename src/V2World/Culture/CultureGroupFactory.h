#ifndef SRC_V2WORLD_CULTURE_CULTURE_GROUP_FACTORY_H
#define SRC_V2WORLD_CULTURE_CULTURE_GROUP_FACTORY_H



#include "external/common_items/Parser.h"
#include "src/V2World/Culture/CultureGroup.h"
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class CultureGroupFactory: commonItems::parser
{
  public:
	CultureGroupFactory();

	[[nodiscard]] CultureGroup GetCultureGroup(std::istream& the_stream);

  private:
	std::vector<std::string> culture_group_;
	std::optional<std::string> union_tag_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_CULTURE_CULTURE_GROUP_FACTORY_H