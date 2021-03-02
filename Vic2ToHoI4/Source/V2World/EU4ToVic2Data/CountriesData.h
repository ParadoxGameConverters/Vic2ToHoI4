#ifndef COUNTRIES_DATA_H
#define COUNTRIES_DATA_H



#include "CountryData.h"
#include <map>
#include <string>



namespace Vic2
{

class CountriesData
{
  public:
	class Factory;

	[[nodiscard]] std::optional<CountryData> getCountryData(const std::string& tag) const;

  private:
	std::map<std::string, CountryData> countriesData;
};

} // namespace Vic2



#endif // COUNTRIES_DATA_H