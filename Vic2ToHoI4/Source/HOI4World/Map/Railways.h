#ifndef HOI4WORLD_MAP_RAILWAYS_H
#define HOI4WORLD_MAP_RAILWAYS_H



#include "HOI4World/Map/Hoi4Province.h"
#include "HOI4World/Map/Railway.h"
#include "ImpassableProvinces.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Maps/MapData.h"
#include "V2World/Provinces/Province.h"
#include <map>
#include <memory>
#include <vector>



namespace HoI4
{

std::vector<Railway> determineRailways(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Maps::MapData& Vic2MapData,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions,
	 const ImpassableProvinces& impassableProvinces,
	 const std::map<int, HoI4::Province>& hoi4Provinces);

}



#endif // HOI4WORLD_MAP_RAILWAYS_H