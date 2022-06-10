#include "external/googletest/googletest/include/gtest/gtest.h"
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

TEST(HoI4World_ScenarioBuilder_ScenarioBuilderTests, InitializeRolesFromFile)
{
	// Read in test file ScenarioBuilderRoles.txt
	// Expect that manually built vector matches file inputed one.
}