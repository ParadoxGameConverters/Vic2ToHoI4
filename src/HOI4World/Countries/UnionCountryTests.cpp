#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Countries/UnionCountry.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/Country/CountryMapperBuilder.h"
#include "src/V2World/Countries/CountryBuilder.h"
#include "src/V2World/Culture/CultureGroup.h"
#include "gmock/gmock-matchers.h"
#include <map>



TEST(HoI4World_Countries_UnionCountryTests, TagIsFromCountryMapping)
{
	const auto vic2_country = Vic2::Country::Builder{}.SetTag("TAG").Build();
	const Vic2::CultureGroups culture_groups;
	const auto country_mapper = Mappers::CountryMapper::Builder{}.addMapping("TAG", "MAP").Build();

	const HoI4::UnionCountry union_country(*vic2_country, culture_groups, *country_mapper);

	EXPECT_EQ(union_country.GetTag(), "MAP_union");
}


TEST(HoI4World_Countries_UnionCountryTests, TagIsFromSourceCountryIfNoMapping)
{
	const auto vic2_country = Vic2::Country::Builder{}.SetTag("TAG").Build();
	const Vic2::CultureGroups culture_groups;
	const auto country_mapper = Mappers::CountryMapper::Builder{}.Build();

	const HoI4::UnionCountry union_country(*vic2_country, culture_groups, *country_mapper);

	EXPECT_EQ(union_country.GetTag(), "TAG_union");
}


TEST(HoI4World_Countries_UnionCountryTests, OldTagIsStored)
{
	const auto vic2_country = Vic2::Country::Builder{}.SetTag("TAG").Build();
	const Vic2::CultureGroups culture_groups;
	const auto country_mapper = Mappers::CountryMapper::Builder{}.Build();

	const HoI4::UnionCountry union_country(*vic2_country, culture_groups, *country_mapper);

	EXPECT_EQ(union_country.GetOldTag(), "TAG");
}

TEST(HoI4World_Countries_UnionCountryTests, ColorIsFromSourceCountry)
{
	const commonItems::Color test_color(std::array<int, 3>{3, 6, 9});
	const auto vic2_country = Vic2::Country::Builder{}.setColor(test_color).Build();
	const Vic2::CultureGroups culture_groups;
	const auto country_mapper = Mappers::CountryMapper::Builder{}.Build();

	const HoI4::UnionCountry union_country(*vic2_country, culture_groups, *country_mapper);

	EXPECT_EQ(union_country.GetColor(), test_color);
}


TEST(HoI4World_Countries_UnionCountryTests, CulturesAreFromCultureGroups)
{
	const auto vic2_country = Vic2::Country::Builder{}.SetTag("TAG").Build();
	const Vic2::CultureGroups culture_groups({}, {{"TAG", {"test_culture_one", "test_culture_two"}}});
	const auto country_mapper = Mappers::CountryMapper::Builder{}.Build();

	const HoI4::UnionCountry union_country(*vic2_country, culture_groups, *country_mapper);

	EXPECT_THAT(union_country.GetCultures(), testing::UnorderedElementsAre("test_culture_one", "test_culture_two"));
}