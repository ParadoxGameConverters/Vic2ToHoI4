#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/CharactersCountryFactory.h"
#include <sstream>



TEST(HoI4World_Characters_CharactersCountryFactory, CharactersDefaultToEmpty)
{
	HoI4::Character::Factory characterFactory;
	HoI4::CharactersCountryFactory charactersCountryFactory(characterFactory);

	std::stringstream input;
	const auto characters = charactersCountryFactory.importCharacters(input);

	EXPECT_THAT(characters, testing::ElementsAre());
}


TEST(HoI4World_Characters_CharactersCountryFactory, CharactersCanBeImported)
{
	HoI4::Character::Factory characterFactory;
	HoI4::CharactersCountryFactory charactersCountryFactory(characterFactory);

	std::stringstream input;
	input << "={\n";
	input << "\tfirst_character={\n";
	input << "\t}\n";
	input << "\tsecond_character={\n";
	input << "\t}\n";
	input << "}";
	const auto characters = charactersCountryFactory.importCharacters(input);

	std::stringstream empty_character_input;
	EXPECT_THAT(characters,
		 testing::ElementsAre(characterFactory.importCharacter("first_character", empty_character_input),
			  characterFactory.importCharacter("second_character", empty_character_input)));
}