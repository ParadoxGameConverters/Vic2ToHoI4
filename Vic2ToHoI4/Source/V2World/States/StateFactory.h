#ifndef VIC2_STATE_FACTORY_H
#define VIC2_STATE_FACTORY_H



#include "Parser.h"
#include "State.h"
#include "BuildingReader.h"
#include <memory>



namespace Vic2
{

class State::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<State> getState(std::istream& theStream,
		 const std::string& ownerTag,
		 const StateDefinitions& theStateDefinitions);
	std::unique_ptr<State> getUnownedState(const std::unordered_map<int, std::shared_ptr<Province>>& theProvinces,
		 const StateDefinitions& theStateDefinitions);

  private:
	void setID(const StateDefinitions& theStateDefinitions);
	void setCapital(const StateDefinitions& theStateDefinitions);
	void determineIfPartialState(const StateDefinitions& theStateDefinitions);

	std::unique_ptr<State> state;
	BuildingReader buildingReader;
};

} // namespace Vic2



#endif // VIC2_STATE_FACTORY_H