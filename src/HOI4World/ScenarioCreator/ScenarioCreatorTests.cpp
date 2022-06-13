#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"
#include "src/HOI4World/ScenarioCreator/ScenarioCreator.h"

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, DefaultsAreAsSet)
{
	const HoI4::ScenarioCreator builder;

	EXPECT_TRUE(builder.getCountries().empty());
	EXPECT_TRUE(builder.getRoles().empty());
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, recalculateRoleFits)
{
	// HoI4::Country a; No default constructor for country

	// Test recalculateRoleFitsFxn
	// Order of vector should change after fxn call
	// Requires roles with working calculateFit(country) fxns
	// Make a dummy role child class just for testing purposes?
	// Would also need dummy Countries.
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, applyRole)
{
	// Test applyRoleFxn
	// Passed country should be modified
	// Need a role that acutally does something
	// Make a dummy role child class just for testing purposes?
}

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, initializeRoles)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> empty;
	const HoI4::ScenarioCreator builder(empty, "");

	// NOTE: Troubles with EXPECT_THAT and containers of ptrs
	EXPECT_EQ(typeid(*builder.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(typeid(*builder.getRoles()[1]), typeid(*expectedRoles[1]));
	EXPECT_EQ(builder.getRoles().size(), 2);
};

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, initializeRolesFromPreGen)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> ghostItaly;
	ghostItaly.emplace("ITA", std::shared_ptr<HoI4::Country>());

	const HoI4::ScenarioCreator builder(ghostItaly, "example");

	EXPECT_EQ(typeid(*builder.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(builder.getRoles().size(), 1);
};