#include "Mappers/Government/IdeologyMapping.h"
#include "Mappers/Government/IdeologyMappingFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Government_IdeologyMappingTests, RulingIdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::IdeologyMappingFactory().importIdeologyMapping(input);

	ASSERT_TRUE(mapping->rulingIdeology.empty());
}


TEST(Mappers_Government_IdeologyMappingTests, RulingIdeologyCanBeImported)
{
	std::stringstream input;
	input << "ruling_ideology = test_ideology";

	const auto mapping = Mappers::IdeologyMappingFactory().importIdeologyMapping(input);

	ASSERT_EQ("test_ideology", mapping->rulingIdeology);
}


TEST(Mappers_Government_IdeologyMappingTests, Vic2IdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::IdeologyMappingFactory().importIdeologyMapping(input);

	ASSERT_TRUE(mapping->vic2Ideology.empty());
}


TEST(Mappers_Government_IdeologyMappingTests, Vic2IdeologyCanBeImported)
{
	std::stringstream input;
	input << "vic2_ideology = test_ideology";

	const auto mapping = Mappers::IdeologyMappingFactory().importIdeologyMapping(input);

	ASSERT_EQ("test_ideology", mapping->vic2Ideology);
}


TEST(Mappers_Government_IdeologyMappingTests, SupportedIdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::IdeologyMappingFactory().importIdeologyMapping(input);

	ASSERT_TRUE(mapping->supportedIdeology.empty());
}


TEST(Mappers_Government_IdeologyMappingTests, SupportedIdeologyCanBeImported)
{
	std::stringstream input;
	input << "supported_ideology = test_ideology";

	const auto mapping = Mappers::IdeologyMappingFactory().importIdeologyMapping(input);

	ASSERT_EQ("test_ideology", mapping->supportedIdeology);
}