#ifndef PROVINCE_MAPPING_TYPES_H
#define PROVINCE_MAPPING_TYPES_H



#include <map>
#include <vector>



namespace Mappers
{

using HoI4ToVic2ProvinceMapping = std::map<int, std::vector<int>>;
using Vic2ToHoI4ProvinceMapping = std::map<int, std::vector<int>>;

} // namespace Mappers



#endif // PROVINCE_MAPPING_TYPES_H