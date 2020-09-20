#ifndef CULTURE_GROUPS_FACTORY_H
#define CULTURE_GROUPS_FACTORY_H



#include "CultureGroups.h"
#include "../../Configuration.h"
#include "Parser.h"
#include <memory>



namespace Vic2
{

class CultureGroups::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CultureGroups> getCultureGroups(const Configuration& theConfiguration);

  private:
	std::unique_ptr<CultureGroups> cultureGroups;
};

} // namespace Vic2



#endif // CULTURE_GROUPS_FACTORY_H