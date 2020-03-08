#ifndef SHIP_VARIANTS_H
#define SHIP_VARIANTS_H



#include "../Technologies.h"
#include "MtgShipVariant.h"
#include "newParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class shipVariants
{
  public:
	shipVariants(const std::vector<MtgShipVariant>& possibleMtgVariants,
		 const technologies& ownedTechs,
		 const std::string& countryTag);

	[[nodiscard]] bool hasMtgVariant(const std::string& variantName) const
	{
		return mtgVariants.find(variantName) != mtgVariants.end();
	}

	friend std::ostream& operator<<(std::ostream& output, const shipVariants& theVariants);

  private:
	std::map<std::string, MtgShipVariant> mtgVariants;
};

} // namespace HoI4



#endif // SHIP_VARIANTS_H