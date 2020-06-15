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
	State::Factory();
	std::unique_ptr<State> getState(std::istream& theStream,
		 const std::string& ownerTag,
		 const Vic2::StateDefinitions& theStateDefinitions);
	std::unique_ptr<State> getState(std::set<std::pair<int, Province*>> theProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions);

  private:
	void setID(const StateDefinitions& theStateDefinitions);
	void setCapital(const StateDefinitions& theStateDefinitions);
	void determineIfPartialState(const Vic2::StateDefinitions& theStateDefinitions);

	std::unique_ptr<State> state;
};

} // namespace Vic2



#endif // VIC2_STATE_FACTORY_H