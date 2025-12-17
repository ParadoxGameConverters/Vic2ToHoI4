#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "src/HOI4World/Factions/FactionRuleGroups.h"


TEST(HoI4World_Factions_FactionRuleGroups, FactionRuleGroupsCanBeImported)
{
	HoI4::FactionRuleGroups ruleGroups(std::filesystem::path("HoI4Windows"));

	EXPECT_THAT(ruleGroups.getRuleGroups(),
		 testing::UnorderedElementsAre(testing::Pair("rule_group_one", testing::ElementsAre("rule_one", "rule_two")),
			  testing::Pair("rule_group_two", testing::ElementsAre("rule_three"))));
}