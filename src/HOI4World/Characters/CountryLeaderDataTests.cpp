#include "src/HOI4World/Characters/CountryLeaderDataFactory.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Characters_CountryLeaderDataFactory, ValuesAreAsSet)
{
	const HoI4::CountryLeaderData countryLeaderData("test_ideology", {"test_leader_trait_1", "test_leader_trait_2"});

	EXPECT_EQ(countryLeaderData.getIdeology(), "test_ideology");
	EXPECT_THAT(countryLeaderData.getTraits(), testing::ElementsAre("test_leader_trait_1", "test_leader_trait_2"));
}


TEST(HoI4World_Characters_CountryLeaderDataFactory, ImportedValuesAreDefault)
{
	std::stringstream input;

	const auto countryLeaderData = HoI4::CountryLeaderDataFactory().importCountryLeaderData(input);

	EXPECT_TRUE(countryLeaderData.getIdeology().empty());
	EXPECT_TRUE(countryLeaderData.getTraits().empty());
}


TEST(HoI4World_Characters_CountryLeaderDataFactory, ValuesCanBeImported)
{
	std::stringstream input;
	input << "\t\t={\n";
	input << "\t\t\tideology=test_ideology\n";
	input << "\t\t\ttraits={ test_leader_trait_1 test_leader_trait_2 }\n";
	input << "\t\t\texpire=\"1965.1.1.1\"\n";
	input << "\t\t\tid=-1\n";
	input << "\t\t}\n";

	const auto countryLeaderData = HoI4::CountryLeaderDataFactory().importCountryLeaderData(input);

	EXPECT_EQ(countryLeaderData.getIdeology(), "test_ideology");
	EXPECT_THAT(countryLeaderData.getTraits(), testing::ElementsAre("test_leader_trait_1", "test_leader_trait_2"));
}