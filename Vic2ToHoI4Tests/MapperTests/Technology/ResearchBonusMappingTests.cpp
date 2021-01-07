#include "Mappers/Technology/ResearchBonusMapping.h"
#include "Mappers/Technology/ResearchBonusMappingFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(ResearchMappingTests, Vic2RequirementsDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::ResearchBonusMapping::Factory{}.importResearchBonusMapping(input);

	ASSERT_TRUE(mapping->getVic2Requirements().empty());
}


TEST(ResearchMappingTests, Vic2RequirementsCanBeAdded)
{
	std::stringstream input;
	input << "vic2 = test_item\n";
	input << "vic2 = test_item2";
	const auto mapping = Mappers::ResearchBonusMapping::Factory{}.importResearchBonusMapping(input);

	ASSERT_THAT(mapping->getVic2Requirements(), testing::UnorderedElementsAre("test_item", "test_item2"));
}


TEST(ResearchMappingTests, ResearchBonusesDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::ResearchBonusMapping::Factory{}.importResearchBonusMapping(input);

	ASSERT_TRUE(mapping->getResearchBonuses().empty());
}


TEST(ResearchMappingTests, ResearchBonusesCanBeAdded)
{
	std::stringstream input;
	input << "test_item = 0\n";
	input << "test_item2 = 42";
	const auto mapping = Mappers::ResearchBonusMapping::Factory{}.importResearchBonusMapping(input);

	ASSERT_THAT(mapping->getResearchBonuses(),
		 testing::UnorderedElementsAre(std::pair("test_item", 0), std::pair("test_item2", 42)));
}