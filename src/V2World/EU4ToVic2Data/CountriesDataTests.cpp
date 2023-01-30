#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/EU4ToVic2Data/CountriesData.h"
#include "src/V2World/EU4ToVic2Data/CountriesDataFactory.h"
#include <sstream>



TEST(Vic2World_EU4ToVic2Data_CountriesDataTests, CountryDataDefaultsToNullopt)
{
	const Vic2::CountriesData countries_data;

	EXPECT_EQ(countries_data.getCountryData("NON"), std::nullopt);
}


TEST(Vic2World_EU4ToVic2Data_CountriesDataTests, CountryDataCanBeImported)
{
	const commonItems::ModFilesystem mod_filesystem("",
		 {Mod("boring", "uninteresting_mod"), Mod("interesting", "Vic2/mod/test_directory")});
	const auto countries_data = Vic2::CountriesData::Factory().ImportCountriesData(mod_filesystem);

	EXPECT_EQ(countries_data->getCountryData("TAG")->getLastDynasty(), "test_dynasty");
	EXPECT_EQ(countries_data->getCountryData("TAG")->getLastMonarch(), "test_monarch");
}