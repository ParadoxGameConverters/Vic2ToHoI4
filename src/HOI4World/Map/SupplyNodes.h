#ifndef HOI4_SUPPLY_NODES_H
#define HOI4_SUPPLY_NODES_H


#include "src/HOI4World/States/HoI4States.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/V2World/Provinces/Province.h"
#include <set>



namespace HoI4
{

[[nodiscard]] std::set<int> determineSupplyNodes(const std::map<int, State>& states,
	 const std::set<int>& railwayEndpoints);

} // namespace HoI4



#endif // HOI4_SUPPLY_NODES_H