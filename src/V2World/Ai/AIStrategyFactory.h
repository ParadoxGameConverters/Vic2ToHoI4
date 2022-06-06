#ifndef AI_STRATEGY_FACTORY_H
#define AI_STRATEGY_FACTORY_H



#include "AIStrategy.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace Vic2
{

class AIStrategy::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<AIStrategy> importStrategy(const std::string& strategyType, std::istream& theStream);

  private:
	std::unique_ptr<AIStrategy> aiStrategy;
};

} // namespace Vic2



#endif // AI_STRATEGY_FACTORY_H