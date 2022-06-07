#include "src/V2World/EU4ToVic2Data/CountryData.h"
#include "src/V2World/EU4ToVic2Data/CountryDataFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(Vic2World_EU4ToVic2Data_CountryDataTests, LastDynastyDefaultsToNullopt)
{
	const Vic2::CountryData countryData;

	ASSERT_EQ(std::nullopt, countryData.getLastDynasty());
}


TEST(Vic2World_EU4ToVic2Data_CountryDataTests, LastDynastyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlast_dynasty = test_dynasty\n";
	input << "}";

	const auto countryData = Vic2::CountryData::Factory().importCountryData(input);

	ASSERT_EQ("test_dynasty", countryData->getLastDynasty());
}


TEST(Vic2World_EU4ToVic2Data_CountryDataTests, LastMonarchDefaultsToNullopt)
{
	const Vic2::CountryData countryData;

	ASSERT_EQ(std::nullopt, countryData.getLastMonarch());
}


TEST(Vic2World_EU4ToVic2Data_CountryDataTests, LastMonarchCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlast_ruler_name = test_monarch\n";
	input << "}";

	const auto countryData = Vic2::CountryData::Factory().importCountryData(input);

	ASSERT_EQ("test_monarch", countryData->getLastMonarch());
}