#ifndef STATE_DEFINITIONS_BUILDER_H
#define STATE_DEFINITIONS_BUILDER_H



#include "StateDefinitions.h"
#include <memory>



namespace Vic2
{

class StateDefinitions::Builder
{
  public:
	Builder() { stateDefinitions = std::make_unique<StateDefinitions>(); }
	std::unique_ptr<StateDefinitions> build() { return std::move(stateDefinitions); }

	Builder& setStateMap(std::map<int, std::set<int>> stateMap)
	{
		stateDefinitions->stateMap = std::move(stateMap);
		return *this;
	}

	Builder& setProvinceToIDMap(std::map<int, std::string> provinceToIDMap)
	{
		stateDefinitions->provinceToIDMap = std::move(provinceToIDMap);
		return *this;
	}
	Builder& setStateToCapitalMap(std::map<std::string, int> stateToCapitalMap)
	{
		stateDefinitions->stateToCapitalMap = std::move(stateToCapitalMap);
		return *this;
	}

  private:
	std::unique_ptr<StateDefinitions> stateDefinitions;
};

} // namespace Vic2



#endif // STATE_DEFINITIONS_BUILDER_H