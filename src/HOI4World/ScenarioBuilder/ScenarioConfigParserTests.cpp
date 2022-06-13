#include "external/googletest/googletest/include/gtest/gtest.h"
#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"

TEST(HoI4World_ScenarioBuilder_ScenarioConfigParserTests, ValidRolesStoredAllElseIgnored)
{
	const HoI4::ConfigParser parser("configurables/ScenarioBuilderRoles.txt");

	std::set<std::string> roles{"SpanishCivilWar", "ArsenalOfIdeology"};
	EXPECT_THAT(parser.getPossibleRoles(), roles);
}

TEST(HoI4World_ScenarioBuilder_ScenarioConfigParserTests, ValidRolesStoredAllElseIgnored)
{
	const bool pregenned = true;
	const HoI4::ConfigParser parser("configurables/scenarios/example_scenario.txt", pregenned);

	std::map<std::string, std::string> roleAssignments({"ITA", "ArsenalOfIdeology"});
	EXPECT_THAT(parser.getRoleAssignments(), roleAssignments);
}
