#ifndef OUT_COUNTRY_CATEGORIES_H
#define OUT_COUNTRY_CATEGORIES_H



#include "src/HOI4World/CountryCategories/CountryCategories.h"



namespace HoI4
{

void outCountryCategories(const std::map<std::string, TagsAndExtras>& countryCategories, const std::filesystem::path& outputName);

}



#endif // OUT_COUNTRY_CATEGORIES_H