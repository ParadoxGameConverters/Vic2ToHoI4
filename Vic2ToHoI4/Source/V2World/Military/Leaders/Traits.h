#ifndef TRAITS_H
#define TRAITS_H



#include "Trait.h"
#include <string_view>



namespace Vic2
{

class Traits
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] TraitEffects getEffectsForTrait(const std::string& traitName) const;

  private:
	std::unordered_map<std::string, TraitEffects> traits;
};

} // namespace Vic2



#endif // TRAITS_H