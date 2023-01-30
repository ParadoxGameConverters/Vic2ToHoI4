#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Technology/TechMapper.h"
#include "src/Mappers/Technology/TechMapperFactory.h"



TEST(Mappers_TechMapperTests, techsMappingsCanBeImported)
{
	const auto techMapper = Mappers::TechMapper::Factory().importTechMapper();

	ASSERT_EQ(7, techMapper->getTechMappings().size());

	ASSERT_EQ(1, techMapper->getTechMappings()[0].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[0].getVic2Requirements().contains("Vic2_tech"));
	ASSERT_TRUE(techMapper->getTechMappings()[0].getLimit().empty());
	ASSERT_EQ(2, techMapper->getTechMappings()[0].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[0].getTechs().contains("HoI4_tech1"));
	ASSERT_TRUE(techMapper->getTechMappings()[0].getTechs().contains("HoI4_tech2"));

	ASSERT_EQ(1, techMapper->getTechMappings()[1].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[1].getVic2Requirements().contains("Vic2_invention"));
	ASSERT_TRUE(techMapper->getTechMappings()[1].getLimit().empty());
	ASSERT_EQ(2, techMapper->getTechMappings()[1].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[1].getTechs().contains("HoI4_tech2"));
	ASSERT_TRUE(techMapper->getTechMappings()[1].getTechs().contains("HoI4_tech3"));

	ASSERT_EQ(1, techMapper->getTechMappings()[2].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[2].getVic2Requirements().contains("Vic2_nonMtgNavalTech"));
	ASSERT_EQ("not = { has_dlc = \"Man the Guns\" }", techMapper->getTechMappings()[2].getLimit());
	ASSERT_EQ(2, techMapper->getTechMappings()[2].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[2].getTechs().contains("HoI4_nonMtgNavalTech1"));
	ASSERT_TRUE(techMapper->getTechMappings()[2].getTechs().contains("HoI4_nonMtgNavalTech2"));

	ASSERT_EQ(1, techMapper->getTechMappings()[3].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[3].getVic2Requirements().contains("Vic2_nonMtgNavalInvention"));
	ASSERT_EQ("not = { has_dlc = \"Man the Guns\" }", techMapper->getTechMappings()[3].getLimit());
	ASSERT_EQ(2, techMapper->getTechMappings()[3].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[3].getTechs().contains("HoI4_nonMtgNavalTech2"));
	ASSERT_TRUE(techMapper->getTechMappings()[3].getTechs().contains("HoI4_nonMtgNavalTech3"));

	ASSERT_EQ(1, techMapper->getTechMappings()[4].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[4].getVic2Requirements().contains("Vic2_mtgNavalTech"));
	ASSERT_EQ("has_dlc = \"Man the Guns\"", techMapper->getTechMappings()[4].getLimit());
	ASSERT_EQ(2, techMapper->getTechMappings()[4].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[4].getTechs().contains("HoI4_mtgNavalTech1"));
	ASSERT_TRUE(techMapper->getTechMappings()[4].getTechs().contains("HoI4_mtgNavalTech2"));

	ASSERT_EQ(1, techMapper->getTechMappings()[5].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[5].getVic2Requirements().contains("Vic2_mtgNavalInvention"));
	ASSERT_EQ("has_dlc = \"Man the Guns\"", techMapper->getTechMappings()[5].getLimit());
	ASSERT_EQ(2, techMapper->getTechMappings()[5].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[5].getTechs().contains("HoI4_mtgNavalTech2"));
	ASSERT_TRUE(techMapper->getTechMappings()[5].getTechs().contains("HoI4_mtgNavalTech3"));

	ASSERT_EQ(2, techMapper->getTechMappings()[6].getVic2Requirements().size());
	ASSERT_TRUE(techMapper->getTechMappings()[6].getVic2Requirements().contains("requirement1"));
	ASSERT_TRUE(techMapper->getTechMappings()[6].getVic2Requirements().contains("requirement2"));
	ASSERT_TRUE(techMapper->getTechMappings()[6].getLimit().empty());
	ASSERT_EQ(2, techMapper->getTechMappings()[6].getTechs().size());
	ASSERT_TRUE(techMapper->getTechMappings()[6].getTechs().contains("test_tech1"));
	ASSERT_TRUE(techMapper->getTechMappings()[6].getTechs().contains("test_tech2"));
}