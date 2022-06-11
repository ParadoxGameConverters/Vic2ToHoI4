#include "external/googletest/googletest/include/gtest/gtest.h"
#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, ValidRolesStoredAllElseIgnored)
{
	const HoI4::ScenarioBuilder::ConfigParser parser("configurables/ScenarioBuilderRoles.txt");

	std::vector<std::string> roles{"SpanishCivilWar", "ArsenalOfIdeology"};
	EXPECT_THAT(parser.getPossibleRoles(), roles);
}