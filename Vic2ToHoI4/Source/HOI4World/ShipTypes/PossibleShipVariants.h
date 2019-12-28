#ifndef POSSIBLE_SHIP_VARIANTS_H
#define POSSIBLE_SHIP_VARIANTS_H



#include "newParser.h"
#include "ShipVariant.h"
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

		[[nodiscard]] auto getPossibleVariants() const { return theVariants; }

	private:
		std::vector<shipVariant> theVariants;
};

}



#endif // POSSIBLE_SHIP_VARIANTS_H