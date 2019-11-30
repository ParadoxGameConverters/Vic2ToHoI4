#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/HoI4Country.h"
#include "../Vic2ToHoI4/Source/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Mocks/CountryMapperMock.h"
#include "../Mocks/GraphicsMapperMock.h"
#include "../Mocks/Hoi4StateMock.h"
#include "../Mocks/NamesMapperMock.h"
#include "../Mocks/ProvinceMapperMock.h"
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
		std::unique_ptr<mappers::FlagsToIdeasMapper> theFlagsToIdeasMapper;

		ConverterColor::Color defaultColor;
};


HoI4World_HoI4CountryTests::HoI4World_HoI4CountryTests()
{
	std::stringstream input;
	theFlagsToIdeasMapper = std::make_unique<mappers::FlagsToIdeasMapper>(input);

	ON_CALL(theGraphicsMapper, getGraphicalCulture).WillByDefault(testing::Return(std::nullopt));
	ON_CALL(theGraphicsMapper, get2dGraphicalCulture).WillByDefault(testing::Return(std::nullopt));

	ON_CALL(sourceCountry, getName).WillByDefault(testing::Return(std::nullopt));
	ON_CALL(sourceCountry, isHuman).WillByDefault(testing::Return(false));
	ON_CALL(sourceCountry, getColor).WillByDefault(testing::ReturnRef(defaultColor));
	ON_CALL(sourceCountry, getPrimaryCultureGroup).WillByDefault(testing::Return(""));
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
		*theFlagsToIdeasMapper
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
		*theFlagsToIdeasMapper
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
		*theFlagsToIdeasMapper
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
		*theFlagsToIdeasMapper
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
		*theFlagsToIdeasMapper
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
		*theFlagsToIdeasMapper
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
		*theFlagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.isHuman(), true);
}


TEST_F(HoI4World_HoI4CountryTests, colorIsFromSourceCountry)
{
	ConverterColor::Color testColor(
		ConverterColor::red(33),
		ConverterColor::green(66),
		ConverterColor::blue(99)
	);
	EXPECT_CALL(sourceCountry, getColor()).WillOnce(testing::ReturnRef(testColor));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.getColor(), testColor);
}


TEST_F(HoI4World_HoI4CountryTests, graphicalCultureDefaultsToWesternEuropean)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.getGraphicalCulture(), "western_european_gfx");
	ASSERT_EQ(theCountry.getGraphicalCulture2d(), "western_european_2d");
}


TEST_F(HoI4World_HoI4CountryTests, graphicalCultureIsFromSourceCountryCultureGroup)
{
	EXPECT_CALL(sourceCountry, getPrimaryCultureGroup).WillRepeatedly(testing::Return("testCultureGroup"));
	EXPECT_CALL(
		theGraphicsMapper,
		getGraphicalCulture("testCultureGroup")).WillOnce(testing::Return("testGraphicalCulture")
	);
	EXPECT_CALL(
		theGraphicsMapper,
		get2dGraphicalCulture("testCultureGroup")).WillOnce(testing::Return("test2dGraphicalCulture")
	);

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.getGraphicalCulture(), "testGraphicalCulture");
	ASSERT_EQ(theCountry.getGraphicalCulture2d(), "test2dGraphicalCulture");
}


TEST_F(HoI4World_HoI4CountryTests, hasProvincesDefaultsToFalse)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_FALSE(theCountry.hasProvinces());
}


TEST_F(HoI4World_HoI4CountryTests, getProvincesDefaultsToEmpty)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_TRUE(theCountry.getProvinces().empty());
}


TEST_F(HoI4World_HoI4CountryTests, provincesCanBeAdded)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockHoi4State state("TAG");
	EXPECT_CALL(state, getID).WillOnce(testing::Return(0));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::Return(std::set<int>{1,2,3}));

	theCountry.addState(state);

	ASSERT_TRUE(theCountry.hasProvinces());
	ASSERT_TRUE(theCountry.getProvinces().contains(1));
	ASSERT_TRUE(theCountry.getProvinces().contains(2));
	ASSERT_TRUE(theCountry.getProvinces().contains(3));
}


TEST_F(HoI4World_HoI4CountryTests, getStatesDefaultsToEmpty)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_TRUE(theCountry.getStates().empty());
}


TEST_F(HoI4World_HoI4CountryTests, statesCanBeAdded)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockHoi4State state("");
	EXPECT_CALL(state, getID).WillOnce(testing::Return(42));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::Return(std::set<int>{}));

	theCountry.addState(state);

	ASSERT_TRUE(theCountry.getStates().contains(42));
}


TEST_F(HoI4World_HoI4CountryTests, capitalDefaultsToNone)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	ASSERT_EQ(theCountry.getCapitalState(), std::nullopt);
	ASSERT_EQ(theCountry.getCapitalProvince(), std::nullopt);
}


TEST_F(HoI4World_HoI4CountryTests, capitalCanBeSetInOwnedState)
{
	EXPECT_CALL(sourceCountry, getCapital).WillOnce(testing::Return(42));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockHoi4State state("TAG");
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::Return(std::set<int>{84}));
	std::string owner = state.getOwner();

	std::map<int, HoI4::State> allStates;
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(84, 1));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(42)).WillOnce(testing::Return(std::vector<int>{84}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 84);
}