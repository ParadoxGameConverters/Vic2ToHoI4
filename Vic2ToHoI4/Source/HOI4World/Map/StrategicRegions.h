#ifndef STRATEGIC_REGIONS_H
#define STRATEGIC_REGIONS_H



#include "../../Configuration.h"
#include "StrategicRegion.h"
#include <map>
#include <memory>



namespace HoI4
{

class StrategicRegions
{
  public:
	class Factory;
	StrategicRegions(std::map<int, StrategicRegion>&& strategicRegions,
		 std::map<int, int>&& provinceToStrategicRegionMap):
		 strategicRegions(strategicRegions),
		 provinceToStrategicRegionMap(provinceToStrategicRegionMap)
	{
	}

	[[nodiscard]] const auto& getStrategicRegions() const { return strategicRegions; }
	[[nodiscard]] auto getProvinceToStrategicRegionMapCopy() const { return provinceToStrategicRegionMap; }

	void addProvinceToRegion(int regionNumber, int provinceId);

  private:
	std::map<int, StrategicRegion> strategicRegions;
	std::map<int, int> provinceToStrategicRegionMap;
};


class StrategicRegions::Factory
{
  public:
	std::unique_ptr<StrategicRegions> importStrategicRegions(const Configuration& theConfiguration);
};

} // namespace HoI4



#endif // STRATEGIC_REGIONS_H