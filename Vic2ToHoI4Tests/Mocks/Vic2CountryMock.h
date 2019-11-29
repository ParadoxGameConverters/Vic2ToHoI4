#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/V2World/Country.h"



class mockVic2Country: public Vic2::Country
{
	public:
		MOCK_METHOD(std::optional<std::string>, getName, (const std::string& language), (const, override));
};