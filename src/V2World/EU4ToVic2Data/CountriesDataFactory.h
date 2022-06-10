#ifndef COUNTRIES_DATA_FACTORY_H
#define COUNTRIES_DATA_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/V2World/EU4ToVic2Data/CountriesData.h"
#include "src/V2World/EU4ToVic2Data/CountryDataFactory.h"
#include <memory>



namespace Vic2
{

class CountriesData::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CountriesData> importCountriesData(const Configuration& configuration);

  private:
	CountryData::Factory countryDataFactory;

	std::unique_ptr<CountriesData> countriesData;
};

} // namespace Vic2



#endif // COUNTRIES_DATA_FACTORY_H