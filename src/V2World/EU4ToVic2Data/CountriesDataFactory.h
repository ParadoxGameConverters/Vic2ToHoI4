#ifndef COUNTRIES_DATA_FACTORY_H
#define COUNTRIES_DATA_FACTORY_H



#include "Configuration.h"
#include "CountriesData.h"
#include "CountryDataFactory.h"
#include "external/common_items/ConvenientParser.h"
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