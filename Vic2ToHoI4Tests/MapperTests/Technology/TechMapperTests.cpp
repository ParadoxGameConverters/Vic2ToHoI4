#include "Mappers/Technology/TechMapper.h"
#include "Mappers/Technology/TechMapperFactory.h"
#include "gtest/gtest.h"



TEST(Mappers_TechMapperTests, techsMappingsCanBeImported)
{
	const auto techMapper = Mappers::TechMapper::Factory{}.importTechMapper();

	ASSERT_EQ(7, techMapper->getTechMappings().size());
	ASSERT_EQ(1, techMapper->getTechMappings()[0].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[0].getVic2Requirements().contains("Vic2_tech"));
	ASSERT_TRUE(techMapper->getTechMappings()[0].getLimit().empty());
	ASSERT_EQ(2, techMapper->getTechMappings()[0].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[0].getTechs().contains("HoI4_tech1"));
	ASSERT_TRUE(techMapper->getTechMappings()[0].getTechs().contains("HoI4_tech2"));

	// et cetera
}