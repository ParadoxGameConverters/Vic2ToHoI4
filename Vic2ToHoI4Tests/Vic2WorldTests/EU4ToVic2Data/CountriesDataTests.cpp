#include "Configuration.h"
#include "V2World/EU4ToVic2Data/CountriesData.h"
#include "V2World/EU4ToVic2Data/CountriesDataFactory.h"
#include "V2World/Mods/ModBuilder.h"
#include "gtest/gtest.h"
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
				.setVic2ModPath("./Vic2/Mod")
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("uninteresting_mod").build())
				.addVic2Mod(*Vic2::Mod::Builder().setDirectory("test_directory").build())
				.build());

	ASSERT_EQ("test_dynasty", countriesData->getCountryData("TAG")->getLastDynasty());
}