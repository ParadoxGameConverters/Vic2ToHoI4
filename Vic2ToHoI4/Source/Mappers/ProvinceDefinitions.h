#ifndef PROVINCE_DEFINITIONS
#define PROVINCE_DEFINITIONS



#include "../Color.h"
#include <map>
#include <optional>
#include <set>



class ProvinceDefinitions
{
  public:
	ProvinceDefinitions() noexcept;

	const auto& getLandProvinces() const { return landProvinces; }
	const bool isLandProvince(int province) const { return (landProvinces.count(province) > 0); }
	const bool isSeaProvince(int province) const { return (seaProvinces.count(province) > 0); }

	std::optional<int> getProvinceFromColor(const ConverterColor::Color& color) const;

  private:
	int getIntFromColor(const ConverterColor::Color& color) const;

	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, int> colorToProvinceMap; // colors are a packed integer to work around some issues. If you can get
														// Colors to work directly, please replace this hack.
};



#endif // PROVINCE_DEFINITIONS