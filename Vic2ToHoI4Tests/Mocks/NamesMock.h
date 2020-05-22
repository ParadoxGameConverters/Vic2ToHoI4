#ifndef NAMES_MAPPER_MOCK
#define NAMES_MAPPER_MOCK



#include "../../Vic2ToHoI4/Source/HOI4World/Names.h"
#include "gmock/gmock.h"



class mockNames final: public HoI4::Names
{
  public:
	MOCK_METHOD(std::optional<std::vector<std::string>>, getMaleNames, (const std::string& culture), (const, override));
};



#endif // NAMES_MAPPER_MOCK