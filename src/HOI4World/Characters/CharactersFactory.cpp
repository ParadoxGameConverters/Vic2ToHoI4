#include "src/HOI4World/Characters/CharactersFactory.h"
#include "external/common_items/CommonRegexes.h"



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


std::multimap<std::string, HoI4::Character> HoI4::CharactersFactory::importCharacters(std::filesystem::path filename)
{
	characters_.clear();
	parseFile(filename);
	return characters_;
}