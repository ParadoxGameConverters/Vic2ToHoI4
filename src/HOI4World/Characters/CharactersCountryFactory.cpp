#include "CharactersCountryFactory.h"
#include "CommonRegexes.h"



HoI4::CharactersCountryFactory::CharactersCountryFactory(Character::Factory& characterFactory):
	 character_factory_ref_(characterFactory)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& input) {
		characters_.push_back(character_factory_ref_.importCharacter(id, input));
	});
}


std::vector<HoI4::Character> HoI4::CharactersCountryFactory::importCharacters(std::istream& input)
{
	characters_.clear();
	parseStream(input);
	return characters_;
}