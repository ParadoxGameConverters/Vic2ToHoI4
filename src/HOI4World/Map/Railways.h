#ifndef HOI4WORLD_MAP_RAILWAYS_H
#define HOI4WORLD_MAP_RAILWAYS_H



#include "src/HOI4World/Map/Hoi4Province.h"
#include "src/HOI4World/Map/Railway.h"
#include "ImpassableProvinces.h"
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
	Railways(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
		 const std::vector<std::reference_wrapper<const Vic2::State>>& states,
		 const Maps::MapData& Vic2MapData,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Maps::MapData& HoI4MapData,
		 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions,
		 const ImpassableProvinces& impassableProvinces,
		 const std::map<int, Province>& hoi4Provinces,
		 const std::set<int>& navalBaseLocations);

	[[nodiscard]] const auto& getRailways() const { return railways_; }
	[[nodiscard]] const auto& getRailwayEndpoints() const { return railway_endpoints_; }

  private:
	std::vector<Railway> railways_;
	std::set<int> railway_endpoints_;
};

} // namespace HoI4



#endif // HOI4WORLD_MAP_RAILWAYS_H