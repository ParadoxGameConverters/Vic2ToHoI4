#include "CountriesData.h"



std::optional<Vic2::CountryData> Vic2::CountriesData::getCountryData(const std::string& tag) const
{
	const auto itr = countriesData.find(tag);
	if (itr == countriesData.end())
	{
		return std::nullopt;
	}

	return itr->second;
}