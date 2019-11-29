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
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return(std::nullopt));

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


TEST_F(HoI4World_HoI4CountryTests, filenamesDefaultToTag)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return(std::nullopt));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);
	ASSERT_EQ(theCountry.getFilename(), "TAG.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "TAG.txt");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesBasedOnSourceCountryName)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return("source country name"));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);
	ASSERT_EQ(theCountry.getFilename(), "TAG - source country name.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "source country name.txt");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesReplaceBadCharacters)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return("hardname|><"));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);
	ASSERT_EQ(theCountry.getFilename(), "TAG - hardname.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "hardname.txt");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesConvertFrom1252ToUtf8)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return("1252Ç"));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.getFilename(), "TAG - 1252\xC3\x87.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "1252\xC3\x87.txt");
}


TEST_F(HoI4World_HoI4CountryTests, isHumanDefaultsToFalse)
{
	EXPECT_CALL(sourceCountry, isHuman()).WillOnce(testing::Return(false));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.isHuman(), false);
}


TEST_F(HoI4World_HoI4CountryTests, isHumanCanBetSetTrue)
{
	EXPECT_CALL(sourceCountry, isHuman()).WillOnce(testing::Return(true));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theflagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.isHuman(), true);
}