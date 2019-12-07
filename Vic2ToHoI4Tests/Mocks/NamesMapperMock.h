#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/Names.h"



class mockNamesMapper: public HoI4::namesMapper
{
	public:
		MOCK_METHOD(std::optional<std::vector<std::string>>, getMaleNames, (const std::string& culture), (const, override));
};