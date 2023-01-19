#ifndef SRC_V2WORLD_STATES_STATE_DEFINITIONS_FACTORY_H
#define SRC_V2WORLD_STATES_STATE_DEFINITIONS_FACTORY_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/Parser.h"
#include "src/V2World/States/StateDefinitions.h"



namespace Vic2
{

class StateDefinitions::Factory
{
  public:
	Factory();
	std::unique_ptr<StateDefinitions> getStateDefinitions(const commonItems::ModFilesystem& mod_filesystem);

  private:
	commonItems::parser parser_;
	std::unique_ptr<StateDefinitions> state_definitions_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_STATES_STATE_DEFINITIONS_FACTORY_H