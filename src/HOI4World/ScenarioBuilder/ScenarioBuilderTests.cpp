#include "external/googletest/googletest/include/gtest/gtest.h"
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
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, applyRole)
{
	// Test applyRoleFxn
}

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, initializeRoles)
{
	std::vector<std::shared_ptr<Role>> expectedRoles;
	expectedRoles.push_back(std::make_shared<RoleSpanishCivilWar>());
	expectedRoles.push_back(std::make_shared<RoleArsenalOfIdeology>());

	const HoI4::ScenarioBuilder builder;
};