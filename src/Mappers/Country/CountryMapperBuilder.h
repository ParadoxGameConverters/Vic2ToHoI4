#ifndef COUNTRY_MAPPER_BUILDER_H
#define COUNTRY_MAPPER_BUILDER_H



#include "src/Mappers/Country/CountryMapper.h"
#include <memory>



namespace Mappers
{

class CountryMapper::Builder
{
  public:
	Builder() { countryMapper = std::make_unique<CountryMapper>(); }

	std::unique_ptr<CountryMapper> Build() { return std::move(countryMapper); }

	Builder& addMapping(const std::string& Vic2Tag, const std::string& HoI4Tag)
	{
		countryMapper->Vic2TagToHoI4TagMap[Vic2Tag] = HoI4Tag;
		return *this;
	}

  private:
	std::unique_ptr<CountryMapper> countryMapper;
};

} // namespace Mappers



#endif // COUNTRY_MAPPER_BUILDER_H