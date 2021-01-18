#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapperFactory.h"
#include "gtest/gtest.h"



TEST(Mappers_FlagsToIdeas_FlagToIdeaMapperTests, unmatchedFlagReturnEmptyOptional)
{
	const auto theMapper = Mappers::FlagsToIdeasMapper::Factory().importFlagsToIdeaMapper();

	ASSERT_FALSE(theMapper->getIdea("unmatched_flag"));
}


TEST(Mappers_FlagsToIdeas_FlagToIdeaMapperTests, matchedFlagReturnsIdea)
{
	const auto theMapper = Mappers::FlagsToIdeasMapper::Factory().importFlagsToIdeaMapper();

	ASSERT_EQ(*theMapper->getIdea("theFlag"), "theIdea");
}