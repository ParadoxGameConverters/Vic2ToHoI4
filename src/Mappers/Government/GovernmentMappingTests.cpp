#include "src/Mappers/Government/GovernmentMapping.h"
#include "src/Mappers/Government/GovernmentMappingFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Government_GovernmentMappingTests, Vic2GovernmentDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->vic2Government.empty());
}


TEST(Mappers_Government_GovernmentMappingTests, Vic2GovernmentCanBeImported)
{
	std::stringstream input;
	input << "vic_government = test_government";

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_EQ("test_government", mapping->vic2Government);
}


TEST(Mappers_Government_GovernmentMappingTests, RequiredTagDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->tagRequired.empty());
}


TEST(Mappers_Government_GovernmentMappingTests, RequiredTagCanBeImported)
{
	std::stringstream input;
	input << "vic_tag = TAG";

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_EQ("TAG", mapping->tagRequired);
}


TEST(Mappers_Government_GovernmentMappingTests, HoI4GovernmentDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->hoI4GovernmentIdeology.empty());
}


TEST(Mappers_Government_GovernmentMappingTests, HoI4GovernmentCanBeImported)
{
	std::stringstream input;
	input << "hoi_gov = test_government";

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_EQ("test_government", mapping->hoI4GovernmentIdeology);
}


TEST(Mappers_Government_GovernmentMappingTests, HoI4LeaerIdeologyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->hoI4LeaderIdeology.empty());
}


TEST(Mappers_Government_GovernmentMappingTests, HoI4LeaerIdeologyCanBeImported)
{
	std::stringstream input;
	input << "hoi_leader = test_ideology";

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_EQ("test_ideology", mapping->hoI4LeaderIdeology);
}


TEST(Mappers_Government_GovernmentMappingTests, RequiredRulingPartyDefaultsToEmpty)
{
	std::stringstream input;

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->rulingPartyRequired.empty());
}


TEST(Mappers_Government_GovernmentMappingTests, RequiredRulingPartyCanBeImported)
{
	std::stringstream input;
	input << "ruling_party = test_party";

	const auto mapping = Mappers::GovernmentMappingFactory().importMapping(input);

	ASSERT_EQ("test_party", mapping->rulingPartyRequired);
}