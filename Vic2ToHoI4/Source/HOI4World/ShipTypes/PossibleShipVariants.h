#ifndef POSSIBLE_SHIP_VARIANTS_H
#define POSSIBLE_SHIP_VARIANTS_H



#include "MtgShipVariant.h"
#include "newParser.h"
#include <vector>



namespace HoI4
{

class possibleShipVariants: commonItems::parser
{
  public:
	explicit possibleShipVariants(std::istream& theStream);

	possibleShipVariants() = delete;
	~possibleShipVariants() = default;
	possibleShipVariants(const possibleShipVariants&) = default;
	possibleShipVariants(possibleShipVariants&&) = default;
	possibleShipVariants& operator=(const possibleShipVariants&) = default;
	possibleShipVariants& operator=(possibleShipVariants&&) = default;

	[[nodiscard]] auto getPossibleMtgVariants() const { return mtgVariants; }

  private:
	std::vector<MtgShipVariant> mtgVariants;
};

} // namespace HoI4



#endif // POSSIBLE_SHIP_VARIANTS_H