#include "Mappers/Ideology/IdeologyMapper.h"
#include "Mappers/Ideology/IdeologyMapperFactory.h"
#include "gtest/gtest.h"



TEST(Mappers_Government_IdeologyMapperTests, IdeologyCanBeMatched)
{
	const auto mapper = Mappers::IdeologyMapper::Factory().importIdeologyMapper();

	ASSERT_EQ("matched_ideology",
		 mapper->getSupportedIdeology("ruling_ideology", "vic2_ideology", {"matched_ideology"}));
}


TEST(Mappers_Government_IdeologyMapperTests, MissingMajorIdeologyMeansNoMatch)
{
	const auto mapper = Mappers::IdeologyMapper::Factory().importIdeologyMapper();

	ASSERT_EQ("neutrality", mapper->getSupportedIdeology("ruling_ideology", "vic2_ideology", {}));
}


TEST(Mappers_Government_IdeologyMapperTests, WrongVic2IdeologyMeansNoMatch)
{
	const auto mapper = Mappers::IdeologyMapper::Factory().importIdeologyMapper();

	ASSERT_EQ("neutrality", mapper->getSupportedIdeology("ruling_ideology", "other_ideology", {"matched_ideology"}));
}


TEST(Mappers_Government_IdeologyMapperTests, WrongRulingIdeologyMeansNoMatch)
{
	const auto mapper = Mappers::IdeologyMapper::Factory().importIdeologyMapper();

	ASSERT_EQ("neutrality", mapper->getSupportedIdeology("other_ideology", "vic2_ideology", {"matched_ideology"}));
}