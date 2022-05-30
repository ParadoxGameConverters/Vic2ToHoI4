#include "Traits.h"



Vic2::TraitEffects Vic2::Traits::getEffectsForTrait(const std::string& traitName) const
{
	const auto& trait = traits.find(traitName);
	if (trait == traits.end())
	{
		return {};
	}
	return trait->second;
}