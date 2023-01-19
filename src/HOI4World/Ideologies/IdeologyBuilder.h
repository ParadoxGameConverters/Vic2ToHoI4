#ifndef IDEOLOGY_BUILDER_H
#define IDEOLOGY_BUILDER_H



#include "src/HOI4World/Ideologies/Ideology.h"
#include <memory>



namespace HoI4
{

class Ideology::Builder
{
  public:
	Builder() { ideology = std::make_unique<Ideology>(); }
	std::unique_ptr<Ideology> Build() { return std::move(ideology); }

	Builder& addName(std::string name)
	{
		ideology->ideologyName = name;
		return *this;
	}

	Builder& addType(std::string type)
	{
		ideology->types.push_back(type);
		return *this;
	}

  private:
	std::unique_ptr<Ideology> ideology;
};

} // namespace HoI4



#endif // IDEOLOGY_BUILDER_H