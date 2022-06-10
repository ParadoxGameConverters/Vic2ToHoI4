#ifndef COMMON_COUNTRY_DATA_H
#define COMMON_COUNTRY_DATA_H



#include "src/Configuration.h"
#include "src/V2World/Countries/CommonCountryData.h"
#include <map>
#include <string>



namespace Vic2
{

std::tuple<std::map<std::string, CommonCountryData>, std::vector<Party>> importCommonCountriesData(
	 const Configuration& theConfiguration);

} // namespace Vic2



#endif // COMMON_COUNTRY_DATA_H