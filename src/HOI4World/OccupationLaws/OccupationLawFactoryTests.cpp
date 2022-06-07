#include "src/HOI4World/OccupationLaws/OccupationLawFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, NameCanBeSet)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_EQ("law_name", occupationLaw->getName());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, IconDefaultsToZero)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_EQ(0, occupationLaw->getIcon());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, IconCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\ticon = 42\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_EQ(42, occupationLaw->getIcon());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, DefaultLawDefaultsToFalse)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_FALSE(occupationLaw->getDefaultLaw());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, DefaultLawCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tdefault_law = yes\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_TRUE(occupationLaw->getDefaultLaw());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, SoundEffectDefaultsToBlank)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_TRUE(occupationLaw->getSoundEffect().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, SoundEffectCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tsound_effect = SoundEffect\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_EQ("SoundEffect", occupationLaw->getSoundEffect());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, VisibleDefaultsToNullopt)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_FALSE(occupationLaw->getVisible());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, VisibleCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tvisible = { some_condition = some_state }\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_TRUE(occupationLaw->getVisible());
	ASSERT_EQ("= { some_condition = some_state }", *occupationLaw->getVisible());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, StateModifierDefaultsToEmpty)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_TRUE(occupationLaw->getStateModifier().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, StateModifierCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tstate_modifier = { some_modifier = some_value }\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_EQ("= { some_modifier = some_value }", occupationLaw->getStateModifier());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, SuppressedStateModifierDefaultsToNullopt)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_FALSE(occupationLaw->getSuppressedStateModifier());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, SuppressedStateModifierCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tsuppressed_state_modifier = { some_modifier = some_value }\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_TRUE(occupationLaw->getSuppressedStateModifier());
	ASSERT_EQ("= { some_modifier = some_value }", *occupationLaw->getSuppressedStateModifier());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, StartingLawDefaultsToFalse)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_FALSE(occupationLaw->getStartingLaw());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, StartingLawCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tstarting_law = yes\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_TRUE(occupationLaw->getStartingLaw());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, AiWillDorDefaultsToNullopt)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_FALSE(occupationLaw->getAiWillDo());
}


TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, AiWillDoCanBeSet)
{
	std::stringstream input;
	input << "{\n";
	input << "\tai_will_do = { base = some_value }\n";
	input << "}";
	const auto occupationLaw = HoI4::OccupationLaw::Factory().getOccupationLaw("law_name", input);

	ASSERT_EQ("= { base = some_value }", *occupationLaw->getAiWillDo());
}