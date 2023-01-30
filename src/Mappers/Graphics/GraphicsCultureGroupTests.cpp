#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include "src/Mappers/Graphics/GraphicsCultureGroup.h"
#include "src/Mappers/Graphics/GraphicsCultureGroupFactory.h"
#include <sstream>



TEST(Mappers_Graphics_GraphicsCultureGroupTests, DefaultsAreProperlySet)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	EXPECT_TRUE(graphicsCultureGroup->getCulturesAndGroups().empty());
	EXPECT_TRUE(graphicsCultureGroup->getArmyPortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getNavyPortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getMaleMonarchPortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getFemaleMonarchPortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getLeaderPortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getFemalePortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getIdeologyMinisterPortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getMaleOperativePortraits().empty());
	EXPECT_TRUE(graphicsCultureGroup->getGraphicalCulture().empty());
	EXPECT_TRUE(graphicsCultureGroup->getGraphicalCulture2D().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, ItemsCanBeImported)
{
	std::stringstream input;
	input << "cultures_and_groups = { test_culture test_culture_group }\n";
	input << "army_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";
	input << "navy_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";
	input << "male_monarch_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";
	input << "female_monarch_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";
	input << "leader_portraits = {\n";
	input << "\ttest_ideology = {\n";
	input << "\t\tpath/test_portrait.dds\n";
	input << "\t\tpath/test_portrait2.dds\n";
	input << "\t}\n";
	input << "\ttest_ideology2 = {\n";
	input << "\t\tpath/test_portrait3.dds\n";
	input << "\t\tpath/test_portrait4.dds\n";
	input << "\t}\n";
	input << "}";
	input << "female_portraits = {\n";
	input << "\ttest_type = {\n";
	input << "\t\tpath/test_portraitF.dds\n";
	input << "\t\tpath/test_portraitF2.dds\n";
	input << "\t}\n";
	input << "\ttest_type2 = {\n";
	input << "\t\tpath/test_portraitF3.dds\n";
	input << "\t\tpath/test_portraitF4.dds\n";
	input << "\t}\n";
	input << "}";
	input << "ideology_minister_portraits = {\n";
	input << "\ttest_ideology = {\n";
	input << "\t\tpath/test_portrait.dds\n";
	input << "\t\tpath/test_portrait2.dds\n";
	input << "\t}\n";
	input << "\ttest_ideology2 = {\n";
	input << "\t\tpath/test_portrait3.dds\n";
	input << "\t\tpath/test_portrait4.dds\n";
	input << "\t}\n";
	input << "}";
	input << "male_operative_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";
	input << "graphical_culture = test_culture_group\n";
	input << "graphical_culture_2d = test_culture_group";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	EXPECT_THAT(graphicsCultureGroup->getCulturesAndGroups(),
		 testing::ElementsAre("test_culture", "test_culture_group"));
	EXPECT_THAT(graphicsCultureGroup->getArmyPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
	EXPECT_THAT(graphicsCultureGroup->getNavyPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
	EXPECT_THAT(graphicsCultureGroup->getMaleMonarchPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
	EXPECT_THAT(graphicsCultureGroup->getFemaleMonarchPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
	EXPECT_THAT(graphicsCultureGroup->getLeaderPortraits(),
		 testing::UnorderedElementsAre(
			  testing::Pair("test_ideology",
					testing::UnorderedElementsAre("path/test_portrait.dds", "path/test_portrait2.dds")),
			  testing::Pair("test_ideology2",
					testing::UnorderedElementsAre("path/test_portrait3.dds", "path/test_portrait4.dds"))));
	EXPECT_THAT(graphicsCultureGroup->getFemalePortraits(),
		 testing::UnorderedElementsAre(
			  testing::Pair("test_type",
					testing::UnorderedElementsAre("path/test_portraitF.dds", "path/test_portraitF2.dds")),
			  testing::Pair("test_type2",
					testing::UnorderedElementsAre("path/test_portraitF3.dds", "path/test_portraitF4.dds"))));
	EXPECT_THAT(graphicsCultureGroup->getIdeologyMinisterPortraits(),
		 testing::UnorderedElementsAre(
			  testing::Pair("test_ideology",
					testing::UnorderedElementsAre("path/test_portrait.dds", "path/test_portrait2.dds")),
			  testing::Pair("test_ideology2",
					testing::UnorderedElementsAre("path/test_portrait3.dds", "path/test_portrait4.dds"))));
	EXPECT_THAT(graphicsCultureGroup->getMaleOperativePortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
	EXPECT_EQ("test_culture_group", graphicsCultureGroup->getGraphicalCulture());
	EXPECT_EQ("test_culture_group", graphicsCultureGroup->getGraphicalCulture2D());
}