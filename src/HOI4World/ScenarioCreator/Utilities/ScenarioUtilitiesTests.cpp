#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"

TEST(HoI4World_ScenarioCreator_ScenarioUtilitiesTests, NonexistentFileLeavesEmptyString)
{
	std::string fake_file = "east_vs_west.txt";
	std::stringstream empty = GetStreamFromFile(fake_file);

	EXPECT_EQ(empty.str(), "");
};


TEST(HoI4World_ScenarioCreator_ScenarioUtilitiesTests, ContentsOfFileCopiedToStringStream)
{
	std::string fake_file = "Configurables/Scenarios/example_scenario.txt";
	std::stringstream file = GetStreamFromFile(fake_file);

	EXPECT_EQ(file.str(), "ITA = TestShellTwo");
};


TEST(HoI4World_ScenarioCreator_ScenarioUtilitiesTests, GetIdeologicalSituationPrioritizesGovernment)
{
	std::map<std::string, int> parties{{"a", 40}, {"b", 35}, {"c", 25}};
	IdeologicalSituationSet the_situation = GetIdeologicalSituation(parties, "b");

	auto it = the_situation.begin();
	EXPECT_EQ(it->ideology_, "b");
	++it;
	EXPECT_EQ(it->ideology_, "a");
	++it;
	EXPECT_EQ(it->ideology_, "c");
};