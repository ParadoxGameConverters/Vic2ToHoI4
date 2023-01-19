#ifndef HOI4_STATE_BUILDER_H
#define HOI4_STATE_BUILDER_H



#include "src/HOI4World/States/HoI4State.h"
#include <memory>



namespace HoI4
{

class State::Builder
{
  public:
	Builder() { state = std::make_unique<State>(); }
	std::unique_ptr<State> Build() { return std::move(state); }

	Builder& setId(int id)
	{
		state->ID = id;
		return *this;
	}

	Builder& setOwner(const std::string& owner)
	{
		state->ownerTag = owner;
		return *this;
	}

	Builder& addCore(const std::string& core)
	{
		state->cores.insert(core);
		return *this;
	}

	Builder& setProvinces(const std::set<int>& provinces)
	{
		state->provinces = provinces;
		return *this;
	}

	Builder& makeImpassable()
	{
		state->impassable = true;
		return *this;
	}

  private:
	std::unique_ptr<State> state;
};

} // namespace HoI4



#endif // HOI4_STATE_BUILDER_H