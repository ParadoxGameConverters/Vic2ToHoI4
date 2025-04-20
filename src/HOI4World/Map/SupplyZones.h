#ifndef HOI4_SUPPLY_ZONES_H
#define HOI4_SUPPLY_ZONES_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/SupplyZone.h"
#include "src/HOI4World/States/DefaultState.h"
#include "src/HOI4World/States/HoI4States.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class SupplyZones: commonItems::parser
{
  public:
	explicit SupplyZones(const std::map<int, DefaultState>& defaultStates, const Configuration& theConfiguration);

	void convertSupplyZones(const States& states);

	[[nodiscard]] const auto& getSupplyZones() const { return supplyZones; }

	[[nodiscard]] std::optional<std::filesystem::path> getSupplyZoneFileName(int supplyZoneNum) const;

  private:
	void importStates(const std::map<int, DefaultState>& defaultStates);

	std::map<int, std::set<int>> defaultStateToProvinceMap;
	std::map<int, std::filesystem::path> supplyZonesFileNames;
	std::map<int, SupplyZone> supplyZones;
	std::map<int, int> provinceToSupplyZoneMap;
};

} // namespace HoI4



#endif // HOI4_SUPPLY_ZONES_H