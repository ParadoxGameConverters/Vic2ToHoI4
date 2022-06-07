#include "src/OutHoi4/Characters/OutCountryLeaderData.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(OutHoI4World_Characters_OutCountryLeaderTests, EmptyCountryLeaderDataIsOutput)
{
	const HoI4::CountryLeaderData countryLeaderData("", {});
	std::stringstream output;
	output << countryLeaderData;

	std::stringstream expected;
	expected << "\t\tcountry_leader={\n";
	expected << "\t\t\tideology=\n";
	expected << "\t\t\texpire=\"1965.1.1.1\"\n";
	expected << "\t\t\tid=-1\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Characters_OutCountryLeaderTests, IdeologyIsOutput)
{
	const HoI4::CountryLeaderData countryLeaderData("test_ideology", {});
	std::stringstream output;
	output << countryLeaderData;

	std::stringstream expected;
	expected << "\t\tcountry_leader={\n";
	expected << "\t\t\tideology=test_ideology\n";
	expected << "\t\t\texpire=\"1965.1.1.1\"\n";
	expected << "\t\t\tid=-1\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}


TEST(OutHoI4World_Characters_OutCountryLeaderTests, TraitsAreOutput)
{
	const HoI4::CountryLeaderData countryLeaderData("", {"test_trait_1", "test_trait_2"});
	std::stringstream output;
	output << countryLeaderData;

	std::stringstream expected;
	expected << "\t\tcountry_leader={\n";
	expected << "\t\t\tideology=\n";
	expected << "\t\t\ttraits={ test_trait_1 test_trait_2 }\n";
	expected << "\t\t\texpire=\"1965.1.1.1\"\n";
	expected << "\t\t\tid=-1\n";
	expected << "\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}