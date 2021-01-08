#include "Mappers/Technology/ResearchBonusMapper.h"
#include "Mappers/Technology/ResearchBonusMapperFactory.h"
#include "gtest/gtest.h"



TEST(Mappers_ResearchBonusMapperTests, researchBonusesCanBeImported)
{
	const auto researchBonusMapper = Mappers::ResearchBonusMapper::Factory{}.importResearchBonusMapper();

	ASSERT_EQ(3, researchBonusMapper->getResearchBonusMappings().size());
	ASSERT_EQ(1, researchBonusMapper->getResearchBonusMappings()[0].getVic2Requirements().size());
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[0].getVic2Requirements().contains("Vic2_tech"));
	ASSERT_EQ(2, researchBonusMapper->getResearchBonusMappings()[0].getResearchBonuses().size());
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[0].getResearchBonuses().contains("bonus1_doctrine"));
	ASSERT_EQ(50, researchBonusMapper->getResearchBonusMappings()[0].getResearchBonuses().at("bonus1_doctrine"));
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[0].getResearchBonuses().contains("bonus2_doctrine"));
	ASSERT_EQ(60, researchBonusMapper->getResearchBonusMappings()[0].getResearchBonuses().at("bonus2_doctrine"));

	ASSERT_EQ(1, researchBonusMapper->getResearchBonusMappings()[1].getVic2Requirements().size());
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[1].getVic2Requirements().contains("Vic2_invention"));
	ASSERT_EQ(2, researchBonusMapper->getResearchBonusMappings()[1].getResearchBonuses().size());
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[1].getResearchBonuses().contains("bonus2_doctrine"));
	ASSERT_EQ(60, researchBonusMapper->getResearchBonusMappings()[1].getResearchBonuses().at("bonus2_doctrine"));
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[1].getResearchBonuses().contains("bonus3_doctrine"));
	ASSERT_EQ(70, researchBonusMapper->getResearchBonusMappings()[1].getResearchBonuses().at("bonus3_doctrine"));

	ASSERT_EQ(2, researchBonusMapper->getResearchBonusMappings()[2].getVic2Requirements().size());
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[2].getVic2Requirements().contains("Vic2_invention"));
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[2].getVic2Requirements().contains("Vic2_invention2"));
	ASSERT_EQ(1, researchBonusMapper->getResearchBonusMappings()[2].getResearchBonuses().size());
	ASSERT_TRUE(researchBonusMapper->getResearchBonusMappings()[2].getResearchBonuses().contains("bonus4_doctrine"));
	ASSERT_EQ(80, researchBonusMapper->getResearchBonusMappings()[2].getResearchBonuses().at("bonus4_doctrine"));
}