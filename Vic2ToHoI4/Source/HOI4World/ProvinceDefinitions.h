#ifndef PROVINCE_DEFINITIONS_H
#define PROVINCE_DEFINITIONS_H



#include "Color.h"
#include <map>
#include <optional>
#include <set>



class Configuration;



namespace HoI4
{

class ProvinceDefinitions
{
  public:
	class Importer;

	ProvinceDefinitions(std::set<int> landProvinces, std::set<int> seaProvinces, std::map<int, int> colorToProvinceMap):
		 landProvinces(std::move(landProvinces)), seaProvinces(std::move(seaProvinces)),
		 colorToProvinceMap(std::move(colorToProvinceMap))
	{
	}

	[[nodiscard]] const auto& getLandProvinces() const { return landProvinces; }
	[[nodiscard]] bool isLandProvince(const int province) const { return (landProvinces.count(province) > 0); }
	[[nodiscard]] bool isSeaProvince(const int province) const { return (seaProvinces.count(province) > 0); }

	[[nodiscard]] std::optional<int> getProvinceFromColor(const commonItems::Color& color) const;

  private:
	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, int> colorToProvinceMap; // colors are a packed integer to work around some issues. If you can get
														// Colors to work directly, please replace this hack.
};


class ProvinceDefinitions::Importer
{
  public:
	[[nodiscard]] ProvinceDefinitions importProvinceDefinitions(const Configuration& theConfiguration) const;
};

} // namespace HoI4



#endif // PROVINCE_DEFINITIONS_H