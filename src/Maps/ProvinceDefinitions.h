#ifndef MAPS_PROVINCE_DEFINITIONS_H
#define MAPS_PROVINCE_DEFINITIONS_H



#include "external/common_items/Color.h"
#include <map>
#include <optional>
#include <set>



namespace Maps
{

// utility function for province definition importers
int getIntFromColor(const commonItems::Color& color);


class ProvinceDefinitions
{
  public:
	ProvinceDefinitions(std::set<int> landProvinces,
		 std::set<int> seaProvinces,
		 std::map<int, std::string> terrain_types,
		 std::map<int, int> colorToProvinceMap):
		 landProvinces(std::move(landProvinces)),
		 seaProvinces(std::move(seaProvinces)), terrain_types_(terrain_types),
		 colorToProvinceMap(std::move(colorToProvinceMap))
	{
	}

	[[nodiscard]] const auto& getLandProvinces() const { return landProvinces; }
	[[nodiscard]] bool isLandProvince(const int province) const { return landProvinces.contains(province); }
	[[nodiscard]] bool isSeaProvince(const int province) const { return seaProvinces.contains(province); }

	[[nodiscard]] std::optional<int> getProvinceFromColor(const commonItems::Color& color) const;
	[[nodiscard]] std::string getTerrainType(int province) const;

  private:
	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, std::string> terrain_types_;
	std::map<int, int> colorToProvinceMap; // colors are a packed integer to work around some issues. If you can get
														// Colors to work directly, please replace this hack.
};

} // namespace Maps



#endif // MAPS_PROVINCE_DEFINITIONS_H