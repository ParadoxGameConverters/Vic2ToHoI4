#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"
#include "src/HOI4World/ScenarioCreator/ScenarioCreator.h"

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, DefaultsAreAsSet)
{
	const HoI4::ScenarioCreator creator;

	EXPECT_TRUE(creator.getCountries().empty());
	EXPECT_TRUE(creator.getRoles().empty());
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, recalculateRoleFits)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleTestShellTwo>());
	expectedRoles.push_back(std::make_shared<RoleTestShellOne>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> countries;
	auto paridoxistan = HoI4::Country::Builder().addTag("PDX").addMillitaryFactories(5).build();
	countries.emplace(paridoxistan->getTag(), std::move(paridoxistan));

	// The order of roles starts as { RoleTestShellOne, RoleTestShellTwo } from input file

	const HoI4::ScenarioCreator creator(countries, "", "scenario_creator_test_roles.txt");

	// recalculateRoleFits should swap that order so RoleTestShellTwo is first after construction

	EXPECT_EQ(typeid(*creator.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(typeid(*creator.getRoles()[1]), typeid(*expectedRoles[1]));
	EXPECT_EQ(creator.getRoles().size(), 2);
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, initializeRoles)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> empty;
	const HoI4::ScenarioCreator creator(empty, "");

	// NOTE: Troubles with EXPECT_THAT and containers of ptrs
	EXPECT_EQ(typeid(*creator.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(typeid(*creator.getRoles()[1]), typeid(*expectedRoles[1]));
	EXPECT_EQ(creator.getRoles().size(), 2);
};

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, initializeRolesFromPreGen)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> ghostItaly;
	ghostItaly.emplace("ITA", std::shared_ptr<HoI4::Country>());

	const HoI4::ScenarioCreator creator(ghostItaly, "example");

	EXPECT_EQ(typeid(*creator.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(creator.getRoles().size(), 1);
};