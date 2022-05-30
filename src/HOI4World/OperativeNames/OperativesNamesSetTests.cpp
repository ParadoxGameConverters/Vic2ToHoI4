#include "HOI4World/OperativeNames/OperativeNamesSet.h"
#include "HOI4World/OperativeNames/OperativeNamesSetFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class HoI4World_OperativeNames_OperativeNamesSetTests: public testing::Test
{
  protected:
	HoI4World_OperativeNames_OperativeNamesSetTests() = default;
	HoI4::OperativeNamesSet::Factory factory;
};


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, FilenameIsSet)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/blank_operative_codenames.txt");

	ASSERT_EQ("blank_operative_codenames.txt", operativeNamesSet->getFilename());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, WrapperDefaultsToEmpty)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/blank_operative_codenames.txt");

	ASSERT_TRUE(operativeNamesSet->getWrapper().empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, WrapperCanBeSet)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/generic_opertive_codenames.txt");

	ASSERT_EQ("GENERIC_ENG_OPERATIVE_CODENAME_HISTORICAL", operativeNamesSet->getWrapper());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, NameDefaultsToEmpty)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/blank_operative_codenames.txt");

	ASSERT_TRUE(operativeNamesSet->getName().empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, NameCanBeSet)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/generic_opertive_codenames.txt");

	ASSERT_EQ("NAME_THEME_HISTORICAL_OPERATIVES", operativeNamesSet->getName());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, CountriesDefaultsToEmpty)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/blank_operative_codenames.txt");

	ASSERT_TRUE(operativeNamesSet->getCountries().empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, CountriesAreNotSetFromFile)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/generic_opertive_codenames.txt");

	const std::vector<std::string> expectedCountries{"USA", "CAN", "NZL", "AST", "RAJ", "SAF"};
	ASSERT_TRUE(operativeNamesSet->getCountries().empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, CountriesCanBeAdded)
{
	auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/blank_operative_codenames.txt");
	operativeNamesSet->addCountry("TAG");

	ASSERT_EQ(1, operativeNamesSet->getCountries().size());
	ASSERT_EQ("TAG", operativeNamesSet->getCountries()[0]);
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, NamesDefaultsToEmpty)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/blank_operative_codenames.txt");

	ASSERT_TRUE(operativeNamesSet->getNames().empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesSetTests, NamesCanBeSet)
{
	const auto operativeNamesSet =
		 factory.getOperativeNamesSetFromFile("common/units/codenames_operatives/generic_opertive_codenames.txt");

	const std::vector<std::string> expectedNames{"Wolf",
		 "Sparrow",
		 "Hawk",
		 "Eagle",
		 "Snake",
		 "Bear",
		 "Tiger",
		 "Condor",
		 "Magpie",
		 "Turtle",
		 "Shark",
		 "Mouse",
		 "Hornet",
		 "Dragon",
		 "Butterfly",
		 "Stallion",
		 "Tomcat"};
	ASSERT_EQ(expectedNames, operativeNamesSet->getNames());
}