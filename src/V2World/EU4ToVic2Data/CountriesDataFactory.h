#ifndef COUNTRIES_DATA_FACTORY_H
#define COUNTRIES_DATA_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "external/common_items/ModLoader/ModFilesystem.h"
#include "src/V2World/EU4ToVic2Data/CountriesData.h"
#include "src/V2World/EU4ToVic2Data/CountryDataFactory.h"
#include <memory>



namespace Vic2
{

class CountriesData::Factory
{
  public:
	Factory();
	std::unique_ptr<CountriesData> ImportCountriesData(const commonItems::ModFilesystem& mod_filesystem);

  private:
	commonItems::parser parser_;
	CountryData::Factory country_data_factory_;

	std::unique_ptr<CountriesData> countries_data_;
};

} // namespace Vic2



#endif // COUNTRIES_DATA_FACTORY_H