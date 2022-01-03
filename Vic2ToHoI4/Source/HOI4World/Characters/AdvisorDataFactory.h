#ifndef HOI4WORLD_CHARACTERS_ADVISOR_DATA_FACTORY_H
#define HOI4WORLD_CHARACTERS_ADVISOR_DATA_FACTORY_H



#include "HOI4World/Characters/AdvisorData.h"
#include "Parser.h"



namespace HoI4
{

class AdvisorDataFactory: commonItems::parser
{
	public:
	AdvisorDataFactory();

	AdvisorData importAdvisorData(std::istream& input);

	private:
	std::string slot_;
	std::string idea_token_;
	std::optional<std::string> ledger_;
	std::optional<std::string> available_;
	std::string allowed_;
	std::optional<std::string> visible_;
	std::optional<std::string> research_bonus_;
	std::vector<std::string> traits_;
	std::optional<float> cost_;
	std::optional<std::string> do_effect_;
	std::optional<std::string> ai_will_do_;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_ADVISOR_DATA_FACTORY_H