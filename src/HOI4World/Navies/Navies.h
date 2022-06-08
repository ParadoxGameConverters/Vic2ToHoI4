#ifndef NAVIES_H
#define NAVIES_H



#include "src/HOI4World/MilitaryMappings/MtgUnitMappings.h"
#include "src/HOI4World/MilitaryMappings/UnitMappings.h"
#include "src/HOI4World/ShipTypes/ShipVariants.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/Navies/LegacyNavy.h"
#include "src/Maps/ProvinceDefinitions.h"
#include "src/HOI4World/Navies/MtgNavy.h"
#include "src/V2World/Military/Army.h"
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
		 const std::string& tag,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper);

	Navies() = delete;
	~Navies() = default;
	Navies(const Navies&) = default;
	Navies(Navies&&) = default;
	Navies& operator=(const Navies&) = default;
	Navies& operator=(Navies&&) = default;

	[[nodiscard]] const auto& getLegacyNavies() const { return legacyNavies; }
	[[nodiscard]] const auto& getMtgNavies() const { return mtgNavies; }

  private:
	std::tuple<int, int> getLocationAndBase(std::optional<int> vic2Location,
		 int backupNavalLocation,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 const std::map<int, int>& provinceToStateIDMap,
		 std::map<int, State> states);

	std::vector<LegacyNavy> legacyNavies;
	std::vector<MtgNavy> mtgNavies;
};

} // namespace HoI4



#endif // NAVIES_H