#ifndef HOI4_SUPPLYNODES_H
#define HOI4_SUPPLYNODES_H


#include "Mappers/Provinces/ProvinceMapper.h"
#include "V2World/Provinces/Province.h"
#include <set>



namespace HoI4
{

[[nodiscard]] std::set<int> determineSupplyNodes(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Mappers::ProvinceMapper& provinceMapper);

} // namespace HoI4



#endif // HOI4_SUPPLYNODES_H