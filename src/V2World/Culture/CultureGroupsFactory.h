#ifndef SRC_V2WORLD_CULTURE_CULTURE_GROUPS_FACTORY_H
#define SRC_V2WORLD_CULTURE_CULTURE_GROUPS_FACTORY_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/Parser.h"
#include "src/V2World/Culture/CultureGroupFactory.h"
#include "src/V2World/Culture/CultureGroups.h"
#include <memory>



namespace Vic2
{

class CultureGroups::Factory
{
  public:
	Factory();
	std::unique_ptr<CultureGroups> GetCultureGroups(const commonItems::ModFilesystem& mod_filesystem);

  private:
	commonItems::parser parser_;
	CultureGroupFactory culture_group_factory_;
	std::unique_ptr<CultureGroups> culture_groups_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_CULTURE_CULTURE_GROUPS_FACTORY_H