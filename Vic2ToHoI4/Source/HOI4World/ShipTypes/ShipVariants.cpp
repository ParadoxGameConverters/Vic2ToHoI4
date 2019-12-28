#include "ShipVariants.h"



HoI4::shipVariants::shipVariants(
	const std::vector<shipVariant>& possibleVariants,
	const technologies& ownedTechs, const std::string& countryTag
)
{
	for (auto &possibleVariant: possibleVariants)
	{
		if (possibleVariant.isValidVariant(ownedTechs))
		{
			auto newVariant(possibleVariant);
			newVariant.setOwningCountryTag(countryTag);
			variants.insert(make_pair(newVariant.getName(), newVariant));
		}
	}
}