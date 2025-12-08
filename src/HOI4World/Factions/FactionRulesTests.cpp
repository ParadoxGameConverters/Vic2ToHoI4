#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "src/HOI4World/Factions/FactionRules.h"


TEST(HoI4World_Factions_FactionRules, FactionRulesCanBeImported)
{
	HoI4::FactionRules rules;

	std::stringstream emptyStream;
	const auto& ruleOne = HoI4::FactionRule("faction_rule_one", emptyStream);
	const auto& ruleTwo = HoI4::FactionRule("faction_rule_two", emptyStream);

	EXPECT_THAT(rules.getImportedRules(),
		 testing::UnorderedElementsAre(
			  testing::Pair("ideology", testing::ElementsAre(testing::Pointee(ruleOne), testing::Pointee(ruleTwo)))));
}