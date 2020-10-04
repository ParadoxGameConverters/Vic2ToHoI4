#ifndef NAVIES_H
#define NAVIES_H



#include "HOI4World/MilitaryMappings/MtgUnitMappings.h"
#include "HOI4World/MilitaryMappings/UnitMappings.h"
#include "HOI4World/ShipTypes/ShipVariants.h"
#include "HOI4World/States/HoI4State.h"
#include "LegacyNavy.h"
#include "MtgNavy.h"
#include "V2World/Military/Army.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class ProvinceDefinitions;


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
		 const ProvinceDefinitions& provinceDefinitions,
		 const mappers::ProvinceMapper& provinceMapper);

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
		 const mappers::ProvinceMapper& provinceMapper,
		 const ProvinceDefinitions& provinceDefinitions,
		 const std::map<int, int>& provinceToStateIDMap,
		 std::map<int, State> states);

	std::vector<LegacyNavy> legacyNavies;
	std::vector<MtgNavy> mtgNavies;
};

} // namespace HoI4



#endif // NAVIES_H