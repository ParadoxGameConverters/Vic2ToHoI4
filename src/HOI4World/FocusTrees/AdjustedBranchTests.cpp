#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/CharacterFactory.h"
#include "src/HOI4World/FocusTrees/AdjustedBranch.h"
#include "src/HOI4World/HoI4Focus.h"



TEST(HoI4World_FocusTrees_AdjustedBranch, NameCanBeSet)
{
	HoI4::AdjustedBranch theBranch("test_adjusted_branch");

	EXPECT_EQ("test_adjusted_branch", theBranch.getName());
}

TEST(HoI4World_FocusTrees_AdjustedBranch, PathCanBeSet)
{
	HoI4::AdjustedBranch theBranch("test_adjusted_branch");

	EXPECT_EQ("Configurables/AdjustedFocusBranches/test_adjusted_branch", theBranch.getPath().string());
}

TEST(HoI4World_FocusTrees_AdjustedBranch, FocusTreeDefaultsToEmpty)
{
	HoI4::AdjustedBranch theBranch("nonexistant_branch");

	EXPECT_TRUE(theBranch.getFocusTree().getFocuses().empty());
}

TEST(HoI4World_FocusTrees_AdjustedBranch, LoadingNonexistantFocusTreeLogsWarning)
{
	const std::stringstream log;
	auto* const stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	HoI4::AdjustedBranch theBranch("nonexistant_branch");

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(),
		 testing::HasSubstr("[WARNING] Couldn't load Configurables/AdjustedFocusBranches/nonexistant_branch.txt"));
}

TEST(HoI4World_FocusTrees_AdjustedBranch, FocusesCanBeImported)
{
	HoI4::AdjustedBranch theBranch("test_adjusted_branch");
	const auto& importedFocuses = theBranch.getFocusTree().getFocuses();

	ASSERT_EQ(1, importedFocuses.size());
	EXPECT_EQ("test_adjusted_focus", importedFocuses[0]->id);
}

TEST(HoI4World_FocusTrees_AdjustedBranch, IdeasDefaultToEmpty)
{
	HoI4::AdjustedBranch theBranch("nonexistant_branch");

	EXPECT_TRUE(theBranch.getIdeas().getGeneralIdeas().empty());
}

TEST(HoI4World_FocusTrees_AdjustedBranch, IdeasCanBeImported)
{
	HoI4::AdjustedBranch theBranch("test_adjusted_branch");

	const auto& importedGeneralIdeas = theBranch.getIdeas().getGeneralIdeas();
	ASSERT_FALSE(importedGeneralIdeas.empty());

	const auto& importedIdeas = importedGeneralIdeas[0].getIdeas();
	ASSERT_EQ(1, importedIdeas.size());
	EXPECT_EQ("test_idea", importedIdeas[0].getName());
}

TEST(HoI4World_FocusTrees_AdjustedBranch, CharactersDefaultToEmpty)
{
	HoI4::AdjustedBranch theBranch("nonexistant_branch");

	EXPECT_THAT(theBranch.getCharacters(), testing::UnorderedElementsAre());
}

TEST(HoI4World_FocusTrees_AdjustedBranch, CharactersCanBeImported)
{
	HoI4::AdjustedBranch theBranch("test_adjusted_branch");

	HoI4::Character::Factory characterFactory;
	std::stringstream empty_character_input;

	EXPECT_THAT(theBranch.getCharacters(),
		 testing::UnorderedElementsAre(
			  testing::Pair("UTI", characterFactory.importCharacter("UTI_test_character", empty_character_input))));
}