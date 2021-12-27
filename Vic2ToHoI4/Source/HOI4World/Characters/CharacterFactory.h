#ifndef HOI4_CHARACTERS_CHARACTER_FACTORY_H
#define HOI4_CHARACTERS_CHARACTER_FACTORY_H



#include "HOI4World/Characters/Character.h"
#include "HOI4World/Characters/CommanderDataFactory.h"
#include "HOI4World/Characters/CountryLeaderDataFactory.h"
#include "HOI4World/Characters/PortraitsFactory.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/Names/Names.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Parser.h"



namespace HoI4
{

class Character::Factory: commonItems::parser
{
  public:
	Factory();

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
	Character importCharacter(std::string_view id, std::istream& input);

  private:
	std::string determineId(const std::string& name, const std::string& tag);

	std::set<std::string> used_ids_;
	PortraitsFactory portraits_factory_;
	CountryLeaderDataFactory country_leader_data_factory_;
	CommanderDataFactory commander_data_factory_;

	std::unique_ptr<Character> imported_character_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_CHARACTER_FACTORY_H