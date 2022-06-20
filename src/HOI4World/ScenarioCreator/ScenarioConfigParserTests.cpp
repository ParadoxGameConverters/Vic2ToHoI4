#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioCreator/ScenarioConfigParser.h"

TEST(HoI4World_ScenarioCreator_ScenarioConfigParserTests, ValidRolesStoredAllElseIgnored)
{
	const HoI4::ConfigParser parser("configurables/scenario_creator_roles.txt");

	std::set<std::string> roles{"SpanishCivilWar", "ArsenalOfIdeology"};
	EXPECT_THAT(parser.GetPossibleRoles(), roles);
}

TEST(HoI4World_ScenarioCreator_ScenarioConfigParserTests, PreGennedScenariosCompleteRoleAssignments)
{
	const bool pregenned = true;
	HoI4::ConfigParser parser("configurables/scenarios/example_scenario.txt", pregenned);

	std::map<std::string, std::string> role_assignments;
	role_assignments.emplace("ITA", "TestShellTwo");

	EXPECT_THAT(parser.GetRoleAssignments(), role_assignments);
}
