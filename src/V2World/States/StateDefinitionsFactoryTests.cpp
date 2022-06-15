#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/States/StateDefinitionsFactory.h"
#include <sstream>



TEST(Vic2World_States_StateDefinitionsFactoryTests, ItemsInStateAreImported)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto stateDefinitions = Vic2::StateDefinitions::Factory().getStateDefinitions(mod_filesystem);

	const std::set<int> expectedProvinces{1, 2, 3};
	EXPECT_EQ(stateDefinitions->getAllProvinces(1), expectedProvinces);
	ASSERT_TRUE(stateDefinitions->getStateID(1).has_value());
	EXPECT_EQ(*stateDefinitions->getStateID(1), "VANILLA_STATE");
	ASSERT_TRUE(stateDefinitions->getCapitalProvince("VANILLA_STATE").has_value());
	EXPECT_EQ(*stateDefinitions->getCapitalProvince("VANILLA_STATE"), 1);
}