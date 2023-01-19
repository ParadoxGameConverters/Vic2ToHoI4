#ifndef STATE_BUILDER_H
#define STATE_BUILDER_H



#include "src/V2World/States/State.h"
#include <memory>



namespace Vic2
{

class State::Builder
{
  public:
	Builder() { state = std::make_unique<State>(); }
	std::unique_ptr<State> build() { return std::move(state); }

	Builder& setOwner(std::string owner)
	{
		state->owner = std::move(owner);
		return *this;
	}

	Builder& setStateID(std::string stateID)
	{
		state->stateID = std::move(stateID);
		return *this;
	}

	Builder& setPartialState(bool partialState)
	{
		state->partialState = partialState;
		return *this;
	}

	Builder& setProvinceNumbers(std::set<int> provinceNumbers)
	{
		state->provinceNumbers = std::move(provinceNumbers);
		return *this;
	}

	Builder& setProvinces(std::vector<std::shared_ptr<Province>> provinces)
	{
		state->provinces = std::move(provinces);
		return *this;
	}

	Builder& setCapitalProvince(std::optional<int> capitalProvince)
	{
		state->capitalProvince = capitalProvince;
		return *this;
	}

	Builder& setFactoryLevel(int factoryLevel)
	{
		state->factoryLevel = factoryLevel;
		return *this;
	}

	Builder& setEmployedWorkers(int employedWorkers)
	{
		state->employedWorkers = employedWorkers;
		return *this;
	}

  private:
	std::unique_ptr<State> state;
};

} // namespace Vic2



#endif // STATE_BUILDER_H