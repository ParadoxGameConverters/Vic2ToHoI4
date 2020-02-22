#ifndef GOVERNMENT_MAPPER_MOCK
#define GOVERNMENT_MAPPER_MOCK



#include "../Vic2ToHoI4/Source/Mappers/GovernmentMapper.h"



class mockGovernmentMapper final: public governmentMapper
{
  public:
	MOCK_METHOD(std::string,
		 getIdeologyForCountry,
		 (const std::string& sourceTag, const std::string& sourceGovernment, const std::string& Vic2RulingIdeology),
		 (const, override));
	MOCK_METHOD(std::string,
		 getLeaderIdeologyForCountry,
		 (const std::string& sourceTag, const std::string& sourceGovernment, const std::string& Vic2RulingIdeology),
		 (const, override));
	MOCK_METHOD(std::string,
		 getSupportedIdeology,
		 (const std::string& rulingIdeology,
			  const std::string& Vic2Ideology,
			  const std::set<std::string>& majorIdeologies),
		 (const, override));
};



#endif // GOVERNMENT_MAPPER_MOCK