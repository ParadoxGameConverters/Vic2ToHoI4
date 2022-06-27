#ifndef HOI4WORLD_MAP_RAILWAYS_H
#define HOI4WORLD_MAP_RAILWAYS_H



#include "src/HOI4World/Map/Hoi4Province.h"
#include "src/HOI4World/Map/ImpassableProvinces.h"
#include "src/HOI4World/Map/Railway.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Maps/MapData.h"
#include "src/V2World/Provinces/Province.h"
#include "src/V2World/States/State.h"
#include <map>
#include <memory>
#include <vector>



namespace HoI4
{

class Railways
{
  public:
	Railways(const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
		 const std::vector<std::reference_wrapper<const Vic2::State>>& vic2_states,
		 const Maps::MapData& vic2_map_data,
		 const Mappers::ProvinceMapper& province_mapper,
		 const Maps::MapData& hoi4_map_data,
		 const Maps::ProvinceDefinitions& hoi4_province_definitions,
		 const ImpassableProvinces& impassable_provinces,
		 const std::map<int, Province>& hoi4_provinces,
		 const std::set<int>& naval_base_locations,
		 const HoI4::States& hoi4_states);

	[[nodiscard]] const auto& GetRailways() const { return railways_; }
	[[nodiscard]] const auto& GetRailwayEndpoints() const { return railway_endpoints_; }

  private:
	std::vector<Railway> railways_;
	std::set<int> railway_endpoints_;
};

} // namespace HoI4



#endif // HOI4WORLD_MAP_RAILWAYS_H