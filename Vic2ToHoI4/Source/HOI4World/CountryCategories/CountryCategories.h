#ifndef COUNTRY_CATEGORIES_FACTORY_H
#define COUNTRY_CATEGORIES_FACTORY_H



#include "Mappers/Country/CountryMapper.h"
#include <map>
#include <optional>
#include <string>



namespace HoI4
{

using TagsAndExtras = std::map<std::string, std::optional<std::string>>;


std::map<std::string, TagsAndExtras> createCountryCategories(const Mappers::CountryMapper& countryMapper);


} // namespace HoI4



#endif // COUNTRY_CATEGORIES_FACTORY_H