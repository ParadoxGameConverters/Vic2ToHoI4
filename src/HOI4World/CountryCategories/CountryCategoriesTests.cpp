#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/CountryCategories/CountryCategories.h"
#include "src/Mappers/Country/CountryMapperBuilder.h"



TEST(HoI4World_CountryCategories_CountryCategoriesTests, CategoriesCanBeCreated)
{
	const auto categories = HoI4::createCountryCategories(*Mappers::CountryMapper::Builder()
																				 .addMapping("BAN", "BAN")
																				 .addMapping("ENG", "ENG")
																				 .addMapping("BGL", "BGL")
																				 .Build(),
		 {},
		 {"absolutist", "democratic"},
		 false);

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(
			  testing::Pair("tag_mscad",
					testing::UnorderedElementsAre(testing::Pair("BAN", std::nullopt),
						 testing::Pair("ENG",
							  std::optional<std::string>(
									"NOT = { has_government = absolutist has_government = democratic }")))),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre(testing::Pair("BGL", std::nullopt)))));
}


TEST(HoI4World_CountryCategories_CountryCategoriesTests, TagsAreTranslated)
{
	const auto categories = HoI4::createCountryCategories(*Mappers::CountryMapper::Builder()
																				 .addMapping("BAN", "B2N")
																				 .addMapping("ENG", "EN2")
																				 .addMapping("BGL", "BG2")
																				 .Build(),
		 {},
		 {"absolutist", "democratic"},
		 false);

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(
			  testing::Pair("tag_mscad",
					testing::UnorderedElementsAre(testing::Pair("B2N", std::nullopt),
						 testing::Pair("EN2",
							  std::optional<std::string>(
									"NOT = { has_government = absolutist has_government = democratic }")))),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre(testing::Pair("BG2", std::nullopt)))));
}


TEST(HoI4World_CountryCategories_CountryCategoriesTests, UnmappedTagsAreSkipped)
{
	const auto categories = HoI4::createCountryCategories(*Mappers::CountryMapper::Builder().Build(), {}, {}, false);

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(testing::Pair("tag_mscad", testing::UnorderedElementsAre()),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre())));
}


TEST(HoI4World_CountryCategories_CountryCategoriesTests, UncategorizedCountriesAreInTagMscne)
{
	const auto categories =
		 HoI4::createCountryCategories(*Mappers::CountryMapper::Builder().Build(), {{"TAG", nullptr}}, {}, false);

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(
			  testing::Pair("tag_mscne", testing::UnorderedElementsAre(testing::Pair("TAG", std::nullopt))),
			  testing::Pair("tag_mscad", testing::UnorderedElementsAre()),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre())));
}


TEST(HoI4World_CountryCategories_CountryCategoriesTests, UncategorizedCountriesAreLoggedWhenDebugIsTrue)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto categories =
		 HoI4::createCountryCategories(*Mappers::CountryMapper::Builder().Build(), {{"TAG", nullptr}}, {}, true);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(),
		 testing::HasSubstr("[WARNING] TAG was not in any language category. Defaulting to tag_mscne"));
}


TEST(HoI4World_CountryCategories_CountryCategoriesTests, MissingIdeologiesAreRemovedFromExtras)
{
	const auto categories = HoI4::createCountryCategories(*Mappers::CountryMapper::Builder()
																				 .addMapping("BAN", "BAN")
																				 .addMapping("ENG", "ENG")
																				 .addMapping("BGL", "BGL")
																				 .Build(),
		 {},
		 {"absolutist"},
		 false);

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(
			  testing::Pair("tag_mscad",
					testing::UnorderedElementsAre(testing::Pair("BAN", std::nullopt),
						 testing::Pair("ENG", std::optional<std::string>("NOT = { has_government = absolutist }")))),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre(testing::Pair("BGL", std::nullopt)))));
}


TEST(HoI4World_CountryCategories_CountryCategoriesTests, MissingIdeologiesCanTurnExtraToNullopt)
{
	const auto categories = HoI4::createCountryCategories(*Mappers::CountryMapper::Builder()
																				 .addMapping("BAN", "BAN")
																				 .addMapping("ENG", "ENG")
																				 .addMapping("BGL", "BGL")
																				 .Build(),
		 {},
		 {},
		 false);

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(
			  testing::Pair("tag_mscad",
					testing::UnorderedElementsAre(testing::Pair("BAN", std::nullopt), testing::Pair("ENG", std::nullopt))),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre(testing::Pair("BGL", std::nullopt)))));
}