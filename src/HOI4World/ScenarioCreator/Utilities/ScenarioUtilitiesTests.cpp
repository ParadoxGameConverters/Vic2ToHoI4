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