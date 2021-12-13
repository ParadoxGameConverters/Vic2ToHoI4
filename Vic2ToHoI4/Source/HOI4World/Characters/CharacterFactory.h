#ifndef HOI4_CHARACTERS_CHARACTER_FACTORY_H
#define HOI4_CHARACTERS_CHARACTER_FACTORY_H



#include "HOI4World/Characters/Character.h"
#include "HOI4World/Names/Names.h"
#include "Mappers/Graphics/GraphicsMapper.h"



namespace HoI4
{

class Character::Factory
{
  public:
	static Character createNewCountryLeader(const std::pair<std::string, std::string>& nextMonarch,
		 const std::string& primaryCulture,
		 const std::string& primaryCultureGroup,
		 const std::string& governmentIdeology,
		 const std::string& leaderIdeology,
		 Names& names,
		 Mappers::GraphicsMapper& graphicsMapper);
};

}




#endif // HOI4_CHARACTERS_CHARACTER_FACTORY_H