#include "Configuration.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Mappers/Graphics/GraphicsMapperFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



class Mappers_Graphics_GraphicsMapperTests: public testing::Test
{
  protected:
	Mappers_Graphics_GraphicsMapperTests(): graphicsMapper(Mappers::GraphicsMapper::Factory().importGraphicsMapper()) {}

	std::unique_ptr<Mappers::GraphicsMapper> graphicsMapper;
};


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedArmyPortraitsAreEmpty)
{
	ASSERT_TRUE(graphicsMapper->getArmyPortraits("nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedArmyPortraitsAreReturned)
{
	ASSERT_THAT(graphicsMapper->getArmyPortraits("test_culture_group"),
		 testing::ElementsAre("path/test_army_portrait.dds", "path/test_army_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedNavyPortraitsAreEmpty)
{
	ASSERT_TRUE(graphicsMapper->getNavyPortraits("nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedNavyPortraitsAreReturned)
{
	ASSERT_THAT(graphicsMapper->getNavyPortraits("test_culture_group"),
		 testing::ElementsAre("path/test_navy_portrait.dds", "path/test_navy_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedMaleMonarchPortraitsAreEmpty)
{
	ASSERT_TRUE(graphicsMapper->getMaleMonarchPortraits("nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedMaleMonarchPortraitsAreReturned)
{
	ASSERT_THAT(graphicsMapper->getMaleMonarchPortraits("test_culture_group"),
		 testing::ElementsAre("path/test_male_monarch_portrait.dds", "path/test_male_monarch_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedFemaleMonarchPortraitsAreEmpty)
{
	ASSERT_TRUE(graphicsMapper->getFemaleMonarchPortraits("nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedFemaleMonarchPortraitsAreReturned)
{
	ASSERT_THAT(graphicsMapper->getFemaleMonarchPortraits("test_culture_group"),
		 testing::ElementsAre("path/test_female_monarch_portrait.dds", "path/test_female_monarch_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedLeaderPortraitsAreDefault)
{
	ASSERT_EQ("gfx/leaders/leader_unknown.dds",
		 graphicsMapper->getLeaderPortrait("nonexistent_culture_group", "good_ideology"));
	ASSERT_EQ("gfx/leaders/leader_unknown.dds",
		 graphicsMapper->getLeaderPortrait("test_culture_group", "missing_ideology"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedLeaderPortraitsAreReturned)
{
	std::set<std::string> leaderPortraits;
	leaderPortraits.insert(graphicsMapper->getLeaderPortrait("test_culture_group", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getLeaderPortrait("test_culture_group", "good_ideology"));

	ASSERT_THAT(leaderPortraits,
		 testing::UnorderedElementsAre("gfx/leaders/test_leader_portrait.dds", "gfx/leaders/test_leader_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedIdeologyMinisterPortraitsAreDefault)
{
	ASSERT_EQ("gfx/interface/ideas/idea_unknown.dds",
		 graphicsMapper->getIdeologyMinisterPortrait("nonexistent_culture_group", "good_ideology"));
	ASSERT_EQ("gfx/interface/ideas/idea_unknown.dds",
		 graphicsMapper->getIdeologyMinisterPortrait("test_culture_group", "missing_ideology"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedIdeologyMinisterPortraitsAreReturned)
{
	std::set<std::string> leaderPortraits;
	leaderPortraits.insert(graphicsMapper->getIdeologyMinisterPortrait("test_culture_group", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getIdeologyMinisterPortrait("test_culture_group", "good_ideology"));

	ASSERT_THAT(leaderPortraits,
		 testing::UnorderedElementsAre("gfx/interface/ideas/test_minister_portrait.dds",
			  "gfx/interface/ideas/test_minister_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedMaleOperativePortraitsAreEmpty)
{
	ASSERT_TRUE(graphicsMapper->getMaleOperativePortraits("nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedMaleOperativePortraitsAreReturned)
{
	ASSERT_THAT(graphicsMapper->getMaleOperativePortraits("test_culture_group"),
		 testing::ElementsAre("path/test_male_operative_portrait.dds", "path/test_male_operative_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedFemaleOperativePortraitsAreEmpty)
{
	ASSERT_TRUE(graphicsMapper->getFemaleOperativePortraits("nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedFemaleOperativePortraitsAreReturned)
{
	ASSERT_THAT(graphicsMapper->getFemaleOperativePortraits("test_culture_group"),
		 testing::ElementsAre("path/test_female_operative_portrait.dds", "path/test_female_operative_portrait2.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedGraphicalCultureIsNullopt)
{
	ASSERT_EQ(std::nullopt, graphicsMapper->getGraphicalCulture("nonexistent_culture_group"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedGraphicalCultureIsReturned)
{
	ASSERT_EQ("test_graphical_culture", graphicsMapper->getGraphicalCulture("test_culture_group"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, Unmatched2dGraphicalCultureIsNullopt)
{
	ASSERT_EQ(std::nullopt, graphicsMapper->get2dGraphicalCulture("nonexistent_culture_group"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, Matched2dGraphicalCultureIsReturned)
{
	ASSERT_EQ("test_graphical_culture_2d", graphicsMapper->get2dGraphicalCulture("test_culture_group"));
}