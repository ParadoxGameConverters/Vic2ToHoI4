#ifndef VIC2_STATE_DEFINITIONS_FACTORY_H
#define VIC2_STATE_DEFINITIONS_FACTORY_H



#include "src/Configuration.h"
#include "src/V2World/States/StateDefinitions.h"



namespace Vic2
{

class StateDefinitions::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<StateDefinitions> getStateDefinitions(const Configuration& theConfiguration);

  private:
	std::unique_ptr<StateDefinitions> stateDefinitions;
};

} // namespace Vic2



#endif // VIC2_STATE_DEFINITIONS_FACTORY_H