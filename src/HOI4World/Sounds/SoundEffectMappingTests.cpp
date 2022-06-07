#include "src/HOI4World/Sounds/SoundEffectMapping.h"
#include "src/HOI4World/Sounds/SoundEffectMappingFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Sounds_SoundEffectMapping, LinksDefaultToEmpty)
{
	std::stringstream input;
	const auto soundEffectMapping = HoI4::SoundEffectMapping::Factory().getSoundEffectMapping(input);

	ASSERT_TRUE(soundEffectMapping->getLinks().empty());
}


TEST(HoI4World_Sounds_SoundEffectMapping, LinksCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlink = { culture = test_culture }\n";
	input << "\tlink = { culture = another_culture }\n";
	input << "}";
	const auto soundEffectMapping = HoI4::SoundEffectMapping::Factory().getSoundEffectMapping(input);

	ASSERT_EQ(2, soundEffectMapping->getLinks().size());
	ASSERT_TRUE(soundEffectMapping->getLinks()[0].getCultures().contains("test_culture"));
	ASSERT_TRUE(soundEffectMapping->getLinks()[1].getCultures().contains("another_culture"));
}