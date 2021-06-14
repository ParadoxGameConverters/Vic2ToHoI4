#include "Configuration.h"
#include "Mappers/Graphics/GraphicsCultureGroup.h"
#include "Mappers/Graphics/GraphicsCultureGroupFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Graphics_GraphicsCultureGroupTests, ArmyPortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getArmyPortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, ArmyPortraitsCanBeImported)
{
	std::stringstream input;
	input << "army_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getArmyPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, NavyPortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getNavyPortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, NavyPortraitsCanBeImported)
{
	std::stringstream input;
	input << "navy_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getNavyPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, MaleMonarchPortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getMaleMonarchPortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, MaleMonarchPortraitsCanBeImported)
{
	std::stringstream input;
	input << "male_monarch_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getMaleMonarchPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, FemaleMonarchPortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getFemaleMonarchPortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, FemaleMonarchPortraitsCanBeImported)
{
	std::stringstream input;
	input << "female_monarch_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getFemaleMonarchPortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, LeaderPortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getLeaderPortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, LeaderPortraitsCanBeImported)
{
	std::stringstream input;
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

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getLeaderPortraits(),
		 testing::UnorderedElementsAre(
			  testing::Pair("test_ideology",
					testing::UnorderedElementsAre("path/test_portrait.dds", "path/test_portrait2.dds")),
			  testing::Pair("test_ideology2",
					testing::UnorderedElementsAre("path/test_portrait3.dds", "path/test_portrait4.dds"))));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, IdeologyMinisterPortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getIdeologyMinisterPortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, IdeologyMinisterPortraitsCanBeImported)
{
	std::stringstream input;
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

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getIdeologyMinisterPortraits(),
		 testing::UnorderedElementsAre(
			  testing::Pair("test_ideology",
					testing::UnorderedElementsAre("path/test_portrait.dds", "path/test_portrait2.dds")),
			  testing::Pair("test_ideology2",
					testing::UnorderedElementsAre("path/test_portrait3.dds", "path/test_portrait4.dds"))));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, MaleOperativePortraitsDefaultToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getMaleOperativePortraits().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, MaleOperativePortraitsCanBeImported)
{
	std::stringstream input;
	input << "male_operative_portraits = {\n";
	input << "\tpath/test_portrait.dds\n";
	input << "\tpath/test_portrait2.dds\n";
	input << "}";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_THAT(graphicsCultureGroup->getMaleOperativePortraits(),
		 testing::ElementsAre("path/test_portrait.dds", "path/test_portrait2.dds"));
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, GraphicalCultureDefaultsToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getGraphicalCulture().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, GraphicalCultureCanBeImported)
{
	std::stringstream input;
	input << "graphical_culture = test_culture_group";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_EQ("test_culture_group", graphicsCultureGroup->getGraphicalCulture());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, GraphicalCulture2DDefaultsToEmpty)
{
	std::stringstream input;

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_TRUE(graphicsCultureGroup->getGraphicalCulture2D().empty());
}


TEST(Mappers_Graphics_GraphicsCultureGroupTests, GraphicalCulture2DCanBeImported)
{
	std::stringstream input;
	input << "graphical_culture_2d = test_culture_group";

	const auto graphicsCultureGroup = Mappers::GraphicsCultureGroup::Factory().importCultureGroup(input);

	ASSERT_EQ("test_culture_group", graphicsCultureGroup->getGraphicalCulture2D());
}