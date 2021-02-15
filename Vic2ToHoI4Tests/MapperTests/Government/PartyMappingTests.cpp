#include "Mappers/Government/PartyMapping.h"
#include "Mappers/Government/PartyMappingFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Government_PartyMappingTests, RulingIdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::PartyMappingFactory().importPartyMapping(input);

	ASSERT_TRUE(mapping->rulingIdeology.empty());
}


TEST(Mappers_Government_PartyMappingTests, RulingIdeologyCanBeImported)
{
	std::stringstream input;
	input << "ruling_ideology = test_ideology";

	const auto mapping = Mappers::PartyMappingFactory().importPartyMapping(input);

	ASSERT_EQ("test_ideology", mapping->rulingIdeology);
}


TEST(Mappers_Government_PartyMappingTests, Vic2IdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::PartyMappingFactory().importPartyMapping(input);

	ASSERT_TRUE(mapping->vic2Ideology.empty());
}


TEST(Mappers_Government_PartyMappingTests, Vic2IdeologyCanBeImported)
{
	std::stringstream input;
	input << "vic2_ideology = test_ideology";

	const auto mapping = Mappers::PartyMappingFactory().importPartyMapping(input);

	ASSERT_EQ("test_ideology", mapping->vic2Ideology);
}


TEST(Mappers_Government_PartyMappingTests, SupportedIdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::PartyMappingFactory().importPartyMapping(input);

	ASSERT_TRUE(mapping->supportedIdeology.empty());
}


TEST(Mappers_Government_PartyMappingTests, SupportedIdeologyCanBeImported)
{
	std::stringstream input;
	input << "supported_ideology = test_ideology";

	const auto mapping = Mappers::PartyMappingFactory().importPartyMapping(input);

	ASSERT_EQ("test_ideology", mapping->supportedIdeology);
}