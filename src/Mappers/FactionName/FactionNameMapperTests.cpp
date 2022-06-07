#include "src/Mappers/FactionName/FactionNameMapperFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>


TEST(Mappers_FactionName_FactionNameMapperTests, MatchingCultureMatchingIdeology)
{
	const auto mapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();

	ASSERT_EQ("matching_culture_matching_ideology", mapper->getFactionName("test_ideology", "test_culture", "ignored"));
}


TEST(Mappers_FactionName_FactionNameMapperTests, MatchingCultureGroupMatchingIdeology)
{
	const auto mapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();

	ASSERT_EQ("matching_culture_group_matching_ideology",
		 mapper->getFactionName("test_ideology", "ignored", "test_culture_group"));
}



TEST(Mappers_FactionName_FactionNameMapperTests, AnyCultureMatchingIdeology)
{
	const auto mapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();

	ASSERT_EQ("any_culture_matching_ideology", mapper->getFactionName("test_ideology", "ignored", "ignored"));
}


TEST(Mappers_FactionName_FactionNameMapperTests, MatchingCultureAnyIdeology)
{
	const auto mapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();

	ASSERT_EQ("matching_culture_any_ideology", mapper->getFactionName("ignored", "test_culture", "ignored"));
}

TEST(Mappers_FactionName_FactionNameMapperTests, AnyCultureAnyIdeology)
{
	const auto mapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();

	ASSERT_EQ("any_culture_any_ideology", mapper->getFactionName("ignored", "ignored", "ignored"));
}

TEST(Mappers_FactionName_FactionNameMapperTests, DuplicateRemoval)
{
	const auto mapper = Mappers::FactionNameMapper::Factory().importFactionNameMapper();

	std::ignore = mapper->getFactionName("duplicate_test", "duplicate_test", "duplicate_test");
	ASSERT_EQ("any_culture_any_ideology", mapper->getFactionName("duplicate_test", "ignored", "ignored"));
}