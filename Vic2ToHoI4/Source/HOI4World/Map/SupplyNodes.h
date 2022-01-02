#ifndef HOI4_SUPPLY_NODES_H
#define HOI4_SUPPLY_NODES_H


#include "Mappers/Provinces/ProvinceMapper.h"
#include "V2World/Provinces/Province.h"
#include <set>



namespace HoI4
{

[[nodiscard]] std::set<int> determineSupplyNodes(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const std::set<int>& railwayEndpoints);

} // namespace HoI4



#endif // HOI4_SUPPLY_NODES_H