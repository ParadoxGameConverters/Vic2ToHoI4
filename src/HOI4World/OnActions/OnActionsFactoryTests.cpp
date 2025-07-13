#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/OnActions/OnActionsFactory.h"



TEST(HoI4World_OnActions_OnActionsFactory, OnActionsCanBeImported)
{
	HoI4::OnActions::Factory onActionsFactory;

	const auto onActions = onActionsFactory.importOnActions("Configurables/ImportOnActions.txt");

	std::string effect;
	effect += "= {\n";
	effect += "\t\teffect = {\n";
	effect += "\t\t\t\n";
	effect += "\t\t}\n";
	effect += "\t}";

	EXPECT_THAT(onActions,
		 testing::UnorderedElementsAre(testing::Pair("on_weekly_TAG", effect), testing::Pair("on_daily_TAG", effect)));
}