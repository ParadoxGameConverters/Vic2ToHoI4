#ifndef HOI4WORLD_CHARACTERS_CHARACTERS_FACTORY_H
#define HOI4WORLD_CHARACTERS_CHARACTERS_FACTORY_H



#include "HOI4World/Characters/Character.h"
#include "HOI4World/Characters/CharacterFactory.h"
#include "HOI4World/Characters/CharactersCountryFactory.h"
#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class CharactersFactory: commonItems::parser
{
  public:
	explicit CharactersFactory(Character::Factory& characterFactory);

	std::multimap<std::string, Character> importCharacters();

  private:
	std::multimap<std::string, Character> characters_;

	CharactersCountryFactory characters_country_factory_;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_CHARACTERS_FACTORY_H