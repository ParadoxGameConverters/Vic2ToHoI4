#ifndef STATE_CATEGORIES_BUILDER_H
#define STATE_CATEGORIES_BUILDER_H



#include "src/HOI4World/States/StateCategories.h"
#include <memory>



namespace HoI4
{

class StateCategories::Builder
{
  public:
	Builder() { stateCategories = std::make_unique<StateCategories>(); }
	std::unique_ptr<StateCategories> Build() { return std::move(stateCategories); }

	Builder& addCategory(int level, const std::string& name)
	{
		StateCategory category;
		category.setName(name);
		category.setNumberOfSlots(level);
		stateCategories->theCategories.push_back(category);
		return *this;
	}

	Builder& capBuilding(const std::string& building, int level)
	{
		StateCategory category;
		category.setBuildingsMaxLevel(building, level);
		stateCategories->theCategories.push_back(category);
		return *this;
	}

  private:
	std::unique_ptr<StateCategories> stateCategories;
};

} // namespace HoI4



#endif // STATE_CATEGORIES_BUILDER_H