#ifndef WAR_FACTORY_H
#define WAR_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "War.h"
#include "WarGoalFactory.h"
#include <memory>



namespace Vic2
{

class War::Factory: commonItems::parser
{
  public:
	Factory();
	[[nodiscard]] War getWar(std::istream& theStream);

  private:
	WarOptions options;
	WarGoalFactory warGoalFactory;
};

} // namespace Vic2



#endif // WAR_FACTORY_H