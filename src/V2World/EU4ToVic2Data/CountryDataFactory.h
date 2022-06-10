#ifndef COUNTRY_DATA_FACTORY_H
#define COUNTRY_DATA_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/EU4ToVic2Data/CountryData.h"
#include <memory>



namespace Vic2
{

class CountryData::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CountryData> importCountryData(std::istream& theStream);

  private:
	std::unique_ptr<CountryData> countryData;
};

} // namespace Vic2



#endif // COUNTRY_DATA_FACTORY_H