#ifndef PROVINCE_DEFINITIONS_H
#define PROVINCE_DEFINITIONS_H



#include "../Color.h"
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

	const auto& getLandProvinces() const { return landProvinces; }
	const bool isLandProvince(int province) const { return (landProvinces.count(province) > 0); }
	const bool isSeaProvince(int province) const { return (seaProvinces.count(province) > 0); }

	std::optional<int> getProvinceFromColor(const ConverterColor::Color& color) const;

  private:
	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, int> colorToProvinceMap; // colors are a packed integer to work around some issues. If you can get
														// Colors to work directly, please replace this hack.
};


class ProvinceDefinitions::Importer
{
  public:
	ProvinceDefinitions importProvinceDefinitions(const Configuration& theConfiguration);
};

} // namespace HoI4



#endif // PROVINCE_DEFINITIONS_H