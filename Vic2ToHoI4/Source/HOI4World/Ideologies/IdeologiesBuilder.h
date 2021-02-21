#ifndef IDEOLOGIES_BUILDER_H
#define IDEOLOGIES_BUILDER_H



#include "Ideologies.h"
#include <memory>



namespace HoI4
{

class Ideologies::Builder
{
  public:
	Builder() { ideologies = std::make_unique<Ideologies>(); }
	std::unique_ptr<Ideologies> Build() { return std::move(ideologies); }

	Builder& addIdeology(Ideology ideology)
	{
		ideologies->ideologies.emplace(ideology.getName(), ideology);
		return *this;
	}

  private:
	std::unique_ptr<Ideologies> ideologies;
};

} // namespace HoI4



#endif // IDEOLOGIES_BUILDER_H