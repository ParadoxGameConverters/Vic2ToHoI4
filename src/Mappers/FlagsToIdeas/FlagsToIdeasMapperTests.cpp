#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "src/Mappers/FlagsToIdeas/FlagsToIdeasMapperFactory.h"



TEST(Mappers_FlagsToIdeas_FlagToIdeaMapperTests, unmatchedFlagReturnEmptyOptional)
{
	const auto theMapper = Mappers::FlagsToIdeasMapper::Factory().importFlagsToIdeaMapper();

	ASSERT_EQ(theMapper->getIdea("unmatched_flag"), std::nullopt);
}


TEST(Mappers_FlagsToIdeas_FlagToIdeaMapperTests, matchedFlagReturnsIdea)
{
	const auto theMapper = Mappers::FlagsToIdeasMapper::Factory().importFlagsToIdeaMapper();

	ASSERT_EQ(*theMapper->getIdea("theFlag"), "theIdea");
}