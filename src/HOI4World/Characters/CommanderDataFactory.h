#ifndef HOI4WORLD_CHARACTERS_COMMANDER_DATA_FACTORY_H
#define HOI4WORLD_CHARACTERS_COMMANDER_DATA_FACTORY_H



#include "HOI4World/Characters/CommanderData.h"
#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class CommanderDataFactory: commonItems::parser
{
  public:
	CommanderDataFactory();

	CommanderData importCommanderData(std::string_view commanderType, std::istream& input);

  private:
	CommanderLevel level_ = CommanderLevel::CorpsCommander;
	std::vector<std::string> traits_;
	int skill_ = 1;
	int attack_skill_ = 1;
	int defense_skill_ = 1;
	int planning_skill_ = 1;
	int logistics_skill_ = 1;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_COMMANDER_DATA_FACTORY_H