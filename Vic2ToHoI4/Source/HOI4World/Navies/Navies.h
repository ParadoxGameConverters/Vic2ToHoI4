#ifndef NAVIES_H
#define NAVIES_H



#include "../../V2World/Army.h"
#include "../MilitaryMappings/MtgUnitMappings.h"
#include "../MilitaryMappings/UnitMappings.h"
#include "../ShipTypes/ShipVariants.h"
#include "../States/HoI4State.h"
#include "LegacyNavy.h"
#include "MtgNavy.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class Navies
{
  public:
	Navies(const std::vector<Vic2::Army>& srcArmies,
		 int backupNavalLocation,
		 const UnitMappings& unitMap,
		 const MtgUnitMappings& mtgUnitMap,
		 const ShipVariants& theShipVariants,
		 const std::map<int, int>& provinceToStateIDMap,
		 std::map<int, State> states,
		 const std::string& tag);

	Navies() = delete;
	~Navies() = default;
	Navies(const Navies&) = default;
	Navies(Navies&&) = default;
	Navies& operator=(const Navies&) = default;
	Navies& operator=(Navies&&) = default;

	[[nodiscard]] const auto& getLegacyNavies() const { return legacyNavies; }
	[[nodiscard]] const auto& getMtgNavies() const { return mtgNavies; }

  private:
	std::vector<LegacyNavy> legacyNavies;
	std::vector<MtgNavy> mtgNavies;
};

} // namespace HoI4



#endif // NAVIES_H