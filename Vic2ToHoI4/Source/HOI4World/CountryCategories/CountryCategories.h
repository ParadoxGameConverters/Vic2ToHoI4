#ifndef COUNTRY_CATEGORIES_FACTORY_H
#define COUNTRY_CATEGORIES_FACTORY_H



#include <map>
#include <optional>
#include <string>



namespace HoI4
{

using tagsAndExtras = std::map<std::string, std::optional<std::string>>;


std::map<std::string, tagsAndExtras> createCountryCategories();


} // namespace HoI4



#endif // COUNTRY_CATEGORIES_FACTORY_H