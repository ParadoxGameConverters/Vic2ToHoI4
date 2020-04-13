#ifndef HOI4_SUPPLY_ZONES_H
#define HOI4_SUPPLY_ZONES_H



#include "newParser.h"
#include <map>
#include <set>
#include <string>



class Configuration;



namespace HoI4
{

class DefaultState;
class States;
class SupplyZone;



class SupplyZones: commonItems::parser
{
  public:
	explicit SupplyZones(const std::map<int, DefaultState>& defaultStates, const Configuration& theConfiguration);

	void convertSupplyZones(const States& states);

	[[nodiscard]] const auto& getSupplyZones() const { return supplyZones; }

	[[nodiscard]] std::optional<std::string> getSupplyZoneFileName(int supplyZoneNum) const;

  private:
	void importStates(const std::map<int, DefaultState>& defaultStates);

	std::map<int, std::set<int>> defaultStateToProvinceMap;
	std::map<int, std::string> supplyZonesFileNames;
	std::map<int, SupplyZone> supplyZones;
	std::map<int, int> provinceToSupplyZoneMap;
};

} // namespace HoI4



#endif // HOI4_SUPPLY_ZONES_H