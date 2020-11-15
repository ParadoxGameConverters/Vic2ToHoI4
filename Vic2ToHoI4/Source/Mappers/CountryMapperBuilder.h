#ifndef COUNTRY_MAPPER_BUILDER_H
#define COUNTRY_MAPPER_BUILDER_H



#include "CountryMapping.h"
#include <memory>



class CountryMapper::Builder
{
  public:
	Builder() { countryMapper = std::make_unique<CountryMapper>(); }
	std::unique_ptr<CountryMapper> Build() { return std::move(countryMapper); }
	Builder& addMapping(const std::string& Vic2Tag, const std::string& HoI4Tag)
	{
		countryMapper->V2TagToHoI4TagMap[Vic2Tag] = HoI4Tag;
		countryMapper->HoI4TagToV2TagMap[HoI4Tag] = Vic2Tag;
		return *this;
	}

  private:
	std::unique_ptr<CountryMapper> countryMapper;
};



#endif // COUNTRY_MAPPER_BUILDER_H