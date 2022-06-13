#ifndef SRC_V2WORLD_MILITARY_LEADERS_TRAITS_FACTORY_H
#define SRC_V2WORLD_MILITARY_LEADERS_TRAITS_FACTORY_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/Parser.h"
#include "src/V2World/Military/Leaders/Traits.h"
#include <memory>



namespace Vic2
{

class Traits::Factory
{
  public:
	Factory();
	std::unique_ptr<Traits> LoadTraits(const commonItems::ModFilesystem& mod_filesystem);

  private:
	commonItems::parser parser_;
	std::unique_ptr<Traits> traits_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_MILITARY_LEADERS_TRAITS_FACTORY_H