#ifndef SHIP_VARIANTS_H
#define SHIP_VARIANTS_H



#include "newParser.h"
#include "../Technologies.h"
#include "ShipVariant.h"
#include <string>
#include <vector>



namespace HoI4
{

class shipVariants
{
	public:
		shipVariants(const std::vector<shipVariant>& possibleVariants, const technologies& ownedTechs, const std::string& countryTag);

		shipVariants() = delete;
		~shipVariants() = default;
		shipVariants(const shipVariants&) = default;
		shipVariants(shipVariants&&) = default;
		shipVariants& operator=(const shipVariants&) = default;
		shipVariants& operator=(shipVariants&&) = default;

		bool hasVariant(const std::string& variantName) const { return variants.find(variantName) != variants.end(); }

		friend std::ostream& operator << (std::ostream& output, const shipVariants& theVariants);

	private:
		std::map<std::string, shipVariant> variants;
};

}



#endif // SHIP_VARIANTS_H