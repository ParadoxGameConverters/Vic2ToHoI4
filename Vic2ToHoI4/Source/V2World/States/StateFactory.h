#ifndef VIC2_STATE_FACTORY_H
#define VIC2_STATE_FACTORY_H



#include "Parser.h"
#include "State.h"
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
	std::unique_ptr<State> getUnownedState(const std::set<std::pair<int, std::shared_ptr<Province>>>& theProvinces,
		 const StateDefinitions& theStateDefinitions);

  private:
	void setID(const StateDefinitions& theStateDefinitions) const;
	void setCapital(const StateDefinitions& theStateDefinitions) const;
	void determineIfPartialState(const StateDefinitions& theStateDefinitions) const;

	std::unique_ptr<State> state;
};

} // namespace Vic2



#endif // VIC2_STATE_FACTORY_H