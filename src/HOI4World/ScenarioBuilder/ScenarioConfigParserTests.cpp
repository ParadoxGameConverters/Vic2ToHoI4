#include "external/googletest/googletest/include/gtest/gtest.h"
#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, ValidRolesStoredAllElseIgnored)
{
	const HoI4::ScenarioBuilder::ConfigParser parser("HoI4Files/ScenarioBuilder/ScenarioBuilderRoles.txt");

	EXPECT_EQ(parser.getPossibleRoles().size(),2);
}