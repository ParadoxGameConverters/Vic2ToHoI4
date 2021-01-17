#include "Mappers/CountryName/CountryNameMappingFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_CountryName_CountryNameMappingTests, Vic2GovernmentDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::CountryNameMappingFactory{}.importMapping(input);

	ASSERT_TRUE(mapping->vic2Government.empty());
}


TEST(Mappers_CountryName_CountryNameMappingTests, Vic2GovernmentCanBeSet)
{
	std::stringstream input;
	input << "= { vic2_gov = test_government }";
	const auto mapping = Mappers::CountryNameMappingFactory{}.importMapping(input);

	ASSERT_EQ("test_government", mapping->vic2Government);
}


TEST(Mappers_CountryName_CountryNameMappingTests, Vic2TagDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::CountryNameMappingFactory{}.importMapping(input);

	ASSERT_TRUE(mapping->vic2Tag.empty());
}


TEST(Mappers_CountryName_CountryNameMappingTests, Vic2TagCanBeSet)
{
	std::stringstream input;
	input << "= { vic2_tag = TAG }";
	const auto mapping = Mappers::CountryNameMappingFactory{}.importMapping(input);

	ASSERT_EQ("TAG", mapping->vic2Tag);
}


TEST(Mappers_CountryName_CountryNameMappingTests, HoI4IdeologyDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::CountryNameMappingFactory{}.importMapping(input);

	ASSERT_TRUE(mapping->hoi4Ideology.empty());
}


TEST(Mappers_CountryName_CountryNameMappingTests, HoI4IdeologyCanBeSet)
{
	std::stringstream input;
	input << "= { hoi4_ideology = test_ideology }";
	const auto mapping = Mappers::CountryNameMappingFactory{}.importMapping(input);

	ASSERT_EQ("test_ideology", mapping->hoi4Ideology);
}