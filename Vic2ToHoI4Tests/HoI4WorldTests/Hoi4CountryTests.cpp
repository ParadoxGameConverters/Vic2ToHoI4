#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/HoI4Country.h"
#include "../Vic2ToHoI4/Source/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Mocks/CountryMapperMock.h"
#include "../Mocks/GraphicsMapperMock.h"
#include "../Mocks/NamesMapperMock.h"
#include "../Mocks/Vic2CountryMock.h"
#include <sstream>


class HoI4World_HoI4CountryTests: public ::testing::Test
{
	protected:
		HoI4World_HoI4CountryTests();

		mockNamesMapper theNamesMapper;
		mockGraphicsMapper theGraphicsMapper;
		mockCountryMapper theCountryMapper;
		mockVic2Country sourceCountry;
		std::unique_ptr<mappers::FlagsToIdeasMapper> theflagsToIdeasMapper;
};


HoI4World_HoI4CountryTests::HoI4World_HoI4CountryTests()
{
	std::stringstream input;
	theflagsToIdeasMapper = std::make_unique<mappers::FlagsToIdeasMapper>(input);
}



TEST_F(HoI4World_HoI4CountryTests, tagCanBeAssigned)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return(""));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);
	ASSERT_EQ(theCountry.getTag(), "TAG");
}