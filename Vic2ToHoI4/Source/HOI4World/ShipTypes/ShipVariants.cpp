#include "ShipVariants.h"



HoI4::ShipVariants::ShipVariants(const PossibleShipVariants& possibleShipVariants,
	 const technologies& ownedTechs,
	 const std::string& countryTag)
{
	for (auto& possibleVariant: possibleShipVariants.getPossibleMtgVariants())
	{
		if (possibleVariant.isValidVariant(ownedTechs))
		{
			auto newVariant(possibleVariant);
			newVariant.setOwningCountryTag(countryTag);
			mtgVariants.insert(std::make_pair(newVariant.getName(), newVariant));
		}
	}
	for (auto& possibleVariant: possibleShipVariants.getPossibleLegacyVariants())
	{
		if (possibleVariant.isValidVariant(ownedTechs))
		{
			auto newVariant(possibleVariant);
			legacyVariants.insert(std::make_pair(newVariant.getName(), newVariant));
		}
	}
}