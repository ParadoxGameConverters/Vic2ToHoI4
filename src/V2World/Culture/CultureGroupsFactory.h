#ifndef CULTURE_GROUPS_FACTORY_H
#define CULTURE_GROUPS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/V2World/Culture/CultureGroupFactory.h"
#include "src/V2World/Culture/CultureGroups.h"
#include <memory>



namespace Vic2
{

class CultureGroups::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CultureGroups> getCultureGroups(const Configuration& theConfiguration);

  private:
	CultureGroupFactory cultureGroupFactory;
	std::unique_ptr<CultureGroups> cultureGroups;
};

} // namespace Vic2



#endif // CULTURE_GROUPS_FACTORY_H