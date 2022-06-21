#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"
#include "src/HOI4World/ScenarioCreator/ScenarioCreator.h"

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, DefaultsAreAsSet)
{
	const HoI4::ScenarioCreator creator;

	EXPECT_TRUE(creator.GetCountries().empty());
	EXPECT_TRUE(creator.GetRoles().empty());
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, RecalculateRoleFits)
{
	std::vector<std::shared_ptr<Role>> expected_roles;
	expected_roles.push_back(std::make_shared<RoleTestShellTwo>());
	expected_roles.push_back(std::make_shared<RoleTestShellOne>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> countries;
	auto paridoxistan = HoI4::Country::Builder().setTag("PDX").setMillitaryFactories(5).build();
	countries.emplace(paridoxistan->getTag(), std::move(paridoxistan));

	// The order of roles starts as { RoleTestShellOne, RoleTestShellTwo } from input file

	const HoI4::ScenarioCreator creator(countries, "", "scenario_creator_test_roles.txt");

	// recalculateRoleFits should swap that order so RoleTestShellTwo is first after construction

	EXPECT_EQ(typeid(*creator.GetRoles()[0]), typeid(*expected_roles[0]));
	EXPECT_EQ(typeid(*creator.GetRoles()[1]), typeid(*expected_roles[1]));
	EXPECT_EQ(creator.GetRoles().size(), 2);
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, InitializeRoles)
{
	std::vector<std::shared_ptr<Role>> expected_roles;
	expected_roles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expected_roles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> empty;
	const HoI4::ScenarioCreator creator(empty, "");

	// NOTE: Troubles with EXPECT_THAT and containers of ptrs
	EXPECT_EQ(typeid(*creator.GetRoles()[0]), typeid(*expected_roles[0]));
	EXPECT_EQ(typeid(*creator.GetRoles()[1]), typeid(*expected_roles[1]));
	EXPECT_EQ(creator.GetRoles().size(), 2);
};

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, InitializeRolesFromPreGen)
{
	std::vector<std::shared_ptr<Role>> expected_roles;
	expected_roles.push_back(std::make_shared<RoleTestShellTwo>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> ghost_italy;
	ghost_italy.emplace("ITA", HoI4::Country::Builder().build());

	const HoI4::ScenarioCreator creator(ghost_italy, "example", "scenario_creator_test_roles.txt");

	EXPECT_EQ(typeid(*creator.GetRoles()[0]), typeid(*expected_roles[0]));
	EXPECT_EQ(creator.GetRoles().size(), 1);
};