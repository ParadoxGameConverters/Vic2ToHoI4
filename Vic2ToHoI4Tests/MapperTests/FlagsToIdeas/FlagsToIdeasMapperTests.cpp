#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapperFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_FlagsToIdeas_FlagToIdeaMapperTests, unmatchedFlagReturnEmptyOptional)
{
	std::stringstream input;

	const auto theMapper = Mappers::FlagsToIdeasMapper::Factory().getFlagsToIdeaMapper(input);

	ASSERT_FALSE(theMapper->getIdea("unmatched_flag"));
}


TEST(Mappers_FlagsToIdeas_FlagToIdeaMapperTests, matchedFlagReturnsIdea)
{
	std::stringstream input;
	input << "mapping = { flag = theFlag idea = theIdea }";

	const auto theMapper = Mappers::FlagsToIdeasMapper::Factory().getFlagsToIdeaMapper(input);

	ASSERT_EQ(*theMapper->getIdea("theFlag"), "theIdea");
}