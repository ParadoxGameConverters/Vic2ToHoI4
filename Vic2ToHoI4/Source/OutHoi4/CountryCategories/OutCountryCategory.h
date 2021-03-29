#ifndef OUT_COUNTRY_CATEGORY_H
#define OUT_COUNTRY_CATEGORY_H



#include "HOI4World/CountryCategories/CountryCategories.h"
#include <ostream>



namespace HoI4
{

void outputCountryCategory(std::ostream& out, const std::string& category, const TagsAndExtras& tagsAndExtras);

}



#endif // OUT_COUNTRY_CATEGORY_H