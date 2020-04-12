#ifndef PROVINCE_MAPPER_MOCK
#define PROVINCE_MAPPER_MOCK



#include "../../Vic2ToHoI4/Source/Mappers/Provinces/ProvinceMapper.h"
#include "gmock/gmock.h"



class mockProvinceMapper final: public mappers::ProvinceMapper
{
  public:
	MOCK_METHOD(std::optional<std::vector<int>>, getVic2ToHoI4ProvinceMapping, (int Vic2Province), (const, override));
};



#endif // PROVINCE_MAPPER_MOCK