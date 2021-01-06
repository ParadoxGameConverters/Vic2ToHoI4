#include "Mappers/Technology/TechMapper.h"
#include "Mappers/Technology/TechMapperFactory.h"
#include "Mappers/Technology/TechMappingBuilder.h"
#include "gtest/gtest.h"



TEST(Mappers_TechMapperTests, techsCanBeImported)
{
	const auto techMapper = Mappers::TechMapper::Factory{}.importTechMapper();

	ASSERT_EQ(7, techMapper->getAllTechMappings().size());
	ASSERT_EQ(1, techMapper->getAllTechMappings()[0].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getAllTechMappings()[0].getVic2Requirements().contains("Vic2_tech"));
	ASSERT_TRUE(techMapper->getAllTechMappings()[0].getLimit().empty());
	ASSERT_EQ(2, techMapper->getAllTechMappings()[0].getTechs().size());
	ASSERT_TRUE(techMapper->getAllTechMappings()[0].getTechs().contains("HoI4_tech1"));
	ASSERT_TRUE(techMapper->getAllTechMappings()[0].getTechs().contains("HoI4_tech2"));

	// et cetera
}