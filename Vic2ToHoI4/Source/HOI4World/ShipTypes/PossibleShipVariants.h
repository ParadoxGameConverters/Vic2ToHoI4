#ifndef POSSIBLE_SHIP_VARIANTS_H
#define POSSIBLE_SHIP_VARIANTS_H



#include "LegacyShipVariant.h"
#include "MtgShipVariant.h"
#include "newParser.h"
#include <vector>



namespace HoI4
{

class possibleShipVariants: commonItems::parser
{
  public:
	explicit possibleShipVariants(std::istream& theStream);

	[[nodiscard]] auto getPossibleMtgVariants() const { return mtgVariants; }
	[[nodiscard]] auto getPossibleLegacyVariants() const { return legacyVariants; }

  private:
	std::vector<MtgShipVariant> mtgVariants;
	std::vector<LegacyShipVariant> legacyVariants;
};

} // namespace HoI4



#endif // POSSIBLE_SHIP_VARIANTS_H