#include "Mappers/Country/CountryMapperBuilder.h"
#include "Mappers/Country/CountryMapper.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Mappers_Country_CountryMapperTests, UnmatchedVic2TagReturnsNullopt)
{
	const auto mapper = Mappers::CountryMapper::Builder().Build();

	ASSERT_EQ(mapper->getHoI4Tag("NON"), std::nullopt);
}


TEST(Mappers_Country_CountryMapperTests, MatchedVic2TagReturnsHoI4Tag)
{
	const auto mapper = Mappers::CountryMapper::Builder().addMapping("VIC", "HOI").Build();

	ASSERT_EQ(mapper->getHoI4Tag("VIC"), "HOI");
}