#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Countries/CommonCountryData.h"
#include "src/V2World/Countries/CommonCountryDataFactory.h"
#include "src/V2World/Politics/PartyBuilder.h"



TEST(Vic2World_Countries_CommonCountryDataTests, DefaultsAreSet)
{
	const auto common_country_data =
		 Vic2::CommonCountryData::Factory().ImportCommonCountryData("countries/blankCommonCountryData.txt",
			  commonItems::ModFilesystem("./", {}));

	EXPECT_EQ(common_country_data->GetColor(), std::nullopt);
	EXPECT_TRUE(common_country_data->GetUnitNames().empty());
	EXPECT_TRUE(common_country_data->GetParties().empty());
}


TEST(Vic2World_Countries_CommonCountryDataTests, ItemsCanBeSet)
{
	const auto common_country_data =
		 Vic2::CommonCountryData::Factory().ImportCommonCountryData("countries/CommonCountryTestData.txt",
			  commonItems::ModFilesystem("./", {}));

	ASSERT_TRUE(common_country_data->GetColor().has_value());
	const auto expected_color = std::array{56, 32, 172};
	EXPECT_EQ(common_country_data->GetColor()->getRgbComponents(), expected_color);
	EXPECT_THAT(common_country_data->GetUnitNames(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"Azerbaijan", "Nader Shah"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
	EXPECT_THAT(common_country_data->GetParties(),
		 testing::ElementsAre(*Vic2::Party::Builder{}.setName("AZB_reactionary").Build(),
			  *Vic2::Party::Builder{}.setName("AZB_liberal").Build()));
}