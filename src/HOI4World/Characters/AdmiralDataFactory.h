#ifndef HOI4WORLD_CHARACTERS_ADMIRAL_DATA_FACTORY_H
#define HOI4WORLD_CHARACTERS_ADMIRAL_DATA_FACTORY_H



#include "HOI4World/Characters/AdmiralData.h"
#include "Parser.h"



namespace HoI4
{

class AdmiralDataFactory: commonItems::parser
{
  public:
	AdmiralDataFactory();

	AdmiralData importAdmiralData(std::istream& input);

  private:
	std::vector<std::string> traits_;
	int skill_ = 1;
	int attack_skill_ = 1;
	int defense_skill_ = 1;
	int maneuvering_skill_ = 1;
	int coordination_skill_ = 1;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_ADMIRAL_DATA_FACTORY_H