#ifndef SHIP_VARIANTS_H
#define SHIP_VARIANTS_H



#include "HOI4World/Technologies.h"
#include "LegacyShipVariant.h"
#include "MtgShipVariant.h"
#include "Parser.h"
#include "PossibleShipVariants.h"
#include <string>



namespace HoI4
{

class ShipVariants
{
  public:
	ShipVariants(const PossibleShipVariants& possibleShipVariants,
		 const technologies& ownedTechs,
		 const std::string& countryTag);

	[[nodiscard]] bool hasMtgVariant(const std::string& variantName) const { return mtgVariants.contains(variantName); }

	[[nodiscard]] bool hasLegacyVariant(const std::string& variantName) const
	{
		return legacyVariants.contains(variantName);
	}

	friend std::ostream& operator<<(std::ostream& output, const ShipVariants& theVariants);

  private:
	std::map<std::string, MtgShipVariant> mtgVariants;
	std::map<std::string, LegacyShipVariant> legacyVariants;
};

} // namespace HoI4



#endif // SHIP_VARIANTS_H