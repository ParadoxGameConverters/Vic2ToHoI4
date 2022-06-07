#include "src/Mappers/Technology/ResearchBonusMapper.h"
#include "src/Mappers/Technology/ResearchBonusMapperFactory.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(Mappers_ResearchBonusMapperTests, researchBonusesCanBeImported)
{
	const auto researchBonusMapper = Mappers::ResearchBonusMapper::Factory().importResearchBonusMapper();

	ASSERT_EQ(3, researchBonusMapper->getResearchBonusMappings().size());

	EXPECT_THAT(researchBonusMapper->getResearchBonusMappings()[0].getVic2Requirements(),
		 testing::UnorderedElementsAre("Vic2_tech"));
	EXPECT_THAT(researchBonusMapper->getResearchBonusMappings()[0].getResearchBonuses(),
		 testing::UnorderedElementsAre(testing::Pair("bonus1_doctrine", 5.5F), testing::Pair("bonus2_doctrine", 6.6F)));

	EXPECT_THAT(researchBonusMapper->getResearchBonusMappings()[1].getVic2Requirements(),
		 testing::UnorderedElementsAre("Vic2_invention"));
	EXPECT_THAT(researchBonusMapper->getResearchBonusMappings()[1].getResearchBonuses(),
		 testing::UnorderedElementsAre(testing::Pair("bonus2_doctrine", 6.6F), testing::Pair("bonus3_doctrine", 7.7F)));

	EXPECT_THAT(researchBonusMapper->getResearchBonusMappings()[2].getVic2Requirements(),
		 testing::UnorderedElementsAre("Vic2_invention", "Vic2_invention2"));
	EXPECT_THAT(researchBonusMapper->getResearchBonusMappings()[2].getResearchBonuses(),
		 testing::UnorderedElementsAre(testing::Pair("bonus4_doctrine", 8.8F)));
}