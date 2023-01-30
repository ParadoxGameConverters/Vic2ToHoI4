#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/FlagsToIdeas/FlagToIdeaMapping.h"
#include "src/Mappers/FlagsToIdeas/FlagToIdeaMappingFactory.h"
#include <sstream>



TEST(Mappers_FlagsToIdeas_FlagToIdeaMappingTests, flagDefaultsToEmpty)
{
	std::stringstream input;

	const auto theMapping = Mappers::FlagToIdeaMapping::Factory().importFlagToIdeaMapping(input);

	ASSERT_TRUE(theMapping->getFlag().empty());
}


TEST(Mappers_FlagsToIdeas_FlagToIdeaMappingTests, flagCanBeSetEmpty)
{
	std::stringstream input;
	input << "flag = theFlag";

	const auto theMapping = Mappers::FlagToIdeaMapping::Factory().importFlagToIdeaMapping(input);

	ASSERT_EQ(theMapping->getFlag(), "theFlag");
}


TEST(Mappers_FlagsToIdeas_FlagToIdeaMappingTests, ideaDefaultsToEmpty)
{
	std::stringstream input;

	const auto theMapping = Mappers::FlagToIdeaMapping::Factory().importFlagToIdeaMapping(input);

	ASSERT_TRUE(theMapping->getIdea().empty());
}


TEST(Mappers_FlagsToIdeas_FlagToIdeaMappingTests, ideaCanBeSetEmpty)
{
	std::stringstream input;
	input << "idea = theIdea";

	const auto theMapping = Mappers::FlagToIdeaMapping::Factory().importFlagToIdeaMapping(input);

	ASSERT_EQ(theMapping->getIdea(), "theIdea");
}