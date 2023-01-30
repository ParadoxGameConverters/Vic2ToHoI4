#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Ideology/IdeologyMapper.h"
#include "src/Mappers/Ideology/IdeologyMapperFactory.h"



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