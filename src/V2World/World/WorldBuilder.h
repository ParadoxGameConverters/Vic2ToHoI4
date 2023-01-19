#ifndef WORLD_H
#define WORLD_H



#include "src/V2World/World/World.h"
#include <memory>



namespace Vic2
{

class World::Builder
{
  public:
	Builder() { world = std::make_unique<World>(); }

	std::unique_ptr<World> Build() { return std::move(world); }

	Builder& addCountry(const std::string& tag, Country country)
	{
		world->countries.emplace(tag, std::move(country));
		return *this;
	}

	Builder& AddUnion(const std::string& tag, Country country)
	{
		world->union_countries_.emplace(tag, std::move(country));
		return *this;
	}

  private:
	std::unique_ptr<World> world;
};

} // namespace Vic2



#endif // WORLD_H