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
	StrategicRegions(std::map<int, StrategicRegion> strategic_regions,
		 std::map<int, int> province_to_strategic_region_map):
		 strategic_regions_(std::move(strategic_regions)),
		 original_province_to_strategic_region_map_(std::move(province_to_strategic_region_map))
	{
		new_province_to_strategic_region_map_ = original_province_to_strategic_region_map_;
	}

	[[nodiscard]] const auto& GetStrategicRegions() const { return strategic_regions_; }
	[[nodiscard]] const auto& GetProvinceToStrategicRegionMap() const { return new_province_to_strategic_region_map_; }

	void Convert(const States& states, const Maps::MapData& hoi4_map_data);

  private:
	std::map<int, StrategicRegion> strategic_regions_;
	std::map<int, int> original_province_to_strategic_region_map_;
	std::map<int, int> new_province_to_strategic_region_map_;
};


class StrategicRegions::Factory
{
  public:
	static std::unique_ptr<StrategicRegions> ImportStrategicRegions(const Configuration& configuration);
};

} // namespace HoI4



#endif // STRATEGIC_REGIONS_H