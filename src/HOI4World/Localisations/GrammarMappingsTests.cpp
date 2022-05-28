#include "HOI4World/Localisations/GrammarMappings.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(HoI4World_Localisations_GrammarMappings, RulesAreImported)
{
	const auto mappings = HoI4::GrammarMappings().importGrammarMappings();

	ASSERT_EQ(2, mappings.size());
	ASSERT_THAT(mappings,
		 testing::UnorderedElementsAre(testing::Pair(std::string("msnc"), std::string("_MS")),
			  testing::Pair(std::string("msac"), std::string("_MS"))));
}