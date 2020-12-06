#include "Configuration.h"
#include "V2World/Countries/CommonCountryDataBuilder.h"
#include "V2World/Countries/Country.h"
#include "V2World/Countries/CountryFactory.h"
#include "V2World/Diplomacy/RelationsBuilder.h"
#include "V2World/Politics/PartyBuilder.h"
#include "V2World/Pops/PopBuilder.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "V2World/States/StateDefinitionsBuilder.h"
#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>
#include <sstream>



TEST(Vic2World_Countries_CountryTests, TagIsAsSet)
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


TEST(Vic2World_Countries_CountryTests, ColorIsFromCommonCountryData)
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


TEST(Vic2World_Countries_CountryTests, StatesCanBeModified)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate = {\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	auto& states = country->getModifiableStates();
	ASSERT_EQ(1, states.size());
	states[0].setOwner("TAG");

	ASSERT_EQ(1, country->getStates().size());
	ASSERT_EQ("TAG", country->getStates()[0].getOwner());
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


TEST(Vic2World_Countries_CountryTests, CoresCanBeReplaced)
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
	country->replaceCores({Vic2::Province::Builder{}.setNumber(2).build()});

	ASSERT_EQ(1, country->getCores().size());
	ASSERT_EQ(2, country->getCores()[0]->getNumber());
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


TEST(Vic2World_Countries_CountryTests, PrimaryCultureCanBeSetFromLargestCulture)
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
	country->addProvince(std::make_pair(1,
		 Vic2::Province::Builder{}
			  .setPops({*Vic2::Pop::Builder{}.setSize(7).setCulture("test_primary").build(),
					*Vic2::Pop::Builder{}.setSize(5).setCulture("test_secondary").build()})
			  .build()));

	ASSERT_EQ("test_primary", country->getPrimaryCulture());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupCanBeSetFromLargestCulture)
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
	country->addProvince(std::make_pair(1,
		 Vic2::Province::Builder{}
			  .setPops({*Vic2::Pop::Builder{}.setSize(7).setCulture("test_primary").build(),
					*Vic2::Pop::Builder{}.setSize(5).setCulture("test_secondary").build()})
			  .build()));

	ASSERT_EQ("test_primary_group", country->getPrimaryCultureGroup());
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

	ASSERT_THAT(country->getTechnologiesAndInventions(),
		 testing::UnorderedElementsAre("technology_one", "technology_two"));
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


TEST(Vic2World_Countries_CountryTests, RelationsDefaultToEmpty)
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

	ASSERT_TRUE(country->getRelations().empty());
}


TEST(Vic2World_Countries_CountryTests, RelationsCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tTWO =\n";
	theStream << "\t{\n";
	theStream << "\t\tvalue=42\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getRelations(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("TWO"), *Vic2::Relations::Builder{}.setValue(42).build())));
}


TEST(Vic2World_Countries_CountryTests, AiDefaultsToEmpty)
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

	ASSERT_TRUE(country->getAI()->getStrategies().empty());
}


TEST(Vic2World_Countries_CountryTests, AiCanBeImported)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tai= {\n";
	theStream << "\t\tprotect=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tid=\"TWO\"\n";
	theStream << "\t\t\tvalue=42\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(1, country->getAI()->getStrategies().size());
	ASSERT_EQ("protect", country->getAI()->getStrategies()[0].getType());
	ASSERT_EQ("TWO", country->getAI()->getStrategies()[0].getID());
	ASSERT_EQ(42, country->getAI()->getStrategies()[0].getValue());
}


TEST(Vic2World_Countries_CountryTests, AiConquerStrategiesCanBeConsolidated)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tai= {\n";
	theStream << "\t\tconquer_prov=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tid=\"1\"\n";
	theStream << "\t\t\tvalue=5\n";
	theStream << "\t\t}\n";
	theStream << "\t\tconquer_prov=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tid=\"2\"\n";
	theStream << "\t\t\tvalue=7\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	country->consolidateConquerStrategies(
		 {std::make_pair(1, Vic2::Province::Builder{}.setNumber(1).setOwner("TWO").build()),
			  std::make_pair(2, Vic2::Province::Builder{}.setNumber(2).setOwner("TWO").build())});

	ASSERT_EQ(12, country->getAI()->getConsolidatedStrategies().find("TWO")->second);
}


TEST(Vic2World_Countries_CountryTests, CivilizedDefaultsToFalse)
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

	ASSERT_FALSE(country->isCivilized());
}


TEST(Vic2World_Countries_CountryTests, CivilizedCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcivilized = yes\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->isCivilized());
}


TEST(Vic2World_Countries_CountryTests, CivilizedNotSetWithoutYes)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcivilized = no\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_FALSE(country->isCivilized());
}


TEST(Vic2World_Countries_CountryTests, ArmiesDefaultsToEmpty)
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

	ASSERT_TRUE(country->getArmies().empty());
}


TEST(Vic2World_Countries_CountryTests, ArmiesCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tarmy=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"42nd Army\"\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(1, country->getArmies().size());
	ASSERT_EQ("42nd Army", country->getArmies()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, NaviesCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tnavy=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"42nd Fleet\"\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(1, country->getArmies().size());
	ASSERT_EQ("42nd Fleet", country->getArmies()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, TransportedArmiesCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tnavy=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"42nd Fleet\"\n";
	theStream << "\t\tarmy=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\t\tname=\"42nd Army\"\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(2, country->getArmies().size());
	ASSERT_EQ("42nd Army", country->getArmies()[0].getName());
	ASSERT_EQ("42nd Fleet", country->getArmies()[1].getName());
}


TEST(Vic2World_Countries_CountryTests, LeadersDefaultToEmpty)
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

	ASSERT_TRUE(country->getLeaders().empty());
}


TEST(Vic2World_Countries_CountryTests, LeadersCanBeAdded)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(1, country->getLeaders().size());
	ASSERT_EQ("Probo Homo", country->getLeaders()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, LeadersCanBeLimited)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=20\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(20, country->getLeaders().size());
	country->limitCommanders();
	ASSERT_EQ(1, country->getLeaders().size());
	ASSERT_EQ(20, country->getLeaders()[0].getPrestige());
}


TEST(Vic2World_Countries_CountryTests, GeneralsAndAdmiralsLimitedSeparately)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=20\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=10\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t\t\tprestige=5\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(40, country->getLeaders().size());
	country->limitCommanders();
	ASSERT_EQ(2, country->getLeaders().size());
	ASSERT_EQ(20, country->getLeaders()[0].getPrestige());
	ASSERT_EQ(5, country->getLeaders()[1].getPrestige());
}


TEST(Vic2World_Countries_CountryTests, RevanchismDefaultsToZero)
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

	ASSERT_NEAR(0.0, country->getRevanchism(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, RevanchismCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\trevanchism = 4.2\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_NEAR(4.2, country->getRevanchism(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, WarExhaustionDefaultsToZero)
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

	ASSERT_NEAR(0.0, country->getWarExhaustion(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, WarExhaustionCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\twar_exhaustion = 4.2\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_NEAR(4.2, country->getWarExhaustion(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, BadBoyDefaultsToZero)
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

	ASSERT_NEAR(0.0, country->getBadBoy(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, BadBoyCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tbadboy = 4.2\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_NEAR(4.2, country->getBadBoy(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, FlagsDefaultToEmpty)
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

	ASSERT_TRUE(country->getFlags().empty());
}


TEST(Vic2World_Countries_CountryTests, FlagsCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tflags=\n";
	theStream << "\t{\n";
	theStream << "\t\ttest_flag_one=yes\n";
	theStream << "\t\ttest_flag_two=no\n";
	theStream << "\t\ttest_flag_three=nobody_cares_what_this_is\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getFlags(), testing::UnorderedElementsAre("test_flag_one", "test_flag_two", "test_flag_three"));
}


TEST(Vic2World_Countries_CountryTests, GovernmentDefaultsToBlank)
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

	ASSERT_TRUE(country->getGovernment().empty());
}


TEST(Vic2World_Countries_CountryTests, GovernmentCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tgovernment=test_government\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ("test_government", country->getGovernment());
}


TEST(Vic2World_Countries_CountryTests, UpperHouseCompositionDefaultsToEmpty)
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

	ASSERT_TRUE(country->getUpperHouseComposition().empty());
}


TEST(Vic2World_Countries_CountryTests, UpperHouseCompositionCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tupper_house=\n";
	theStream << "\t{\n";
	theStream << "\t\tideology_one=0.3\n";
	theStream << "\t\tideology_two=0.6\n";
	theStream << "\t\tideology_three=0.1\n";
	theStream << "\t}\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getUpperHouseComposition(),
		 testing::UnorderedElementsAre(testing::Pair(std::string("ideology_one"), 0.3),
			  testing::Pair(std::string("ideology_two"), 0.6),
			  testing::Pair(std::string("ideology_three"), 0.1)));
}


TEST(Vic2World_Countries_CountryTests, RulingPartyUnsetThrowsException)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};
	std::stringstream theStream;
	auto countryFactory = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()};

	ASSERT_THROW(
		 {
			 try
			 {

				 countryFactory.createCountry("TAG",
					  theStream,
					  *Vic2::CommonCountryData::Builder{}.Build(),
					  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
			 }
			 catch (const std::runtime_error& e)
			 {
				 EXPECT_STREQ("TAG had no ruling party. The save needs manual repair.", e.what());
				 throw;
			 }
		 },
		 std::runtime_error);
}


TEST(Vic2World_Countries_CountryTests, RulingPartyNonexistantThrowsException)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	auto countryFactory = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()};

	ASSERT_THROW(
		 {
			 try
			 {

				 countryFactory.createCountry("TAG",
					  theStream,
					  *Vic2::CommonCountryData::Builder{}.Build(),
					  std::vector<Vic2::Party>{});
			 }
			 catch (const std::runtime_error& e)
			 {
				 EXPECT_STREQ(
					  "Could not find the ruling party for TAG. Most likely a mod was not included.\n"
					  "Double-check your settings, and remember to include EU4 to Vic2 mods. See the FAQ for more "
					  "information.",
					  e.what());
				 throw;
			 }
		 },
		 std::runtime_error);
}


TEST(Vic2World_Countries_CountryTests, RulingPartyCanBeSet)
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
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.setName("test_party").Build()});

	ASSERT_EQ("test_party", country->getRulingParty().getName());
}


TEST(Vic2World_Countries_CountryTests, ActivePartiesDefaultToEmpty)
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

	ASSERT_TRUE(country->getActiveParties().empty());
}


TEST(Vic2World_Countries_CountryTests, ActivePartiesCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tactive_party=1\n";
	theStream << "\tactive_party=3\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.setName("test_party_one").Build(),
												*Vic2::Party::Builder{}.setName("test_party_two").Build(),
												*Vic2::Party::Builder{}.setName("test_party_three").Build()});

	ASSERT_THAT(country->getActiveParties(),
		 testing::UnorderedElementsAre(*Vic2::Party::Builder{}.setName("test_party_one").Build(),
			  *Vic2::Party::Builder{}.setName("test_party_three").Build()));
}


TEST(Vic2World_Countries_CountryTests, LastElectionDefaultsToOneOneOne)
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

	ASSERT_EQ(country->getLastElection(), date("1.1.1"));
}


TEST(Vic2World_Countries_CountryTests, LastElectionCanBeSet)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tlast_election=1942.11.6\n";
	theStream << "}";
	const auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
									 .createCountry("TAG",
										  theStream,
										  *Vic2::CommonCountryData::Builder{}.Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(country->getLastElection(), date("1942.11.6"));
}


TEST(Vic2World_Countries_CountryTests, ShipNamesDefaultToEmpty)
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

	ASSERT_TRUE(country->getAllShipNames().empty());
	ASSERT_TRUE(country->getShipNames("dreadnought").empty());
	ASSERT_TRUE(country->getShipNames("ironclad").empty());
}


TEST(Vic2World_Countries_CountryTests, ShipNamesCanBeSet)
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
										  *Vic2::CommonCountryData::Builder{}
												 .addUnitNames("dreadnought", std::vector<std::string>{"Azerbaijan", "Nader Shah"})
												 .addUnitNames("ironclad", std::vector<std::string>{"Erivan", "Nakchivan"})
												 .Build(),
										  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_THAT(country->getAllShipNames(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"Azerbaijan", "Nader Shah"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
	ASSERT_THAT(country->getShipNames("dreadnought"), testing::UnorderedElementsAre("Azerbaijan", "Nader Shah"));
	ASSERT_THAT(country->getShipNames("ironclad"), testing::UnorderedElementsAre("Erivan", "Nakchivan"));
}


TEST(Vic2World_Countries_CountryTests, AtWarDefaultsToFalse)
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

	ASSERT_FALSE(country->isAtWar());
}


TEST(Vic2World_Countries_CountryTests, AtWarCanBeSet)
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
	country->setAtWar();

	ASSERT_TRUE(country->isAtWar());
}


TEST(Vic2World_Countries_CountryTests, WarsDefaultToEmpty)
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

	ASSERT_TRUE(country->getWars().empty());
}


TEST(Vic2World_Countries_CountryTests, WarsCanBeAdded)
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
	country->addWar(Vic2::War{});

	ASSERT_FALSE(country->getWars().empty());
}


TEST(Vic2World_Countries_CountryTests, HasCoreOnCapitalFalseWithNoCoreOnCapital)
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

	ASSERT_FALSE(country->hasCoreOnCapital());
}


TEST(Vic2World_Countries_CountryTests, HasCoreOnCapitalTrueWithCoreOnCapital)
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
	country->addCore(Vic2::Province::Builder{}.setNumber(42).build());


	ASSERT_TRUE(country->hasCoreOnCapital());
}


TEST(Vic2World_Countries_CountryTests, EmployedWorkersDefaultsToZero)
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

	ASSERT_EQ(0, country->getEmployedWorkers());
}


TEST(Vic2World_Countries_CountryTests, EmployedWorkersComeFromStates)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate=\n";
	theStream << "\t{\n";
	theStream << "\t\tprovinces=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\t1\n";
	theStream << "\t\t}\n";
	theStream << "\t\tstate_buildings=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tlevel=1\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "\tstate=\n";
	theStream << "\t{\n";
	theStream << "\t\tprovinces=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\t2\n";
	theStream << "\t\t}\n";
	theStream << "\t\tstate_buildings=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tlevel=1\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	country->addProvince(std::make_pair(1,
		 Vic2::Province::Builder{}
			  .setNumber(1)
			  .setPops({*Vic2::Pop::Builder{}.setType("craftsmen").setSize(5).build()})
			  .build()));
	country->addProvince(std::make_pair(2,
		 Vic2::Province::Builder{}
			  .setNumber(2)
			  .setPops({*Vic2::Pop::Builder{}.setType("craftsmen").setSize(7).build()})
			  .build()));
	country->putProvincesInStates();
	country->determineEmployedWorkers();

	ASSERT_EQ(12, country->getEmployedWorkers());
}


TEST(Vic2World_Countries_CountryTests, IssueSupportDefaultsToZero)
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

	ASSERT_EQ(0, country->getAverageIssueSupport("test_issue"));
}


TEST(Vic2World_Countries_CountryTests, IssueSupportComesFromProvinces)
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
	country->addProvince(std::make_pair(1,
		 Vic2::Province::Builder{}
			  .setNumber(1)
			  .setPops({*Vic2::Pop::Builder{}.setIssues({std::make_pair("test_issue", 0.5F)}).setSize(5).build()})
			  .build()));

	ASSERT_EQ(0.5, country->getAverageIssueSupport("test_issue"));
}


TEST(Vic2World_Countries_CountryTests, NameMissingByDefault)
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

	ASSERT_EQ(std::nullopt, country->getName("english"));
}


TEST(Vic2World_Countries_CountryTests, NameComesFromLocalisations)
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

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Test Country"),
		 std::make_pair("spanish", "País de prueba")};
	Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationNames(localisations);

	ASSERT_EQ("Test Country", country->getName("english"));
	ASSERT_EQ("País de prueba", country->getName("spanish"));
}


TEST(Vic2World_Countries_CountryTests, NameCanComeFromDomain)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tdomain_region=\"Test Region\"\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Test Country"),
		 std::make_pair("spanish", "País de prueba")};
	Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationNames(localisations);

	ASSERT_EQ("Test Region", country->getName("english"));
	ASSERT_EQ("Test Region", country->getName("spanish"));
}


TEST(Vic2World_Countries_CountryTests, NameFromDomainUpdatesLocalisations)
{
	const commonItems::Color testColor{std::array<int, 3>{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tdomain_region=\"Test Region\"\n";
	theStream << "}";
	auto country = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
							 .createCountry("TAG",
								  theStream,
								  *Vic2::CommonCountryData::Builder{}.Build(),
								  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "$REGION$"),
		 std::make_pair("spanish", "$REGION$")};
	Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationNames(localisations);

	ASSERT_EQ("Test Region", localisations.getTextInLanguage("TAG", "english"));
	ASSERT_EQ("Test Region", localisations.getTextInLanguage("TAG", "spanish"));
}


TEST(Vic2World_Countries_CountryTests, AdjectiveMissingByDefault)
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

	ASSERT_EQ(std::nullopt, country->getAdjective("english"));
}


TEST(Vic2World_Countries_CountryTests, AdjectiveComesFromLocalisations)
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

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Testy"),
		 std::make_pair("spanish",
			  "Irascible")}; // yes, I know that's a different meaning than what I was going for. The contrast amuses me.
	Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG_ADJ", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationAdjectives(localisations);

	ASSERT_EQ("Testy", country->getAdjective("english"));
	ASSERT_EQ("Irascible", country->getAdjective("spanish"));
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsStates)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "\tstate=\n";
	theStreamTwo << "\t{\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getStates().empty());
	country->eatCountry(*countryTwo, false);

	ASSERT_EQ(1, country->getStates().size());
	ASSERT_EQ("TAG", country->getStates()[0].getOwner());
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsCores)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});
	countryTwo->addCore(Vic2::Province::Builder{}.setNumber(1).setCores({"TWO"}).build());
	countryTwo->addCore(Vic2::Province::Builder{}.setNumber(2).setCores({"TWO"}).build());

	ASSERT_TRUE(country->getCores().empty());
	country->eatCountry(*countryTwo, false);

	ASSERT_EQ(2, country->getCores().size());
	ASSERT_FALSE(country->getCores()[0]->getCores().contains("TWO"));
	ASSERT_TRUE(country->getCores()[0]->getCores().contains("TAG"));
	ASSERT_FALSE(country->getCores()[1]->getCores().contains("TWO"));
	ASSERT_TRUE(country->getCores()[1]->getCores().contains("TAG"));
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsProvinces)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder{}.setNumber(1).setOwner({"TWO"}).build();
	std::shared_ptr<Vic2::Province> provinceTwo = Vic2::Province::Builder{}.setNumber(2).setOwner({"TWO"}).build();
	countryTwo->addProvince(std::make_pair(1, provinceOne));
	countryTwo->addProvince(std::make_pair(2, provinceTwo));

	ASSERT_FALSE(country->hasLand());
	country->eatCountry(*countryTwo, false);

	ASSERT_TRUE(country->hasLand());
	ASSERT_EQ("TAG", provinceOne->getOwner());
	ASSERT_EQ("TAG", provinceTwo->getOwner());
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsTechnologiesAndInventions)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "\ttechnology = {\n";
	theStreamTwo << "\t\ttechnology_one = {}\n";
	theStreamTwo << "\t\ttechnology_two = {}\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getTechnologiesAndInventions().empty());
	country->eatCountry(*countryTwo, false);

	ASSERT_THAT(country->getTechnologiesAndInventions(),
		 testing::UnorderedElementsAre("technology_one", "technology_two"));
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsArmies)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "\tarmy=\n";
	theStreamTwo << "\t{\n";
	theStreamTwo << "\t\t\tname=\"42nd Army\"\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_TRUE(country->getArmies().empty());
	country->eatCountry(*countryTwo, false);

	ASSERT_EQ(1, country->getArmies().size());
	ASSERT_EQ("42nd Army", country->getArmies()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, EatCountryNoLoggingIfDebugOff)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	country->eatCountry(*countryTwo, false);
	std::cout.rdbuf(stdOutBuf);

	ASSERT_TRUE(log.str().empty());
}


TEST(Vic2World_Countries_CountryTests, EatCountryLogsIfDebugTrue)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	country->eatCountry(*countryTwo, true);
	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ("   [DEBUG]     Merged TWO into TAG\n", log.str());
}


TEST(Vic2World_Countries_CountryTests, SameTagsMakeEqualCountries)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TAG",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_EQ(*country, *countryTwo);
}


TEST(Vic2World_Countries_CountryTests, DifferentTagsMakeUnequalCountries)
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

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(),
		 *Vic2::StateDefinitions::Builder{}.build()}
										 .createCountry("TWO",
											  theStreamTwo,
											  *Vic2::CommonCountryData::Builder{}.Build(),
											  std::vector<Vic2::Party>{*Vic2::Party::Builder{}.Build()});

	ASSERT_NE(*country, *countryTwo);
}