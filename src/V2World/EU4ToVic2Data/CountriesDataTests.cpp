#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include "src/V2World/EU4ToVic2Data/CountriesData.h"
#include "src/V2World/EU4ToVic2Data/CountriesDataFactory.h"
#include <sstream>



TEST(Vic2World_EU4ToVic2Data_CountriesDataTests, CountryDataDefaultsToNullopt)
{
	const Vic2::CountriesData countriesData;

	ASSERT_EQ(std::nullopt, countriesData.getCountryData("NON"));
}


TEST(Vic2World_EU4ToVic2Data_CountriesDataTests, CountryDataCanBeImported)
{
	const auto countriesData = Vic2::CountriesData::Factory().importCountriesData(
		 *Configuration::Builder()
				.addVic2Mod(Mod("boring", "uninteresting_mod"))
				.addVic2Mod(Mod("interesting", "Vic2/mod/test_directory"))
				.build());

	ASSERT_EQ("test_dynasty", countriesData->getCountryData("TAG")->getLastDynasty());
	ASSERT_EQ("test_monarch", countriesData->getCountryData("TAG")->getLastMonarch());
}