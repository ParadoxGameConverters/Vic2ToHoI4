#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/Mappers/GraphicsMapper.h"



class mockGraphicsMapper: public graphicsMapper
{
	public:
		MOCK_METHOD(
			std::optional<std::string>,
			getGraphicalCulture,
			(const std::string& cultureGroup),
			(const, override)
		);
		MOCK_METHOD(
			std::optional<std::string>,
			get2dGraphicalCulture,
			(const std::string& cultureGroup),
			(const, override)
		);
};