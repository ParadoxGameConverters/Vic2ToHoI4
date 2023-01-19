#ifndef STRATEGIC_REGIONS_H
#define STRATEGIC_REGIONS_H



#include "src/Configuration.h"
#include "src/HOI4World/Map/StrategicRegion.h"
#include "src/HOI4World/States/HoI4State.h"
#include <map>
#include <memory>
#include <optional>



namespace HoI4
{

class States; // forward declaration to break circular dependency


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
	[[nodiscard]] const auto& getProvinceToStrategicRegionMap() const { return provinceToStrategicRegionMap; }

	void convert(const States& theStates);

  private:
	std::map<int, int> determineUsedRegions(const State& state);
	[[nodiscard]] static std::optional<int> determineMostUsedRegion(const std::map<int, int>& usedRegions);
	void addLeftoverProvincesToRegions();
	void addProvincesToRegion(int regionNumber, const State& state);
	void addProvinceToRegion(int regionNumber, int provinceId);

	std::map<int, StrategicRegion> strategicRegions;
	std::map<int, int> provinceToStrategicRegionMap;
};


class StrategicRegions::Factory
{
  public:
	static std::unique_ptr<StrategicRegions> importStrategicRegions(const Configuration& theConfiguration);
};

} // namespace HoI4



#endif // STRATEGIC_REGIONS_H