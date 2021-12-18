#ifndef HOI4_CHARACTERS_CHARACTER_FACTORY_H
#define HOI4_CHARACTERS_CHARACTER_FACTORY_H



#include "HOI4World/Characters/Character.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/Names/Names.h"
#include "Mappers/Graphics/GraphicsMapper.h"



namespace HoI4
{

class Character::Factory
{
  public:
	Character createNewCountryLeader(const std::string& tag,
		 const std::pair<std::string, std::string>& nextMonarch,
		 const std::string& primaryCulture,
		 const std::string& primaryCultureGroup,
		 const std::string& governmentIdeology,
		 const std::string& leaderIdeology,
		 Names& names,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Localisation& localisation);
	Character createNewGeneral(const Vic2::Leader& src_general, const std::string& tag, Localisation& localisation);
	Character createNewAdmiral(const Vic2::Leader& src_admiral, const std::string& tag, Localisation& localisation);

  private:
	std::string determineId(const std::string& name, const std::string& tag);

	std::set<std::string> used_ids_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_CHARACTER_FACTORY_H