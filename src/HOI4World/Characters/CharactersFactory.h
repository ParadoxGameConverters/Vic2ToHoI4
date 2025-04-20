#ifndef HOI4WORLD_CHARACTERS_CHARACTERS_FACTORY_H
#define HOI4WORLD_CHARACTERS_CHARACTERS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Characters/Character.h"
#include "src/HOI4World/Characters/CharacterFactory.h"
#include "src/HOI4World/Characters/CharactersCountryFactory.h"
#include <map>
#include <string>



namespace HoI4
{

class CharactersFactory: commonItems::parser
{
  public:
	explicit CharactersFactory(Character::Factory& characterFactory);

	std::multimap<std::string, Character> importCharacters(std::filesystem::path filename);

  private:
	std::multimap<std::string, Character> characters_;

	CharactersCountryFactory characters_country_factory_;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_CHARACTERS_FACTORY_H