#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/CharactersFactory.h"
#include <sstream>



TEST(HoI4World_Characters_CharactersFactory, CharactersCanBeImported)
{
	HoI4::Character::Factory characterFactory;
	HoI4::CharactersFactory charactersFactory(characterFactory);

	const auto characters = charactersFactory.importCharacters();

	std::stringstream empty_character_input;
	EXPECT_THAT(characters,
		 testing::UnorderedElementsAre(
			  testing::Pair("ONE", characterFactory.importCharacter("ONE_only_character", empty_character_input)),
			  testing::Pair("TWO", characterFactory.importCharacter("TWO_first_character", empty_character_input)),
			  testing::Pair("TWO", characterFactory.importCharacter("TWO_second_character", empty_character_input)),
			  testing::Pair("FOO", characterFactory.importCharacter("FOO_first_character", empty_character_input)),
			  testing::Pair("FOO", characterFactory.importCharacter("FOO_second_character", empty_character_input))));
}