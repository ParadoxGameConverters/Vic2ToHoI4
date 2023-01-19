#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Countries/CommonCountriesDataFactory.h"
#include "src/V2World/Politics/PartyBuilder.h"



TEST(Vic2World_Countries_CommonCountriesDataTests, ItemsDefaultToEmpty)
{
	const auto& [common_country_data, parties] =
		 Vic2::ImportCommonCountriesData(commonItems::ModFilesystem("./missing_common_countries_data/", {}));

	EXPECT_TRUE(common_country_data.empty());
	EXPECT_TRUE(parties.empty());
}


TEST(Vic2World_Countries_CommonCountriesDataTests, ItemsCanBeImported)
{
	const auto& [common_country_data, parties] =
		 Vic2::ImportCommonCountriesData(commonItems::ModFilesystem("./vanilla_common_countries_data/", {}));

	EXPECT_THAT(common_country_data,
		 testing::UnorderedElementsAre(testing::Pair("ONE",
													  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{
															.color_ = commonItems::Color(std::array<int, 3>{1, 2, 3}),
															.parties_ = {*Vic2::Party::Builder{}.setName("ONE_conservative").Build(),
																 *Vic2::Party::Builder{}.setName("ONE_liberal").Build()}})),
			  testing::Pair("TWO",
					Vic2::CommonCountryData(
						 Vic2::CommonCountryDataOptions{.color_ = commonItems::Color(std::array<int, 3>{2, 4, 6}),
							  .parties_ = {*Vic2::Party::Builder{}.setName("TWO_conservative").Build(),
									*Vic2::Party::Builder{}.setName("TWO_liberal").Build()}}))));

	EXPECT_THAT(parties,
		 testing::ElementsAre(*Vic2::Party::Builder{}.setName("ONE_conservative").Build(),
			  *Vic2::Party::Builder{}.setName("ONE_liberal").Build(),
			  *Vic2::Party::Builder{}.setName("TWO_conservative").Build(),
			  *Vic2::Party::Builder{}.setName("TWO_liberal").Build()));
}