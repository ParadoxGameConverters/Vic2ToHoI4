#ifndef VIC2_STATE_DEFINITIONS_FACTORY_H
#define VIC2_STATE_DEFINITIONS_FACTORY_H



#include "StateDefinitions.h"
#include "../../Configuration.h"



namespace Vic2
{

class StateDefinitions::Factory: commonItems::parser
{
  public:
	std::unique_ptr<StateDefinitions> getStateDefinitions(const Configuration& theConfiguration);
};

} // namespace Vic2



#endif // VIC2_STATE_DEFINITIONS_FACTORY_H