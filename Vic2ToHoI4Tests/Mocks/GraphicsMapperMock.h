#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/Mappers/GraphicsMapper.h"



class mockGraphicsMapper: public graphicsMapper
{
	public:
		MOCK_METHOD(std::string, getLeaderPortrait, (const std::string& cultureGroup, const std::string& ideology), (override));
};