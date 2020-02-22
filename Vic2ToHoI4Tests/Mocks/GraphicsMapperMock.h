#ifndef GRAPHICS_MAPPER_MOCK
#define GRAPHICS_MAPPER_MOCK



#include "../../Vic2ToHoI4/Source/Mappers/GraphicsMapper.h"
#include "gmock/gmock.h"



class mockGraphicsMapper final: public graphicsMapper
{
  public:
	MOCK_METHOD(std::optional<std::string>, getGraphicalCulture, (const std::string& cultureGroup), (const, override));
	MOCK_METHOD(std::optional<std::string>, get2dGraphicalCulture, (const std::string& cultureGroup), (const, override));
};



#endif // GRAPHICS_MAPPER_MOCK