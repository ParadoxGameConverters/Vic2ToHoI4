#ifndef COMMON_COUNTRY_DATA_H
#define COMMON_COUNTRY_DATA_H



#include "CommonCountryData.h"
#include "Configuration.h"
#include <map>
#include <string>



namespace Vic2
{

std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> importCommonCountriesData(
	 const Configuration& theConfiguration);

}



#endif // COMMON_COUNTRY_DATA_H