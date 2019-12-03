#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/HoI4Country.h"
#include "../Vic2ToHoI4/Source/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Vic2ToHoI4/Source/V2World/Party.h"
#include "../Mocks/CountryMapperMock.h"
#include "../Mocks/GovermentMapperMock.h"
#include "../Mocks/GraphicsMapperMock.h"
#include "../Mocks/Hoi4StateMock.h"
#include "../Mocks/NamesMapperMock.h"
#include "../Mocks/ProvinceMapperMock.h"
#include "../Mocks/Vic2CountryMock.h"
#include "../Mocks/Vic2WorldMock.h"
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
	ON_CALL(sourceCountry, getTag).WillByDefault(testing::Return("TAG"));
	ON_CALL(sourceCountry, getGovernment).WillByDefault(testing::Return("testGovernment"));
}


TEST_F(HoI4World_HoI4CountryTests, tagCanBeAssigned)
{
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
		getGraphicalCulture("testCultureGroup")
	).WillOnce(testing::Return("testGraphicalCulture"));
	EXPECT_CALL(
		theGraphicsMapper,
		get2dGraphicalCulture("testCultureGroup")
	).WillOnce(testing::Return("test2dGraphicalCulture"));

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


TEST_F(HoI4World_HoI4CountryTests, capitalSetInFirstOwnedStateIfFirstChoiceIsImpassible)
{
	EXPECT_CALL(sourceCountry, getCapital).WillOnce(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("TAG");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("TAG");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("TAG");
	state3.addCores(std::set<std::string>{"TAG"});
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillOnce(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalSetInFirstOwnedStateIfFirstChoiceNotOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillOnce(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("TAG");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("TAG");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("NON");
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillOnce(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalCanGoInPreferredWastelandIfOnlyWastelandOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("TAG");
	state.makeImpassable();
	state.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("TAG");
	state2.makeImpassable();
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("TAG");
	state3.makeImpassable();
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 3);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
}


TEST_F(HoI4World_HoI4CountryTests, capitalCanGoInOtherWastelandIfOnlyWastelandOwnedAndPreferredNotOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("TAG");
	state.makeImpassable();
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("TAG");
	state2.makeImpassable();
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("NON");
	state3.makeImpassable();
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToCoredPreferredIfNoneOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("NON");
	state.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("NON");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("NON");
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 3);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToCoredNonWastelandIfNoneOwnedAndPreferredIsWasteland)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("NON");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("NON");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("NON");
	state3.addCores(std::set<std::string>{"TAG"});
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToPreferredWastelandIfNoneOwnedAndAllWasteland)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("NON");
	state.addCores(std::set<std::string>{"TAG"});
	state.makeImpassable();
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("NON");
	state2.addCores(std::set<std::string>{"TAG"});
	state2.makeImpassable();
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("NON");
	state3.addCores(std::set<std::string>{"TAG"});
	state3.addProvince(30);
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 3);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToAnyWastelandIfNoneOwnedAllWastelandAndPreferredNotCored)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state("NON");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	state.makeImpassable();
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2("NON");
	state2.addCores(std::set<std::string>{"TAG"});
	state2.makeImpassable();
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3("NON");
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalRemainsUnassignedIfNoCoresAndNoOwnedProvince)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	std::map<int, HoI4::State> allStates;
	mockHoi4State state3("NON");
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mockProvinceMapper aProvinceMapper;
	EXPECT_CALL(aProvinceMapper, getVic2ToHoI4ProvinceMapping(3)).WillRepeatedly(testing::Return(std::vector<int>{30}));

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_EQ(theCountry.getCapitalState(), std::nullopt);
	ASSERT_EQ(theCountry.getCapitalProvince(), std::nullopt);
}


TEST_F(HoI4World_HoI4CountryTests, governmentIdeologiesDefaultsToNeutrality)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);
	ASSERT_EQ(theCountry.getGovernmentIdeology(), "neutrality");
	ASSERT_EQ(theCountry.getLeaderIdeology(), "conservatism_neutral");
}


TEST_F(HoI4World_HoI4CountryTests, governmentIdeologiesCanBeSet)
{
	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology";
	Vic2::Party testParty(partyInput);

	std::vector<Vic2::Party> testParties{ testParty };
	EXPECT_CALL(
		sourceCountry,
		getRulingParty(testParties)
	).WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(
		mockGovernmentMap,
		getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
			.WillOnce(testing::Return("testGovernmentIdeology")
	);
	EXPECT_CALL(
		mockGovernmentMap,
		getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
			.WillOnce(testing::Return("testLeaderIdeology")
	);

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap);
	ASSERT_EQ(theCountry.getGovernmentIdeology(), "testGovernmentIdeology");
	ASSERT_EQ(theCountry.getLeaderIdeology(), "testLeaderIdeology");
}


TEST_F(HoI4World_HoI4CountryTests, rulingPartyComesFromVic2Country)
{
	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology";
	Vic2::Party testParty(partyInput);

	std::vector<Vic2::Party> testParties{ testParty };
	EXPECT_CALL(
		sourceCountry,
		getRulingParty(testParties)
	).WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(
		mockGovernmentMap,
		getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		.WillOnce(testing::Return("testGovernmentIdeology")
		);
	EXPECT_CALL(
		mockGovernmentMap,
		getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		.WillOnce(testing::Return("testLeaderIdeology")
		);

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap);
	ASSERT_EQ(theCountry.getRulingParty(), testParty);
}


TEST_F(HoI4World_HoI4CountryTests, missingRulingPartyThrowsException)
{
	std::vector<Vic2::Party> testParties{ };
	EXPECT_CALL(
		sourceCountry,
		getRulingParty(testParties)
	).WillOnce(testing::Return(std::nullopt));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;

	EXPECT_THROW(theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap), std::runtime_error);
}


TEST_F(HoI4World_HoI4CountryTests, partiesDefaultsToEmpty)
{
	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	EXPECT_TRUE(theCountry.getParties().empty());
}


TEST_F(HoI4World_HoI4CountryTests, partiesComeFromVic2Country)
{
	std::stringstream partyInput;
	partyInput << "name = TAG_testParty\n";
	partyInput << "ideology = testSourceIdeology";
	Vic2::Party testParty(partyInput);

	std::stringstream partyInput2;
	partyInput2 << "name = TAG_testParty2\n";
	partyInput2 << "ideology = testSourceIdeology";
	Vic2::Party testParty2(partyInput2);

	std::vector<Vic2::Party> testParties{ testParty, testParty2 };
	EXPECT_CALL(
		sourceCountry,
		getRulingParty(testParties)
	).WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	set<Vic2::Party, function<bool(const Vic2::Party&, const Vic2::Party&)>> activeParties([](const Vic2::Party& first, const Vic2::Party& second)
		{ return first.getName() < second.getName(); }
	);
	activeParties.insert(testParty);
	activeParties.insert(testParty2);
	EXPECT_CALL(
		sourceCountry,
		getActiveParties(testParties)
	).WillOnce(testing::Return(activeParties));

	HoI4::Country theCountry(
		"TAG",
		&sourceCountry,
		theNamesMapper,
		theGraphicsMapper,
		theCountryMapper,
		*theFlagsToIdeasMapper
	);

	mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(
		mockGovernmentMap,
		getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		.WillOnce(testing::Return("testGovernmentIdeology")
		);
	EXPECT_CALL(
		mockGovernmentMap,
		getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		.WillOnce(testing::Return("testLeaderIdeology")
		);

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap);
	ASSERT_EQ(theCountry.getParties().count(testParty), 1);
	ASSERT_EQ(theCountry.getParties().count(testParty2), 1);
}