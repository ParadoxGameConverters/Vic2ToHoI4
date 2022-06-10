#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Technology/TechMapping.h"
#include "src/Mappers/Technology/TechMappingFactory.h"



TEST(Mappers_TechMappingTests, Vic2RequirementsDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::TechMapping::Factory().importTechMapping(input);

	ASSERT_TRUE(mapping->getVic2Requirements().empty());
}


TEST(Mappers_TechMappingTests, Vic2RequirementsCanBeSet)
{
	std::stringstream input;
	input << "vic2 = test_item\n";
	input << "vic2 = test_item2";
	const auto mapping = Mappers::TechMapping::Factory().importTechMapping(input);

	ASSERT_THAT(mapping->getVic2Requirements(), testing::UnorderedElementsAre("test_item", "test_item2"));
}


TEST(Mappers_TechMappingTests, LimitDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::TechMapping::Factory().importTechMapping(input);

	ASSERT_TRUE(mapping->getLimit().empty());
}


TEST(Mappers_TechMappingTests, LimitCanBeSet)
{
	std::stringstream input;
	input << "limit = test_limit";
	const auto mapping = Mappers::TechMapping::Factory().importTechMapping(input);

	ASSERT_EQ("test_limit", mapping->getLimit());
}


TEST(Mappers_TechMappingTests, TechsDefaultToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::TechMapping::Factory().importTechMapping(input);

	ASSERT_TRUE(mapping->getTechs().empty());
}


TEST(Mappers_TechMappingTests, TechsCanBeSet)
{
	std::stringstream input;
	input << "hoi4 = test_tech\n";
	input << "hoi4 = test_tech2";
	const auto mapping = Mappers::TechMapping::Factory().importTechMapping(input);

	ASSERT_THAT(mapping->getTechs(), testing::UnorderedElementsAre("test_tech", "test_tech2"));
}