#ifndef COUNTRY_DATA_FACTORY_H
#define COUNTRY_DATA_FACTORY_H



#include "CountryData.h"
#include "external/common_items/ConvenientParser.h"
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