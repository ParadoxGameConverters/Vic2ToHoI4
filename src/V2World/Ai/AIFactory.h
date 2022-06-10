#ifndef VIC2_AI_FACTORY_H
#define VIC2_AI_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Ai/AI.h"
#include "src/V2World/Ai/AIStrategyFactory.h"
#include <memory>



namespace Vic2
{

class AI::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<AI> importAI(std::istream& theStream);

  private:
	std::unique_ptr<AI> ai;
	AIStrategy::Factory aiStrategyFactory;
};

} // namespace Vic2



#endif // VIC2_AI_FACTORY_H