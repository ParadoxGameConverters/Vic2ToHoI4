#ifndef TRAITS_BUILDER_H
#define TRAITS_BUILDER_H



#include "src/V2World/Military/Leaders/Traits.h"
#include <memory>



namespace Vic2
{

class Traits::Builder
{
  public:
	Builder() { traits = std::make_unique<Traits>(); }
	std::unique_ptr<Traits> Build() { return std::move(traits); }

	Builder& addTrait(std::string traitName, TraitEffects traitEffects)
	{
		traits->traits.insert(std::make_pair(std::move(traitName), std::move(traitEffects)));
		return *this;
	}

  private:
	std::unique_ptr<Traits> traits;
};

} // namespace Vic2



#endif // TRAITS_BUILDER_H