#include "HOI4World/CountryCategories/CountryCategories.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(HoI4World_CountryCategories_CountryCategoriesTests, CategoriesCanBeCreated)
{
	const auto categories = HoI4::createCountryCategories();

	ASSERT_THAT(categories,
		 testing::UnorderedElementsAre(
			  testing::Pair("tag_mscad",
					testing::UnorderedElementsAre(testing::Pair("BAN", std::nullopt),
						 testing::Pair("ENG",
							  std::optional<std::string>("NOT = { has_government = absolutism has_government = democratic "
																  "has_government = democratic }")))),
			  testing::Pair("tag_mscae", testing::UnorderedElementsAre(testing::Pair("BGL", std::nullopt)))));
}