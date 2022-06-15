#ifndef SRC_V2WORLD_TECHNOLOGY_INVENTIONS_FACTORY_H
#define SRC_V2WORLD_TECHNOLOGY_INVENTIONS_FACTORY_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/Parser.h"
#include "src/V2World/Technology/Inventions.h"
#include <memory>



namespace Vic2
{

class Inventions::Factory
{
  public:
	Factory();
	std::unique_ptr<Inventions> LoadInventions(const commonItems::ModFilesystem& mod_filesystem);

  private:
	commonItems::parser parser_;

	std::unique_ptr<Inventions> inventions_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_TECHNOLOGY_INVENTIONS_FACTORY_H