#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include "src/Mappers/Graphics/GraphicsMapper.h"
#include "src/Mappers/Graphics/GraphicsMapperFactory.h"



class Mappers_Graphics_GraphicsMapperTests: public testing::Test
{
  protected:
	Mappers_Graphics_GraphicsMapperTests(): graphicsMapper(Mappers::GraphicsMapper::Factory().importGraphicsMapper()) {}

	std::unique_ptr<Mappers::GraphicsMapper> graphicsMapper;
};


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedArmyPortraitsAreEmpty)
{
	EXPECT_TRUE(graphicsMapper->getArmyPortraits("nonexistent_culture", "nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedArmyPortraitsAreReturned)
{
	EXPECT_THAT(graphicsMapper->getArmyPortraits("", "test_culture_group"),
		 testing::ElementsAre("path/test_army_portrait.dds", "path/test_army_portrait2.dds"));
	EXPECT_THAT(graphicsMapper->getArmyPortraits("test_culture", ""),
		 testing::ElementsAre("path/test_army_portrait3.dds", "path/test_army_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getArmyPortraits("", "test_culture_group2"),
		 testing::ElementsAre("path/test_army_portrait3.dds", "path/test_army_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getArmyPortraits("", "test_culture_group3"),
		 testing::ElementsAre("path/test_army_portrait3.dds", "path/test_army_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedNavyPortraitsAreEmpty)
{
	EXPECT_TRUE(graphicsMapper->getNavyPortraits("nonexistent_culture", "nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedNavyPortraitsAreReturned)
{
	EXPECT_THAT(graphicsMapper->getNavyPortraits("", "test_culture_group"),
		 testing::ElementsAre("path/test_navy_portrait.dds", "path/test_navy_portrait2.dds"));
	EXPECT_THAT(graphicsMapper->getNavyPortraits("test_culture", ""),
		 testing::ElementsAre("path/test_navy_portrait3.dds", "path/test_navy_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getNavyPortraits("", "test_culture_group2"),
		 testing::ElementsAre("path/test_navy_portrait3.dds", "path/test_navy_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getNavyPortraits("", "test_culture_group3"),
		 testing::ElementsAre("path/test_navy_portrait3.dds", "path/test_navy_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedMaleMonarchPortraitsAreEmpty)
{
	EXPECT_TRUE(graphicsMapper->getMaleMonarchPortraits("nonexistent_culture", "nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedMaleMonarchPortraitsAreReturned)
{
	EXPECT_THAT(graphicsMapper->getMaleMonarchPortraits("", "test_culture_group"),
		 testing::ElementsAre("path/test_male_monarch_portrait.dds", "path/test_male_monarch_portrait2.dds"));
	EXPECT_THAT(graphicsMapper->getMaleMonarchPortraits("test_culture", ""),
		 testing::ElementsAre("path/test_male_monarch_portrait3.dds", "path/test_male_monarch_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getMaleMonarchPortraits("", "test_culture_group2"),
		 testing::ElementsAre("path/test_male_monarch_portrait3.dds", "path/test_male_monarch_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getMaleMonarchPortraits("", "test_culture_group3"),
		 testing::ElementsAre("path/test_male_monarch_portrait3.dds", "path/test_male_monarch_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedFemaleMonarchPortraitsAreEmpty)
{
	EXPECT_TRUE(graphicsMapper->getFemaleMonarchPortraits("nonexistent_culture", "nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedFemaleMonarchPortraitsAreReturned)
{
	EXPECT_THAT(graphicsMapper->getFemaleMonarchPortraits("", "test_culture_group"),
		 testing::ElementsAre("path/test_female_monarch_portrait.dds", "path/test_female_monarch_portrait2.dds"));
	EXPECT_THAT(graphicsMapper->getFemaleMonarchPortraits("test_culture", ""),
		 testing::ElementsAre("path/test_female_monarch_portrait3.dds", "path/test_female_monarch_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getFemaleMonarchPortraits("", "test_culture_group2"),
		 testing::ElementsAre("path/test_female_monarch_portrait3.dds", "path/test_female_monarch_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getFemaleMonarchPortraits("", "test_culture_group3"),
		 testing::ElementsAre("path/test_female_monarch_portrait3.dds", "path/test_female_monarch_portrait4.dds"));
}

TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedLeaderPortraitIsDefault)
{
	EXPECT_TRUE(graphicsMapper->getLeaderPortrait("nonexistent_culture", "nonexistent_group", "nihilism") ==
					"gfx/leaders/leader_unknown.dds");
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedLeaderPortraitIsReturned)
{
	std::set<std::string> leaderPortraits;
	leaderPortraits.insert(graphicsMapper->getLeaderPortrait("", "test_culture_group", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getLeaderPortrait("", "test_culture_group", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getLeaderPortrait("test_culture2", "", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getLeaderPortrait("", "test_culture_group2", "good_ideology"));

	EXPECT_THAT(leaderPortraits,
		 testing::UnorderedElementsAre("gfx/leaders/test_leader_portrait.dds",
			  "gfx/leaders/test_leader_portrait2.dds",
			  "gfx/leaders/test_leader_portrait3.dds",
			  "gfx/leaders/test_leader_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedLeaderPortraitsAreDefault)
{
	EXPECT_EQ("gfx/leaders/leader_unknown.dds",
		 graphicsMapper->getLeaderPortrait("nonexistent_culture", "nonexistent_culture_group", "good_ideology"));
	EXPECT_EQ("gfx/leaders/leader_unknown.dds",
		 graphicsMapper->getLeaderPortrait("", "test_culture_group", "missing_ideology"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedLeaderPortraitsAreReturned)
{
	std::set<std::string> leaderPortraits;
	for (const auto& portrait: graphicsMapper->getLeaderPortraits("", "test_culture_group", "good_ideology"))
	{
		leaderPortraits.insert(portrait);
	}
	for (const auto& portrait: graphicsMapper->getLeaderPortraits("", "test_culture_group2", "good_ideology"))
	{
		leaderPortraits.insert(portrait);
	}
	for (const auto& portrait: graphicsMapper->getLeaderPortraits("test_culture2", "", "good_ideology"))
	{
		leaderPortraits.insert(portrait);
	}

	EXPECT_THAT(leaderPortraits,
		 testing::UnorderedElementsAre("gfx/leaders/test_leader_portrait.dds",
			  "gfx/leaders/test_leader_portrait2.dds",
			  "gfx/leaders/test_leader_portrait3.dds",
			  "gfx/leaders/test_leader_portrait4.dds"));
}

TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedFemalePortraitsAreDefault)
{
	EXPECT_EQ("gfx/leaders/leader_unknown_female.dds",
		 graphicsMapper->getFemalePortraits("nonexistent_culture", "nonexistent_culture_group", "good_ideology")[0]);
	EXPECT_EQ("gfx/leaders/leader_unknown_female.dds",
		 graphicsMapper->getFemalePortraits("", "test_culture_group", "missing_ideology")[0]);
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedFemalePortraitsAreReturned)
{
	std::set<std::string> femalePortraits;
	for (const auto& testPortrait: graphicsMapper->getFemalePortraits("", "test_culture_group", "good_ideology"))
	{
		femalePortraits.insert(testPortrait);
	}
	for (const auto& testPortrait: graphicsMapper->getFemalePortraits("", "test_culture_group2", "good_ideology"))
	{
		femalePortraits.insert(testPortrait);
	}
	for (const auto& testPortrait: graphicsMapper->getFemalePortraits("test_culture2", "", "good_ideology"))
	{
		femalePortraits.insert(testPortrait);
	}
	EXPECT_THAT(femalePortraits,
		 testing::UnorderedElementsAre("gfx/leaders/test_leader_portraitF.dds",
			  "gfx/leaders/test_leader_portraitF2.dds",
			  "gfx/leaders/test_leader_portraitF3.dds",
			  "gfx/leaders/test_leader_portraitF4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedIdeologyMinisterPortraitsAreDefault)
{
	EXPECT_EQ("gfx/interface/ideas/idea_unknown.dds",
		 graphicsMapper->getIdeologyMinisterPortrait("nonexistent_culture",
			  "nonexistent_culture_group",
			  "good_ideology"));
	EXPECT_EQ("gfx/interface/ideas/idea_unknown.dds",
		 graphicsMapper->getIdeologyMinisterPortrait("", "test_culture_group", "missing_ideology"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedIdeologyMinisterPortraitsAreReturned)
{
	std::set<std::string> leaderPortraits;
	leaderPortraits.insert(graphicsMapper->getIdeologyMinisterPortrait("", "test_culture_group", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getIdeologyMinisterPortrait("", "test_culture_group", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getIdeologyMinisterPortrait("test_culture2", "", "good_ideology"));
	leaderPortraits.insert(graphicsMapper->getIdeologyMinisterPortrait("", "test_culture_group2", "good_ideology"));

	EXPECT_THAT(leaderPortraits,
		 testing::UnorderedElementsAre("gfx/interface/ideas/test_minister_portrait.dds",
			  "gfx/interface/ideas/test_minister_portrait2.dds",
			  "gfx/interface/ideas/test_minister_portrait3.dds",
			  "gfx/interface/ideas/test_minister_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedMaleOperativePortraitsAreEmpty)
{
	EXPECT_TRUE(graphicsMapper->getMaleOperativePortraits("nonexistent_culture", "nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedMaleOperativePortraitsAreReturned)
{
	EXPECT_THAT(graphicsMapper->getMaleOperativePortraits("", "test_culture_group"),
		 testing::ElementsAre("path/test_male_operative_portrait.dds", "path/test_male_operative_portrait2.dds"));
	EXPECT_THAT(graphicsMapper->getMaleOperativePortraits("test_culture", ""),
		 testing::ElementsAre("path/test_male_operative_portrait3.dds", "path/test_male_operative_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getMaleOperativePortraits("", "test_culture_group2"),
		 testing::ElementsAre("path/test_male_operative_portrait3.dds", "path/test_male_operative_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getMaleOperativePortraits("", "test_culture_group3"),
		 testing::ElementsAre("path/test_male_operative_portrait3.dds", "path/test_male_operative_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedFemaleOperativePortraitsAreEmpty)
{
	EXPECT_TRUE(graphicsMapper->getFemaleOperativePortraits("nonexistent_culture", "nonexistent_culture_group").empty());
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedFemaleOperativePortraitsAreReturned)
{
	EXPECT_THAT(graphicsMapper->getFemaleOperativePortraits("", "test_culture_group"),
		 testing::ElementsAre("path/test_female_operative_portrait.dds", "path/test_female_operative_portrait2.dds"));
	EXPECT_THAT(graphicsMapper->getFemaleOperativePortraits("test_culture", ""),
		 testing::ElementsAre("path/test_female_operative_portrait3.dds", "path/test_female_operative_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getFemaleOperativePortraits("", "test_culture_group2"),
		 testing::ElementsAre("path/test_female_operative_portrait3.dds", "path/test_female_operative_portrait4.dds"));
	EXPECT_THAT(graphicsMapper->getFemaleOperativePortraits("", "test_culture_group3"),
		 testing::ElementsAre("path/test_female_operative_portrait3.dds", "path/test_female_operative_portrait4.dds"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, UnmatchedGraphicalCultureIsNullopt)
{
	EXPECT_EQ(std::nullopt, graphicsMapper->getGraphicalCulture("nonexistent_culture", "nonexistent_culture_group"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, MatchedGraphicalCultureIsReturned)
{
	EXPECT_EQ("test_graphical_culture", graphicsMapper->getGraphicalCulture("", "test_culture_group"));
	EXPECT_EQ("test_graphical_culture2", graphicsMapper->getGraphicalCulture("test_culture", ""));
	EXPECT_EQ("test_graphical_culture2", graphicsMapper->getGraphicalCulture("", "test_culture_group2"));
	EXPECT_EQ("test_graphical_culture2", graphicsMapper->getGraphicalCulture("", "test_culture_group3"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, Unmatched2dGraphicalCultureIsNullopt)
{
	EXPECT_EQ(std::nullopt, graphicsMapper->get2dGraphicalCulture("nonexistent_culture", "nonexistent_culture_group"));
}


TEST_F(Mappers_Graphics_GraphicsMapperTests, Matched2dGraphicalCultureIsReturned)
{
	EXPECT_EQ("test_graphical_culture_2d", graphicsMapper->get2dGraphicalCulture("", "test_culture_group"));
	EXPECT_EQ("test_graphical_culture2_2d", graphicsMapper->get2dGraphicalCulture("test_culture", ""));
	EXPECT_EQ("test_graphical_culture2_2d", graphicsMapper->get2dGraphicalCulture("", "test_culture_group2"));
	EXPECT_EQ("test_graphical_culture2_2d", graphicsMapper->get2dGraphicalCulture("", "test_culture_group3"));
}