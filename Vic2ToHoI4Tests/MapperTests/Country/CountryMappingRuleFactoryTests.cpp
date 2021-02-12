#include "Mappers/Country/CountryMappingRuleFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Country_CountryMappingRuleFactoryTests, Vic2PartDefaultsToEmpty)
{
	std::stringstream input;
	const auto [vic2, unused] = Mappers::CountryMappingRuleFactory().importMapping(input);

	ASSERT_TRUE(vic2.empty());
}


TEST(Mappers_Country_CountryMappingRuleFactoryTests, Vic2PartCanBeSet)
{
	std::stringstream input;
	input << "vic = TAG";
	const auto [vic2, unused] = Mappers::CountryMappingRuleFactory().importMapping(input);

	ASSERT_EQ("TAG", vic2);
}


TEST(Mappers_Country_CountryMappingRuleFactoryTests, HoI4PartDefaultsToEmpty)
{
	std::stringstream input;
	const auto [unused, HoI4] = Mappers::CountryMappingRuleFactory().importMapping(input);

	ASSERT_TRUE(HoI4.empty());
}


TEST(Mappers_Country_CountryMappingRuleFactoryTests, HoI4PartCanBeSet)
{
	std::stringstream input;
	input << "hoi = TAG hoi = TWO";
	const auto [unused, HoI4] = Mappers::CountryMappingRuleFactory().importMapping(input);

	ASSERT_THAT(HoI4, testing::ElementsAre("TAG", "TWO"));
}