#include "Configuration.h"
#include "V2World/Countries/CommonCountryDataBuilder.h"
#include "V2World/Countries/Country.h"
#include "V2World/Countries/CountryFactory.h"
#include "V2World/Politics/PartyBuilder.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "V2World/States/StateDefinitionsBuilder.h"
#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>
#include <sstream>



TEST(Vic2World_Countries_CountryTests, tagIsAsSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ("TAG", country->getTag());
}


TEST(Vic2World_Countries_CountryTests, colorIsFromCommonCountryData)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.setColor(testColor).Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(testColor, country->getColor());
}


TEST(Vic2World_Countries_CountryTests, HumanDefaultsToFalse)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_FALSE(country->isHuman());
}


TEST(Vic2World_Countries_CountryTests, HumanCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\thuman = whatever\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->isHuman());
}


TEST(Vic2World_Countries_CountryTests, StatesDefaultToEmpty)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getStates().empty());
}


TEST(Vic2World_Countries_CountryTests, StatesCanBeImported)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate = {\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(1, country->getStates().size());
}


TEST(Vic2World_Countries_CountryTests, DoesNotHaveLandByDefault)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_FALSE(country->hasLand());
}


TEST(Vic2World_Countries_CountryTests, HasLandWhenGivenProvinces)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	country->addProvince(std::make_pair(1, std::make_shared<Vic2::Province>()));

	ASSERT_TRUE(country->hasLand());
}


TEST(Vic2World_Countries_CountryTests, IsEmptyByDefault)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->isEmpty());
}


TEST(Vic2World_Countries_CountryTests, IsNotEmptyWhenGivenProvinces)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	country->addProvince(std::make_pair(1, std::make_shared<Vic2::Province>()));

	ASSERT_FALSE(country->isEmpty());
}


TEST(Vic2World_Countries_CountryTests, IsNotEmptyWhenGivenCores)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	country->addCore(std::make_shared<Vic2::Province>());

	ASSERT_FALSE(country->isEmpty());
}


TEST(Vic2World_Countries_CountryTests, CoresDefaultToEmpty)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getCores().empty());
}


TEST(Vic2World_Countries_CountryTests, CoresCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	country->addCore(Vic2::Province::Builder{}.setNumber(1).build());

	ASSERT_EQ(1, country->getCores().size());
	ASSERT_EQ(1, country->getCores()[0]->getNumber());
}


TEST(Vic2World_Countries_CountryTests, CapitalDefaultsToZero)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(0, country->getCapital());
}


TEST(Vic2World_Countries_CountryTests, CapitalCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcapital = 42\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(42, country->getCapital());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureDefaultsToEmpty)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getPrimaryCulture().empty());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = test_primary\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ("test_primary", country->getPrimaryCulture());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureWithQuotesCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = \"test_primary\"\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ("test_primary", country->getPrimaryCulture());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupDefaultsToNoCulture)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ("no_culture", country->getPrimaryCultureGroup());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupsSetFromPrimaryCulture)
{
	// see TestCountryCultures.txt for the culture definition
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = test_primary\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countryTests/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ("test_primary_group", country->getPrimaryCultureGroup());
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesDefaultToEmpty)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getAcceptedCultures().empty());
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesIncludePrimaryCulture)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = test_primary\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getAcceptedCultures(), testing::UnorderedElementsAre("test_primary"));
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tculture = {\n";
	theStream << "\t\ttest_primary\n";
	theStream << "\t\t\"test_primary2\"\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getAcceptedCultures(), testing::UnorderedElementsAre("test_primary", "test_primary2"));
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesIdentifiedAsAcceptedCultures)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tculture = {\n";
	theStream << "\t\ttest_primary\n";
	theStream << "\t\t\"test_primary2\"\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->isAnAcceptedCulture("test_primary"));
	ASSERT_TRUE(country->isAnAcceptedCulture("test_primary2"));
}


TEST(Vic2World_Countries_CountryTests, NonAcceptedCulturesNotIdentifiedAsAcceptedCultures)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_FALSE(country->isAnAcceptedCulture("fake_culture"));
}


TEST(Vic2World_Countries_CountryTests, TechnologiesAndInventionsDefaultToEmpty)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getTechnologiesAndInventions().empty());
}


TEST(Vic2World_Countries_CountryTests, TechnologiesAndInventionsCanBeAddedFromTechnologies)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\ttechnology = {\n";
	theStream << "\t\ttechnology_one = {}\n";
	theStream << "\t\ttechnology_two = {}\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getTechnologiesAndInventions(), testing::UnorderedElementsAre("technology_one", "technology_two"));
}


TEST(Vic2World_Countries_CountryTests, TechnologiesAndInventionsCanBeAddedFromInventions)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tactive_inventions = { 1 4 5 }\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countryTests/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getTechnologiesAndInventions(),
		 testing::UnorderedElementsAre("first_invention", "fourth_invention", "fifth_invention"));
}