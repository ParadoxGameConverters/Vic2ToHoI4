#ifndef COUNTRY_DATA_BUILDER_H
#define COUNTRY_DATA_BUILDER_H



#include "CountryData.h"
#include <memory>



namespace Vic2
{

class CountryData::Builder
{
  public:
	Builder() { countryData = std::make_unique<CountryData>(); }
	std::unique_ptr<CountryData> Build() { return std::move(countryData); }

	Builder& setLastDynasty(const std::string& lastDynasty)
	{
		countryData->lastDynasty = lastDynasty;
		return *this;
	}
	Builder& setLastMonarch(const std::string& lastMonarch)
	{
		countryData->lastMonarch = lastMonarch;
		return *this;
	}

  private:
	std::unique_ptr<CountryData> countryData;
};

} // namespace Vic2



#endif // COUNTRY_DATA_BUILDER_H