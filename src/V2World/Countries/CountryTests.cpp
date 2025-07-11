#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/Countries/CountryFactory.h"
#include "src/V2World/Culture/CultureGroupsFactory.h"
#include "src/V2World/Diplomacy/RelationsBuilder.h"
#include "src/V2World/EU4ToVic2Data/CountryDataBuilder.h"
#include "src/V2World/Politics/PartyBuilder.h"
#include "src/V2World/Pops/Pop.h"
#include "src/V2World/Provinces/ProvinceBuilder.h"
#include "src/V2World/States/StateDefinitionsBuilder.h"
#include "src/V2World/States/StateLanguageCategoriesBuilder.h"
#include <sstream>



using Vic2::Pop;
using Vic2::PopOptions;



TEST(Vic2World_Countries_CountryTests, TagIsAsSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ("TAG", country->getTag());
}


TEST(Vic2World_Countries_CountryTests, ColorIsFromCommonCountryData)
{
	const commonItems::Color testColor{std::array{1, 2, 3}};

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{.color_ = testColor}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(testColor, country->getColor());
}


TEST(Vic2World_Countries_CountryTests, HumanDefaultsToFalse)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->isHuman());
}


TEST(Vic2World_Countries_CountryTests, HumanCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\thuman = yes\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->isHuman());
}


TEST(Vic2World_Countries_CountryTests, HumanNotSetWithoutYes)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\thuman = whatever\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->isHuman());
}


TEST(Vic2World_Countries_CountryTests, StatesDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getStates().empty());
}


TEST(Vic2World_Countries_CountryTests, StatesCanBeImported)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate = {\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(1, country->getStates().size());
}


TEST(Vic2World_Countries_CountryTests, DoesNotHaveLandByDefault)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->hasLand());
}


TEST(Vic2World_Countries_CountryTests, HasLandWhenGivenProvinces)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addProvince(1, std::make_shared<Vic2::Province>());

	ASSERT_TRUE(country->hasLand());
}


TEST(Vic2World_Countries_CountryTests, IsEmptyByDefault)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->isEmpty());
}


TEST(Vic2World_Countries_CountryTests, IsNotEmptyWhenGivenProvinces)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addProvince(1, std::make_shared<Vic2::Province>());

	ASSERT_FALSE(country->isEmpty());
}


TEST(Vic2World_Countries_CountryTests, IsNotEmptyWhenGivenCores)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addCore(std::make_shared<Vic2::Province>());

	ASSERT_FALSE(country->isEmpty());
}


TEST(Vic2World_Countries_CountryTests, CoresDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getCores().empty());
}


TEST(Vic2World_Countries_CountryTests, CoresCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addCore(Vic2::Province::Builder().setNumber(1).build());

	ASSERT_EQ(1, country->getCores().size());
	ASSERT_EQ(1, country->getCores()[0]->getNumber());
}


TEST(Vic2World_Countries_CountryTests, CoresCanBeReplaced)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addCore(Vic2::Province::Builder().setNumber(1).build());
	country->replaceCores({Vic2::Province::Builder().setNumber(2).build()});

	ASSERT_EQ(1, country->getCores().size());
	ASSERT_EQ(2, country->getCores()[0]->getNumber());
}


TEST(Vic2World_Countries_CountryTests, CapitalDefaultsToZero)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(0, country->getCapital());
}


TEST(Vic2World_Countries_CountryTests, CapitalCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcapital = 42\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																		.createCountry("TAG",
																			 theStream,
																			 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																			 std::vector{*Vic2::Party::Builder().Build()},
																			 *Vic2::StateLanguageCategories::Builder().build(),
																			 0.05F,
																			 std::nullopt);

	ASSERT_EQ(42, country->getCapital());
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureDefaultsToNullopt)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																		.createCountry("TAG",
																			 theStream,
																			 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																			 std::vector{*Vic2::Party::Builder().Build()},
																			 *Vic2::StateLanguageCategories::Builder().build(),
																			 0.05F,
																			 std::nullopt);

	EXPECT_EQ(country->getPrimaryCulture(), std::nullopt);
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = test_primary\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});

	const std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																		.createCountry("TAG",
																			 theStream,
																			 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																			 std::vector{*Vic2::Party::Builder().Build()},
																			 *Vic2::StateLanguageCategories::Builder().build(),
																			 0.05F,
																			 std::nullopt);

	EXPECT_EQ(country->getPrimaryCulture(), std::make_optional("test_primary"));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureWithQuotesCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = \"test_primary\"\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});

	const std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																		.createCountry("TAG",
																			 theStream,
																			 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																			 std::vector{*Vic2::Party::Builder().Build()},
																			 *Vic2::StateLanguageCategories::Builder().build(),
																			 0.05F,
																			 std::nullopt);

	EXPECT_EQ(country->getPrimaryCulture(), std::make_optional("test_primary"));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureCanBeSetFromLargestCulture)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});
	std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																.createCountry("TAG",
																	 theStream,
																	 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																	 std::vector{*Vic2::Party::Builder().Build()},
																	 *Vic2::StateLanguageCategories::Builder().build(),
																	 0.05F,
																	 std::nullopt);
	country->addProvince(1,
		 Vic2::Province::Builder()
			  .setNumber(1)
			  .setPops({Pop(PopOptions{.culture = "test_primary", .size = 7}),
					Pop(PopOptions{.culture = "test_secondary", .size = 5})})
			  .build());

	std::stringstream log;
	auto std_out_buf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	country->HandleMissingCulture(*Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	std::cout.rdbuf(std_out_buf);

	EXPECT_EQ(country->getPrimaryCulture(), std::make_optional("test_primary"));
	EXPECT_THAT(log.str(),
		 testing::HasSubstr("[WARNING] TAG had no primary culture set. Attempting to get one via pops."));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureCanBeSetFromMultiplePopsAddingToLargestCulture)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});

	std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																.createCountry("TAG",
																	 theStream,
																	 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																	 std::vector{*Vic2::Party::Builder().Build()},
																	 *Vic2::StateLanguageCategories::Builder().build(),
																	 0.05F,
																	 std::nullopt);
	country->addProvince(1,
		 Vic2::Province::Builder()
			  .setNumber(1)
			  .setPops({Pop(PopOptions{.culture = "test_primary", .size = 3}),
					Pop(PopOptions{.culture = "test_primary", .size = 4}),
					Pop(PopOptions{.culture = "test_secondary", .size = 5})})
			  .build());

	country->HandleMissingCulture(*Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	EXPECT_EQ(country->getPrimaryCulture(), std::make_optional("test_primary"));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureNotSetFromLargestCultureIfNoPops)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});

	std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																.createCountry("TAG",
																	 theStream,
																	 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																	 std::vector{*Vic2::Party::Builder().Build()},
																	 *Vic2::StateLanguageCategories::Builder().build(),
																	 0.05F,
																	 std::nullopt);

	std::stringstream log;
	auto std_out_buf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	country->HandleMissingCulture(*Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	std::cout.rdbuf(std_out_buf);

	EXPECT_EQ(country->getPrimaryCulture(), std::nullopt);
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] \tCould not set primary culture via pops."));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupDefaultsToNullopt)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																		.createCountry("TAG",
																			 theStream,
																			 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																			 std::vector{*Vic2::Party::Builder().Build()},
																			 *Vic2::StateLanguageCategories::Builder().build(),
																			 0.05F,
																			 std::nullopt);

	EXPECT_EQ(country->getPrimaryCulture(), std::nullopt);
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupsSetFromPrimaryCulture)
{
	// see TestCountryCultures.txt for the culture definition
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = test_primary\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});
	const std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																		.createCountry("TAG",
																			 theStream,
																			 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																			 std::vector{*Vic2::Party::Builder().Build()},
																			 *Vic2::StateLanguageCategories::Builder().build(),
																			 0.05F,
																			 std::nullopt);

	EXPECT_EQ(country->getPrimaryCultureGroup(), std::make_optional("test_primary_group"));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupNotSetFromLargestCultureIfNoPops)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});
	std::unique_ptr<Vic2::Country> country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
																.createCountry("TAG",
																	 theStream,
																	 Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
																	 std::vector{*Vic2::Party::Builder().Build()},
																	 *Vic2::StateLanguageCategories::Builder().build(),
																	 0.05F,
																	 std::nullopt);

	std::stringstream log;
	auto std_out_buf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	country->HandleMissingCulture(*Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	std::cout.rdbuf(std_out_buf);

	EXPECT_EQ(country->getPrimaryCultureGroup(), std::nullopt);
	EXPECT_THAT(log.str(),
		 testing::HasSubstr("[WARNING] TAG had no primary culture set. Attempting to get one via pops."));
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] \tCould not set primary culture via pops."));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupCanBeSetFromLargestCulture)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addProvince(1,
		 Vic2::Province::Builder()
			  .setNumber(1)
			  .setPops({Pop(PopOptions{.culture = "test_primary", .size = 7}),
					Pop(PopOptions{.culture = "test_secondary", .size = 6})})
			  .build());

	country->HandleMissingCulture(*Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	EXPECT_EQ(country->getPrimaryCultureGroup(), std::make_optional("test_primary_group"));
}


TEST(Vic2World_Countries_CountryTests, PrimaryCultureGroupBecomesNulloptfUnset)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);
	country->HandleMissingCulture(*Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	EXPECT_EQ(country->getPrimaryCultureGroup(), std::nullopt);
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getAcceptedCultures().empty());
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesIncludePrimaryCulture)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tprimary_culture = test_primary\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getAcceptedCultures(), testing::UnorderedElementsAre("test_primary"));
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tculture = {\n";
	theStream << "\t\ttest_primary\n";
	theStream << "\t\t\"test_primary2\"\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getAcceptedCultures(), testing::UnorderedElementsAre("test_primary", "test_primary2"));
}


TEST(Vic2World_Countries_CountryTests, AcceptedCulturesIdentifiedAsAcceptedCultures)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tculture = {\n";
	theStream << "\t\ttest_primary\n";
	theStream << "\t\t\"test_primary2\"\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->isAnAcceptedCulture("test_primary"));
	ASSERT_TRUE(country->isAnAcceptedCulture("test_primary2"));
}


TEST(Vic2World_Countries_CountryTests, NonAcceptedCulturesNotIdentifiedAsAcceptedCultures)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->isAnAcceptedCulture("fake_culture"));
}


TEST(Vic2World_Countries_CountryTests, TechnologiesAndInventionsDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getTechnologiesAndInventions().empty());
}


TEST(Vic2World_Countries_CountryTests, TechnologiesAndInventionsCanBeAddedFromTechnologies)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\ttechnology = {\n";
	theStream << "\t\ttechnology_one = {}\n";
	theStream << "\t\ttechnology_two = {}\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getTechnologiesAndInventions(),
		 testing::UnorderedElementsAre("technology_one", "technology_two"));
}


TEST(Vic2World_Countries_CountryTests, TechnologiesAndInventionsCanBeAddedFromInventions)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tactive_inventions = { 1 4 5 }\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countryTests", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getTechnologiesAndInventions(),
		 testing::UnorderedElementsAre("first_invention", "fourth_invention", "fifth_invention"));
}


TEST(Vic2World_Countries_CountryTests, RelationsDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getRelations().empty());
}


TEST(Vic2World_Countries_CountryTests, RelationsCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tTWO =\n";
	theStream << "\t{\n";
	theStream << "\t\tvalue=42\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getRelations(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("TWO"), *Vic2::Relations::Builder().setValue(42).build())));
}


TEST(Vic2World_Countries_CountryTests, AiDefaultsToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getAI().getStrategies().empty());
}


TEST(Vic2World_Countries_CountryTests, AiCanBeImported)
{
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

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(1, country->getAI().getStrategies().size());
	ASSERT_EQ("protect", country->getAI().getStrategies()[0].getType());
	ASSERT_EQ("TWO", country->getAI().getStrategies()[0].getID());
	ASSERT_EQ(42, country->getAI().getStrategies()[0].getValue());
}

TEST(Vic2World_Countries_CountryTests, DefaultConquerStrategiesAreIgnored)
{
	std::stringstream theStream;
	theStream << "={\n";
	theStream << "\tai= {\n";
	theStream << "\t\tconquer_prov=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tid=\"1\"\n";
	theStream << "\t\t\tvalue=5\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->consolidateConquerStrategies(
		 {std::make_pair(1, Vic2::Province::Builder().setNumber(1).setOwner("TWO").build())});

	ASSERT_TRUE(country->getAI().getConsolidatedStrategies().empty());
}


TEST(Vic2World_Countries_CountryTests, AiConquerStrategiesCanBeConsolidated)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tai= {\n";
	theStream << "\t\tconquer_prov=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tid=\"1\"\n";
	theStream << "\t\t\tvalue=50\n";
	theStream << "\t\t}\n";
	theStream << "\t\tconquer_prov=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\tid=\"2\"\n";
	theStream << "\t\t\tvalue=71\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->consolidateConquerStrategies(
		 {std::make_pair(1, Vic2::Province::Builder().setNumber(1).setOwner("TWO").build()),
			  std::make_pair(2, Vic2::Province::Builder().setNumber(2).setOwner("TWO").build())});

	ASSERT_EQ(121, country->getAI().getConsolidatedStrategies().find("TWO")->second.value);
}


TEST(Vic2World_Countries_CountryTests, CivilizedDefaultsToFalse)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->isCivilized());
}


TEST(Vic2World_Countries_CountryTests, CivilizedCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcivilized = yes\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->isCivilized());
}


TEST(Vic2World_Countries_CountryTests, CivilizedNotSetWithoutYes)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcivilized = no\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->isCivilized());
}


TEST(Vic2World_Countries_CountryTests, ArmiesDefaultsToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getArmies().empty());
}


TEST(Vic2World_Countries_CountryTests, ArmiesCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tarmy=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"42nd Army\"\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(1, country->getArmies().size());
	ASSERT_EQ("42nd Army", country->getArmies()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, ArmiesCanBeModified)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tarmy=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"42nd Army\"\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	ASSERT_EQ(1, country->getModifiableArmies().size());
	country->getModifiableArmies()[0].setLocation(144);

	ASSERT_EQ(144, country->getArmies()[0].getLocation());
}


TEST(Vic2World_Countries_CountryTests, NaviesCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tnavy=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"42nd Fleet\"\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(1, country->getArmies().size());
	ASSERT_EQ("42nd Fleet", country->getArmies()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, TransportedArmiesCanBeAdded)
{
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

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(2, country->getArmies().size());
	ASSERT_EQ("42nd Army", country->getArmies()[0].getName());
	ASSERT_EQ("42nd Fleet", country->getArmies()[1].getName());
}


TEST(Vic2World_Countries_CountryTests, LeadersDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getLeaders().empty());
}


TEST(Vic2World_Countries_CountryTests, LeadersCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=land\n";
	theStream << "\t\t\tprestige=20\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  1.0,
										  std::nullopt);

	ASSERT_EQ(1, country->getLeaders().size());
	ASSERT_EQ(20, country->getLeaders()[0].getPrestige());
}


TEST(Vic2World_Countries_CountryTests, GeneralsAndAdmiralsAreLimited)
{
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
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t\t\tprestige=5\n";
	theStream << "\t}\n";
	theStream << "\tleader=\n";
	theStream << "\t{\n";
	theStream << "\t\t\tname=\"Probo Homo\"\n";
	theStream << "\t\t\ttype=sea\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.5F,
										  std::nullopt);

	ASSERT_EQ(2, country->getLeaders().size());
	ASSERT_EQ(20, country->getLeaders()[0].getPrestige());
	ASSERT_EQ(5, country->getLeaders()[1].getPrestige());
}


TEST(Vic2World_Countries_CountryTests, RevanchismDefaultsToZero)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NEAR(0.0, country->getRevanchism(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, RevanchismCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\trevanchism = 4.2\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NEAR(4.2, country->getRevanchism(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, WarExhaustionDefaultsToZero)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NEAR(0.0, country->getWarExhaustion(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, WarExhaustionCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\twar_exhaustion = 4.2\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NEAR(4.2, country->getWarExhaustion(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, BadBoyDefaultsToZero)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NEAR(0.0, country->getBadBoy(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, BadBoyCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tbadboy = 4.2\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NEAR(4.2, country->getBadBoy(), 0.0001);
}


TEST(Vic2World_Countries_CountryTests, FlagsDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getFlags().empty());
}


TEST(Vic2World_Countries_CountryTests, FlagsCanBeSet)
{
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

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getFlags(), testing::UnorderedElementsAre("test_flag_one", "test_flag_two", "test_flag_three"));
}


TEST(Vic2World_Countries_CountryTests, GovernmentDefaultsToBlank)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getGovernment().empty());
}


TEST(Vic2World_Countries_CountryTests, GovernmentCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tgovernment=test_government\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ("test_government", country->getGovernment());
}


TEST(Vic2World_Countries_CountryTests, UpperHouseCompositionDefaultsToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getUpperHouseComposition().empty());
}


TEST(Vic2World_Countries_CountryTests, UpperHouseCompositionCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tupper_house=\n";
	theStream << "\t{\n";
	theStream << "\t\tideology_one=0.25\n";
	theStream << "\t\tideology_two=0.625\n";
	theStream << "\t\tideology_three=0.125\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getUpperHouseComposition(),
		 testing::UnorderedElementsAre(testing::Pair(std::string("ideology_one"), 0.25),
			  testing::Pair(std::string("ideology_two"), 0.625),
			  testing::Pair(std::string("ideology_three"), 0.125)));
}


TEST(Vic2World_Countries_CountryTests, UpperHouseCompositionLogsErrorOnBadInput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tupper_house=\n";
	theStream << "\t{\n";
	theStream << "\t\tideology_one=not_a_number\n";
	theStream << "\t}\n";
	theStream << "}";

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);
	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(),
		 testing::HasSubstr("[WARNING] Malformed input while importing upper house composition for TAG"));
}


TEST(Vic2World_Countries_CountryTests, RulingPartyUnsetLogsWarning)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	std::stringstream theStream;
	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);
	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] TAG had no ruling party. The save may need manual repair."));
	ASSERT_EQ(std::nullopt, country->getRulingParty());
}


TEST(Vic2World_Countries_CountryTests, RulingPartyNonexistantThrowsException)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto countryFactory = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem));

	ASSERT_THROW(
		 {
			 try
			 {
				 countryFactory.createCountry("TAG",
					  theStream,
					  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
					  {},
					  *Vic2::StateLanguageCategories::Builder().build(),
					  0.05F,
					  std::nullopt);
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
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().setName("test_party").Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NE(std::nullopt, country->getRulingParty());
	ASSERT_EQ("test_party", country->getRulingParty()->getName());
}


TEST(Vic2World_Countries_CountryTests, RulingPartyNotSetForRebel)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("REB",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().setName("test_party").Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(std::nullopt, country->getRulingParty());
}


TEST(Vic2World_Countries_CountryTests, ActivePartiesDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getActiveParties().empty());
}


TEST(Vic2World_Countries_CountryTests, ActivePartiesCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tactive_party=1\n";
	theStream << "\tactive_party=3\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().setName("test_party_one").Build(),
												*Vic2::Party::Builder().setName("test_party_two").Build(),
												*Vic2::Party::Builder().setName("test_party_three").Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getActiveParties(),
		 testing::UnorderedElementsAre(*Vic2::Party::Builder().setName("test_party_one").Build(),
			  *Vic2::Party::Builder().setName("test_party_three").Build()));
}


TEST(Vic2World_Countries_CountryTests, ActivePartiesLoggedIfUndefined)
{
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tactive_party=1\n";
	theStream << "\tactive_party=3\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().setName("test_party_one").Build(),
												*Vic2::Party::Builder().setName("test_party_two").Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);
	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Party ID mismatch! Did some Vic2 country files not get read?"));
	ASSERT_THAT(country->getActiveParties(),
		 testing::UnorderedElementsAre(*Vic2::Party::Builder().setName("test_party_one").Build()));
}


TEST(Vic2World_Countries_CountryTests, ActivePartiesCanBecomeRulingPartyIfUnset)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\tactive_party=3\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().setName("test_party_one").Build(),
												*Vic2::Party::Builder().setName("test_party_two").Build(),
												*Vic2::Party::Builder().setName("test_party_three").Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_NE(std::nullopt, country->getRulingParty());
	ASSERT_EQ("test_party_three", country->getRulingParty()->getName());
}


TEST(Vic2World_Countries_CountryTests, LastElectionDefaultsToOneOneOne)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(date("1.1.1"), country->getLastElection());
}


TEST(Vic2World_Countries_CountryTests, LastElectionCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tlast_election=1942.11.6\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(date("1942.11.6"), country->getLastElection());
}


TEST(Vic2World_Countries_CountryTests, ShipNamesDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getAllShipNames().empty());
	ASSERT_TRUE(country->getShipNames("dreadnought").empty());
	ASSERT_TRUE(country->getShipNames("ironclad").empty());
}


TEST(Vic2World_Countries_CountryTests, ShipNamesCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	std::map<std::string, std::vector<std::string>> unit_names = {
		 {"dreadnought", std::vector<std::string>{"Azerbaijan", "Nader Shah"}},
		 {"ironclad", std::vector<std::string>{"Erivan", "Nakchivan"}}};

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{.unit_names_ = unit_names}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getAllShipNames(),
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"Azerbaijan", "Nader Shah"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
	ASSERT_THAT(country->getShipNames("dreadnought"), testing::UnorderedElementsAre("Azerbaijan", "Nader Shah"));
	ASSERT_THAT(country->getShipNames("ironclad"), testing::UnorderedElementsAre("Erivan", "Nakchivan"));
}


TEST(Vic2World_Countries_CountryTests, AtWarDefaultsToFalse)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->isAtWar());
}


TEST(Vic2World_Countries_CountryTests, AtWarCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->setAtWar();

	ASSERT_TRUE(country->isAtWar());
}


TEST(Vic2World_Countries_CountryTests, WarsDefaultToEmpty)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getWars().empty());
}


TEST(Vic2World_Countries_CountryTests, WarsCanBeAdded)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addWar(Vic2::War({}));

	ASSERT_FALSE(country->getWars().empty());
}


TEST(Vic2World_Countries_CountryTests, HasCoreOnCapitalFalseWithNoCores)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_FALSE(country->hasCoreOnCapital());
}


TEST(Vic2World_Countries_CountryTests, HasCoreOnCapitalFalseWithNoCoreOnCapital)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcapital = 42\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);
	country->addCore(Vic2::Province::Builder().setNumber(43).build());

	ASSERT_FALSE(country->hasCoreOnCapital());
}


TEST(Vic2World_Countries_CountryTests, HasCoreOnCapitalTrueWithCoreOnCapital)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tcapital = 42\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addCore(Vic2::Province::Builder().setNumber(42).build());


	ASSERT_TRUE(country->hasCoreOnCapital());
}


TEST(Vic2World_Countries_CountryTests, EmployedWorkersDefaultsToZero)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(0, country->getEmployedWorkers());
}


TEST(Vic2World_Countries_CountryTests, EmployedWorkersComeFromStates)
{
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

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addProvince(1,
		 Vic2::Province::Builder().setNumber(1).setPops({Pop(PopOptions{.type = "craftsmen", .size = 5})}).build());
	country->addProvince(2,
		 Vic2::Province::Builder().setNumber(2).setPops({Pop(PopOptions{.type = "craftsmen", .size = 7})}).build());
	country->putProvincesInStates();
	country->determineEmployedWorkers();

	ASSERT_EQ(12, country->getEmployedWorkers());
}


TEST(Vic2World_Countries_CountryTests, StateCategoriesCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate = {\n";
	theStream << "\t\tprovinces = { 42 }\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country =
		 Vic2::Country::Factory(mod_filesystem,
			  *Vic2::StateDefinitions::Builder().setProvinceToIDMap({{42, "TEST_STATE"}}).build(),
			  Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
			  .createCountry("TAG",
					theStream,
					Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
					std::vector{*Vic2::Party::Builder().Build()},
					*Vic2::StateLanguageCategories::Builder().setCategories({{"TEST_STATE", "TEST_CATEGORY"}}).build(),
					0.05F,
					std::nullopt);

	ASSERT_EQ(1, country->getStates().size());
	ASSERT_EQ("TEST_CATEGORY", country->getStates()[0].getLanguageCategory());
}


TEST(Vic2World_Countries_CountryTests, StateCategoriesLoggedWhenNotSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate = {\n";
	theStream << "\t\tprovinces = { 42 }\n";
	theStream << "\t}\n";
	theStream << "}";

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().setProvinceToIDMap({{42, "TEST_STATE"}}).build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_THAT(log.str(), testing::HasSubstr(" [WARNING] TEST_STATE was not in any language category.\n"));
}


TEST(Vic2World_Countries_CountryTests, IssueSupportDefaultsToZero)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(0, country->getAverageIssueSupport("test_issue"));
}


TEST(Vic2World_Countries_CountryTests, IssueSupportComesFromProvinces)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	country->addProvince(1,
		 Vic2::Province::Builder()
			  .setNumber(1)
			  .setPops({Pop(PopOptions{.size = 5, .popIssues{std::make_pair("test_issue", 0.5F)}})})
			  .build());

	ASSERT_EQ(0.5F, country->getAverageIssueSupport("test_issue"));
}


TEST(Vic2World_Countries_CountryTests, NameMissingByDefault)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(std::nullopt, country->getName("english"));
}


TEST(Vic2World_Countries_CountryTests, NameComesFromLocalisations)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Test Country"),
		 std::make_pair("spanish", "Pais de prueba")};
	const Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationNames(localisations);

	ASSERT_EQ("Test Country", country->getName("english"));
	ASSERT_EQ("Pais de prueba", country->getName("spanish"));
}


TEST(Vic2World_Countries_CountryTests, NameCanComeFromDomain)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tdomain_region=\"Test Region\"\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Test Country"),
		 std::make_pair("spanish", "Pais de prueba")};
	const Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationNames(localisations);

	ASSERT_EQ("Test Region", country->getName("english"));
	ASSERT_EQ("Test Region", country->getName("spanish"));
}


TEST(Vic2World_Countries_CountryTests, NameFromDomainUpdatesLocalisations)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tdomain_region=\"Test Region\"\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "$REGION$"),
		 std::make_pair("spanish", "$REGION$")};
	const Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG", nameInLanguages)};
	Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationNames(localisations);

	ASSERT_EQ("Test Region", localisations.getTextInLanguage("TAG", "english"));
	ASSERT_EQ("Test Region", localisations.getTextInLanguage("TAG", "spanish"));
}


TEST(Vic2World_Countries_CountryTests, AdjectiveMissingByDefault)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(std::nullopt, country->getAdjective("english"));
}


TEST(Vic2World_Countries_CountryTests, AdjectiveComesFromLocalisations)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Testy"),
		 std::make_pair("spanish", "Irascible")}; // yes, I know that's a different meaning than what I was going for.
																// The contrast amuses me.
	const Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG_ADJ", nameInLanguages)};
	const Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationAdjectives(localisations);

	ASSERT_EQ("Testy", country->getAdjective("english"));
	ASSERT_EQ("Irascible", country->getAdjective("spanish"));
}


TEST(Vic2World_Countries_CountryTests, AdjectiveCanComeFromDomain)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tdomain_region=\"Test Region\"\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	Vic2::LanguageToLocalisationMap nameInLanguages{std::make_pair("english", "Testy"),
		 std::make_pair("spanish", "Irascible")}; // yes, I know that's a different meaning than what I was going for.
																// The contrast amuses me.
	const Vic2::KeyToLocalisationsMap keyToLocalisations{std::make_pair("TAG_ADJ", nameInLanguages)};
	const Vic2::Localisations localisations{keyToLocalisations, {}};
	country->setLocalisationAdjectives(localisations);

	ASSERT_EQ("Test Region", country->getAdjective("english"));
	ASSERT_EQ("Test Region", country->getAdjective("spanish"));
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsStates)
{
	const auto stateDefinitions =
		 Vic2::StateDefinitions::Builder()
			  .setProvinceToIDMap({{1, "MERGE_STATE"}, {2, "MERGE_STATE"}, {3, "MERGE_STATE"}, {42, "UNMERGED_STATE"}})
			  .setStateMap({{1, {1, 2, 3}}, {2, {1, 2, 3}}, {3, {1, 2, 3}}, {42, {42}}})
			  .build();

	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate=\n";
	theStream << "\t{\n";
	theStream << "\t\tprovinces = { 1 }\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *stateDefinitions,
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "\tstate=\n";
	theStreamTwo << "\t{\n";
	theStreamTwo << "\t\tprovinces = { 2 3 }\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "\tstate=\n";
	theStreamTwo << "\t{\n";
	theStreamTwo << "\t\tprovinces = { 42 }\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *stateDefinitions,
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	ASSERT_EQ(1, country->getStates().size());
	country->eatCountry(*countryTwo, false);
	country->mergeStates(*stateDefinitions);

	ASSERT_EQ(2, country->getStates().size());
	ASSERT_EQ("TAG", country->getStates()[0].getOwner());
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsCores)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);
	countryTwo->addCore(Vic2::Province::Builder().setNumber(1).setCores({"TWO"}).build());
	countryTwo->addCore(Vic2::Province::Builder().setNumber(2).setCores({"TWO"}).build());

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
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder().setNumber(1).setOwner({"TWO"}).build();
	const std::shared_ptr<Vic2::Province> provinceTwo = Vic2::Province::Builder().setNumber(2).setOwner({"TWO"}).build();
	countryTwo->addProvince(1, provinceOne);
	countryTwo->addProvince(2, provinceTwo);

	ASSERT_FALSE(country->hasLand());
	country->eatCountry(*countryTwo, false);

	ASSERT_TRUE(country->hasLand());
	ASSERT_EQ("TAG", provinceOne->getOwner());
	ASSERT_EQ("TAG", provinceTwo->getOwner());
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsTechnologiesAndInventions)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "\ttechnology = {\n";
	theStreamTwo << "\t\ttechnology_one = {}\n";
	theStreamTwo << "\t\ttechnology_two = {}\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	ASSERT_TRUE(country->getTechnologiesAndInventions().empty());
	country->eatCountry(*countryTwo, false);

	ASSERT_THAT(country->getTechnologiesAndInventions(),
		 testing::UnorderedElementsAre("technology_one", "technology_two"));
}


TEST(Vic2World_Countries_CountryTests, EatCountryAbsorbsArmies)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "\tarmy=\n";
	theStreamTwo << "\t{\n";
	theStreamTwo << "\t\t\tname=\"42nd Army\"\n";
	theStreamTwo << "\t}\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	ASSERT_TRUE(country->getArmies().empty());
	country->eatCountry(*countryTwo, false);

	ASSERT_EQ(1, country->getArmies().size());
	ASSERT_EQ("42nd Army", country->getArmies()[0].getName());
}


TEST(Vic2World_Countries_CountryTests, EatCountryNoLoggingIfDebugOff)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	country->eatCountry(*countryTwo, false);
	std::cout.rdbuf(stdOutBuf);

	ASSERT_TRUE(log.str().empty());
}


TEST(Vic2World_Countries_CountryTests, EatCountryLogsIfDebugTrue)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	country->eatCountry(*countryTwo, true);
	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[DEBUG]     Merged TWO into TAG"));
}


TEST(Vic2World_Countries_CountryTests, EatCountryHasNoEffectOnSelf)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate=\n";
	theStream << "\t{\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	ASSERT_EQ(1, country->getStates().size());
	country->eatCountry(*country, false);

	ASSERT_EQ(1, country->getStates().size());
}


TEST(Vic2World_Countries_CountryTests, ProvincesCanBePlacedInStates)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate=\n";
	theStream << "\t{\n";
	theStream << "\t\tprovinces=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\t1\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);
	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder().setNumber(1).build();
	country->addProvince(1, provinceOne);
	country->putProvincesInStates();

	ASSERT_THAT(country->getStates()[0].getProvinces(), testing::UnorderedElementsAre(provinceOne));
}


TEST(Vic2World_Countries_CountryTests, MissingProvinceInStateLogged)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "\tstate=\n";
	theStream << "\t{\n";
	theStream << "\t\tprovinces=\n";
	theStream << "\t\t{\n";
	theStream << "\t\t\t42\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
							 .createCountry("TAG",
								  theStream,
								  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
								  std::vector{*Vic2::Party::Builder().Build()},
								  *Vic2::StateLanguageCategories::Builder().build(),
								  0.05F,
								  std::nullopt);

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());
	country->putProvincesInStates();
	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] State () owned by TAG had province (42) that TAG did not"));
}


TEST(Vic2World_Countries_CountryTests, SameTagsMakeEqualCountries)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";
	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TAG",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	ASSERT_EQ(*country, *countryTwo);
}


TEST(Vic2World_Countries_CountryTests, DifferentTagsMakeUnequalCountries)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	std::stringstream theStreamTwo;
	theStreamTwo << "= {\n";
	theStreamTwo << "\truling_party = 1\n";
	theStreamTwo << "}";

	const auto countryTwo = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
										 .createCountry("TWO",
											  theStreamTwo,
											  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
											  std::vector{*Vic2::Party::Builder().Build()},
											  *Vic2::StateLanguageCategories::Builder().build(),
											  0.05F,
											  std::nullopt);

	ASSERT_FALSE(*country == *countryTwo);
}


TEST(Vic2World_Countries_CountryTests, DynastyDefaultsToNullopt)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(std::nullopt, country->getLastDynasty());
}


TEST(Vic2World_Countries_CountryTests, MonarchDefaultsToNullopt)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_EQ(std::nullopt, country->getLastMonarch());
}


TEST(Vic2World_Countries_CountryTests, DynastyImportedFromCountryData)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  *Vic2::CountryData::Builder().setLastDynasty("test_dynasty").Build());

	ASSERT_EQ("test_dynasty", country->getLastDynasty());
}


TEST(Vic2World_Countries_CountryTests, MonarchImportedFromCountryData)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1\n";
	theStream << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  theStream,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  *Vic2::CountryData::Builder().setLastMonarch("test_monarch").Build());

	ASSERT_EQ("test_monarch", country->getLastMonarch());
}


TEST(Vic2World_Countries_CountryTests, GoodsStockpileDefaultsToEmpty)
{
	std::stringstream input;

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  input,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_TRUE(country->getGoodsStockpile().empty());
}


TEST(Vic2World_Countries_CountryTests, GoodsStockpileIsReturned)
{
	std::stringstream input;
	input << "stockpile=\n";
	input << "{\n";
	input << "\ttest_good = 4.2\n";
	input << "}";

	const commonItems::ModFilesystem mod_filesystem("countries/blank", {});
	const auto country = Vic2::Country::Factory(mod_filesystem,
		 *Vic2::StateDefinitions::Builder().build(),
		 Vic2::CultureGroups::Factory().GetCultureGroups(mod_filesystem))
									 .createCountry("TAG",
										  input,
										  Vic2::CommonCountryData(Vic2::CommonCountryDataOptions{}),
										  std::vector{*Vic2::Party::Builder().Build()},
										  *Vic2::StateLanguageCategories::Builder().build(),
										  0.05F,
										  std::nullopt);

	ASSERT_THAT(country->getGoodsStockpile(), testing::UnorderedElementsAre(testing::Pair("test_good", 4.2F)));
}