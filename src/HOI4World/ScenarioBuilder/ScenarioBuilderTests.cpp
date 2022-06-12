#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, DefaultsAreAsSet)
{
	const HoI4::ScenarioBuilder builder;

	EXPECT_TRUE(builder.getCountries().empty());
	EXPECT_TRUE(builder.getRoles().empty());
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, recalculateRoleFits)
{
	// Test recalculateRoleFitsFxn
	// Order of vector should change after fxn call
	// Requires roles with working calculateFit(country) fxns
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, applyRole)
{
	// Test applyRoleFxn
	// Passed country should be modified
	// Need a role that acutally does something
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, initializeRoles)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> empty;
	const HoI4::ScenarioBuilder builder(empty, "");

	// NOTE: Troubles with EXPECT_THAT and shared ptrs
	EXPECT_EQ(typeid(*builder.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(typeid(*builder.getRoles()[1]), typeid(*expectedRoles[1]));
	EXPECT_EQ(builder.getRoles().size(), 2);
};

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, initializeRolesFromPreGen)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	std::map<std::string, std::shared_ptr<HoI4::Country>> ghostItaly;
	ghostItaly.emplace("ITA", std::shared_ptr<HoI4::Country>());

	const HoI4::ScenarioBuilder builder(ghostItaly, "example");

	EXPECT_EQ(typeid(*builder.getRoles()[0]), typeid(*expectedRoles[0]));
	EXPECT_EQ(builder.getRoles().size(), 1);
};