#include "Mappers/FactionName/FactionNameMappingFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_CountryName_FactionNameMappingTests, CultureDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::FactionNameMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->hoi4Culture.empty());
}


TEST(Mappers_FactionName_FactionNameMappingTests, CultureCanBeSet)
{
	std::stringstream input;
	input << "= { culture = test_culture }";
	const auto mapping = Mappers::FactionNameMappingFactory().importMapping(input);

	ASSERT_EQ("test_culture", mapping->hoi4Culture);
}


TEST(Mappers_FactionName_FactionNameMappingTests, IdeologyDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::FactionNameMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->hoi4Ideology.empty());
}


TEST(Mappers_FactionName_FactionNameMappingTests, IdeologyCanBeSet)
{
	std::stringstream input;
	input << "= { ideology = test_ideology }";
	const auto mapping = Mappers::FactionNameMappingFactory().importMapping(input);

	ASSERT_EQ("test_ideology", mapping->hoi4Ideology);
}


TEST(Mappers_FactionName_FactionNameMappingTests, FactionDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::FactionNameMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->factionName.empty());
}


TEST(Mappers_FactionName_FactionNameMappingTests, FactionCanBeSet)
{
	std::stringstream input;
	input << "= { faction = test_faction }";
	const auto mapping = Mappers::FactionNameMappingFactory().importMapping(input);

	ASSERT_EQ("test_faction", mapping->factionName);
}