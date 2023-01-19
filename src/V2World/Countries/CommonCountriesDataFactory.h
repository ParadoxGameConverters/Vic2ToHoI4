#ifndef SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_H
#define SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "src/V2World/Countries/CommonCountryData.h"
#include <map>
#include <string>



namespace Vic2
{

std::tuple<std::map<std::string, CommonCountryData>, std::vector<Party>> ImportCommonCountriesData(
	 const commonItems::ModFilesystem& mod_filesystem);

} // namespace Vic2



#endif // SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_H