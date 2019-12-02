#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/Mappers/GovernmentMapper.h"



class mockGovernmentMapper: public governmentMapper
{
	public:
		MOCK_METHOD(
			std::string,
			getIdeologyForCountry,
			(const std::string& sourceTag, const std::string& sourceGovernment, const std::string& Vic2RulingIdeology),
			(const, override)
		);
		MOCK_METHOD(
			std::string,
			getLeaderIdeologyForCountry,
			(const std::string& sourceTag, const std::string& sourceGovernment, const std::string& Vic2RulingIdeology),
			(const, override)
		);
};