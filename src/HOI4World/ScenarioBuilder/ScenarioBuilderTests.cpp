#include "external/googletest/googletest/include/gtest/gtest.h"
#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar.h"
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
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, applyRole)
{
	// Test applyRoleFxn
	// Passed country should be modified
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, initializeRoles)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	const HoI4::ScenarioBuilder builder;

	EXPECT_THAT(builder.getRoles(), expectedRoles);
};

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, initializeRolesFromPreGen)
{
	// Still need to implement pre-gen
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	const HoI4::ScenarioBuilder builder;

	EXPECT_THAT(builder.getRoles(), expectedRoles);
};