#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/HoI4Country.h"
#include "../Vic2ToHoI4/Source/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Mocks/CountryMapperMock.h"
#include "../Mocks/GraphicsMapperMock.h"
#include "../Mocks/NamesMapperMock.h"
#include "../Mocks/Vic2CountryMock.h"
#include <sstream>



TEST(HoI4World_HoI4CountryTests, tagCanBeAssigned)
{
	mockNamesMapper theNamesMapper;
	mockGraphicsMapper theGraphicsMapper;
	mockCountryMapper theCountryMapper;

	mockVic2Country sourceCountry;
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return(""));

	std::stringstream input;
	mappers::FlagsToIdeasMapper theflagsToIdeasMapper(input);

	
	HoI4::Country theCountry("TAG", &sourceCountry, theNamesMapper, theGraphicsMapper, theCountryMapper, theflagsToIdeasMapper);
	ASSERT_EQ(theCountry.getTag(), "TAG");
}