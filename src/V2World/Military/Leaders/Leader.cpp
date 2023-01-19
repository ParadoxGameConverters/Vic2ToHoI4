#include "src/V2World/Military/Leaders/Leader.h"



float Vic2::Leader::getTraitEffectValue(const std::string& trait) const
{
	const auto effect = traitEffects.find(trait);
	if (effect == traitEffects.end())
	{
		return 0.0F;
	}

	return effect->second;
}