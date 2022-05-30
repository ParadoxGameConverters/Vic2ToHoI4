#ifndef ARMY_BUILDER_H
#define ARMY_BUILDER_H



#include "Army.h"
#include <memory>



namespace Vic2
{

class Army::Builder
{
  public:
	Builder() { army = std::make_unique<Army>(); }
	std::unique_ptr<Army> Build() { return std::move(army); }

	Builder& setName(std::string name)
	{
		army->name = std::move(name);
		return *this;
	}

	Builder& setOwner(std::string owner)
	{
		army->owner = std::move(owner);
		return *this;
	}

	Builder& setLocation(std::optional<int> location)
	{
		army->location = location;
		return *this;
	}

  private:
	std::unique_ptr<Army> army;
};

} // namespace Vic2



#endif // ARMY_BUILDER_H