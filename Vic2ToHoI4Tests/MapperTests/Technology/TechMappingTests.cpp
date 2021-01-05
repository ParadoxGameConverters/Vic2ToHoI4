#include <gmock/gmock-matchers.h>

#include "Mappers/Technology/TechMapping.h"
#include "Mappers/Technology/TechMappingFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_AI_Strategy_Tests, Vic2ItemDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::TechMapping::Factory{}.importTechMapping(input);

	ASSERT_TRUE(mapping->getVic2Item().empty());
}


TEST(Vic2World_AI_Strategy_Tests, Vic2ItemCanBeSet)
{
	std::stringstream input;
	input << "vic2 = test_item";
	const auto mapping = Mappers::TechMapping::Factory{}.importTechMapping(input);

	ASSERT_EQ("test_item", mapping->getVic2Item());
}


TEST(Vic2World_AI_Strategy_Tests, LimitDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::TechMapping::Factory{}.importTechMapping(input);

	ASSERT_TRUE(mapping->getLimit().empty());
}


TEST(Vic2World_AI_Strategy_Tests, LimitCanBeSet)
{
	std::stringstream input;
	input << "limit = test_limit";
	const auto mapping = Mappers::TechMapping::Factory{}.importTechMapping(input);

	ASSERT_EQ("test_limit", mapping->getLimit());
}


TEST(Vic2World_AI_Strategy_Tests, TechsDefaultToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::TechMapping::Factory{}.importTechMapping(input);

	ASSERT_TRUE(mapping->getTechs().empty());
}


TEST(Vic2World_AI_Strategy_Tests, TechsCanBeSet)
{
	std::stringstream input;
	input << "hoi4 = test_tech\n";
	input << "hoi4 = test_tech2";
	const auto mapping = Mappers::TechMapping::Factory{}.importTechMapping(input);

	ASSERT_THAT(mapping->getTechs(), testing::UnorderedElementsAre("test_tech", "test_tech2"));
}