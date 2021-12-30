#include "CharactersFactory.h"
#include "CommonRegexes.h"



HoI4::CharactersFactory::CharactersFactory(Character::Factory& characterFactory):
	 characters_country_factory_(characterFactory)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& tag, std::istream& input) {
		for (const auto& character: characters_country_factory_.importCharacters(input))
		{
			characters_.emplace(tag, character);
		}
	});
}


std::multimap<std::string, HoI4::Character> HoI4::CharactersFactory::importCharacters()
{
	characters_.clear();
	parseFile("Configurables/ImportCharacters.txt");
	return characters_;
}