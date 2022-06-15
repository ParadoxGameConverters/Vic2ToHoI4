#ifndef SRC_V2WORLD_ISSUES_ISSUES_FACTORY_H
#define SRC_V2WORLD_ISSUES_ISSUES_FACTORY_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/Parser.h"
#include "src/V2World/Issues/Issues.h"
#include <memory>



namespace Vic2
{

class Issues::Factory
{
  public:
	Factory();
	std::unique_ptr<Issues> GetIssues(const commonItems::ModFilesystem& mod_filesystem);

  private:
	commonItems::parser parser_;

	std::unique_ptr<Issues> issues_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_ISSUES_ISSUES_FACTORY_H