#ifndef HOI4WORLD_CHARACTERS_CHARACTERS_COUNTRY_FACTORY_H
#define HOI4WORLD_CHARACTERS_CHARACTERS_COUNTRY_FACTORY_H



#include "HOI4World/Characters/CharacterFactory.h"
#include "external/common_items/ConvenientParser.h"
#include <vector>



namespace HoI4
{

class CharactersCountryFactory: commonItems::parser
{
  public:
	explicit CharactersCountryFactory(Character::Factory& characterFactory);

	std::vector<Character> importCharacters(std::istream& input);

  private:
	std::vector<Character> characters_;
	Character::Factory& character_factory_ref_;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_CHARACTERS_COUNTRY_FACTORY_H