#ifndef COUNTRY_MAPPER_MOCK_H
#define COUNTRY_MAPPER_MOCK_H



#include "Mappers/CountryMapping.h"
#include "gmock/gmock.h"



class mockCountryMapper final: public CountryMapper
{
  public:
	MOCK_METHOD(std::optional<std::string>, getHoI4Tag, (const std::string&), (const, override));
};



#endif // COUNTRY_MAPPER_MOCK_H