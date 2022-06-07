#include "src/Configuration.h"
#include "src/Mappers/MergeRules/MergeRules.h"
#include "src/Mappers/MergeRules/MergeRulesFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Mappers_MergeRules_MergeRulesTests, RulesCanBeImported)
{
	const auto mergeRules = Mappers::MergeRules::Factory().importMergeRules();

	ASSERT_THAT(mergeRules->getRules(),
		 ::testing::UnorderedElementsAre(testing::Pair(std::string("ONE"), std::vector<std::string>{"ONA", "ONB"}),
			  testing::Pair(std::string("TWO"), std::vector<std::string>{"TWA", "TWB"}),
			  testing::Pair(std::string("FOO"), std::vector<std::string>{"BAR", "BAZ"}),
			  testing::Pair(std::string("QUX"), std::vector<std::string>{"BAR"})));
}