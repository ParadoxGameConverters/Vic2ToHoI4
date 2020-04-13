#include "../Mocks/CountryMapperMock.h"
#include "../Mocks/GovermentMapperMock.h"
#include "../Mocks/GraphicsMapperMock.h"
#include "../Mocks/Hoi4StateMock.h"
#include "../Mocks/NamesMapperMock.h"
#include "../Mocks/Vic2CountryMock.h"
#include "../Mocks/Vic2WorldMock.h"
#include "../Vic2ToHoI4/Source/HOI4World/HoI4Country.h"
#include "../Vic2ToHoI4/Source/HOI4World/HoI4Localisation.h"
#include "../Vic2ToHoI4/Source/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../Vic2ToHoI4/Source/V2World/Party.h"
#include "../Vic2ToHoI4/Source/V2World/State.h"
#include "../Vic2ToHoI4/Source/V2World/Vic2Localisations.h"
#include "gtest/gtest.h"
#include <sstream>



class HoI4World_HoI4CountryTests: public testing::Test
{
  protected:
	HoI4World_HoI4CountryTests();

	mockNamesMapper theNamesMapper;
	mockGraphicsMapper theGraphicsMapper;
	mockCountryMapper theCountryMapper;
	mockVic2Country sourceCountry;
	std::unique_ptr<mappers::FlagsToIdeasMapper> theFlagsToIdeasMapper;

	ConverterColor::Color defaultColor;

	std::unique_ptr<Vic2::Localisations> vic2Localisations;
	std::unique_ptr<HoI4::Localisation> hoi4Localisations;
};


HoI4World_HoI4CountryTests::HoI4World_HoI4CountryTests()
{
	std::stringstream input;
	theFlagsToIdeasMapper = std::make_unique<mappers::FlagsToIdeasMapper>(input);

	Vic2::KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
	vic2Localisations = std::make_unique<Vic2::Localisations>(localisations, localisationToKeyMap);

	Configuration theConfiguration("",
		 "",
		 {},
		 0.0,
		 0.0,
		 0.0,
		 0.0,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false,
		 HoI4::Version());
	hoi4Localisations = HoI4::Localisation::Importer{}.generateLocalisations(theConfiguration);

	ON_CALL(theGraphicsMapper, getGraphicalCulture).WillByDefault(testing::Return(std::nullopt));
	ON_CALL(theGraphicsMapper, get2dGraphicalCulture).WillByDefault(testing::Return(std::nullopt));

	ON_CALL(sourceCountry, getName).WillByDefault(testing::Return(std::nullopt));
	ON_CALL(sourceCountry, isHuman).WillByDefault(testing::Return(false));
	ON_CALL(sourceCountry, getColor).WillByDefault(testing::ReturnRef(defaultColor));
	ON_CALL(sourceCountry, getPrimaryCultureGroup).WillByDefault(testing::Return(""));
	ON_CALL(sourceCountry, getTag).WillByDefault(testing::Return("TAG"));
	ON_CALL(sourceCountry, getGovernment).WillByDefault(testing::Return("testGovernment"));
	ON_CALL(sourceCountry, getProvinces()).WillByDefault(testing::Return(std::map<int, Vic2::Province*>{}));
	ON_CALL(sourceCountry, getRevanchism()).WillByDefault(testing::Return(0));
	ON_CALL(sourceCountry, getWarExhaustion()).WillByDefault(testing::Return(0));
	ON_CALL(sourceCountry, getAverageIssueSupport("jingoism")).WillByDefault(testing::Return(0.0f));
	ON_CALL(sourceCountry, getAverageIssueSupport("pro_military")).WillByDefault(testing::Return(0.0f));
	ON_CALL(sourceCountry, getAverageIssueSupport("anti_military")).WillByDefault(testing::Return(0.0f));
	ON_CALL(sourceCountry, getAverageIssueSupport("pacifism")).WillByDefault(testing::Return(0.0f));
	ON_CALL(sourceCountry, isAtWar()).WillByDefault(testing::Return(false));
}


TEST_F(HoI4World_HoI4CountryTests, tagCanBeAssigned)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);
	ASSERT_EQ(theCountry.getTag(), "TAG");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesDefaultToTag)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);
	ASSERT_EQ(theCountry.getFilename(), "TAG.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "TAG.txt");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesBasedOnSourceCountryName)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return("source country name"));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);
	ASSERT_EQ(theCountry.getFilename(), "TAG - source country name.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "source country name.txt");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesReplaceBadCharacters)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return("hardname|><"));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);
	ASSERT_EQ(theCountry.getFilename(), "TAG - hardname.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "hardname.txt");
}


TEST_F(HoI4World_HoI4CountryTests, filenamesConvertFrom1252ToUtf8)
{
	EXPECT_CALL(sourceCountry, getName("english")).WillOnce(testing::Return("1252Ç"));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getFilename(), "TAG - 1252\xC3\x87.txt");
	ASSERT_EQ(theCountry.getCommonCountryFile(), "1252\xC3\x87.txt");
}


TEST_F(HoI4World_HoI4CountryTests, isHumanDefaultsToFalse)
{
	EXPECT_CALL(sourceCountry, isHuman()).WillOnce(testing::Return(false));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.isHuman(), false);
}


TEST_F(HoI4World_HoI4CountryTests, isHumanCanBetSetTrue)
{
	EXPECT_CALL(sourceCountry, isHuman()).WillOnce(testing::Return(true));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.isHuman(), true);
}


TEST_F(HoI4World_HoI4CountryTests, colorIsFromSourceCountry)
{
	ConverterColor::Color testColor(ConverterColor::red(33), ConverterColor::green(66), ConverterColor::blue(99));
	EXPECT_CALL(sourceCountry, getColor()).WillOnce(testing::ReturnRef(testColor));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getColor(), testColor);
}


TEST_F(HoI4World_HoI4CountryTests, graphicalCultureDefaultsToWesternEuropean)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getGraphicalCulture(), "western_european_gfx");
	ASSERT_EQ(theCountry.getGraphicalCulture2d(), "western_european_2d");
}


TEST_F(HoI4World_HoI4CountryTests, graphicalCultureIsFromSourceCountryCultureGroup)
{
	EXPECT_CALL(sourceCountry, getPrimaryCultureGroup).WillRepeatedly(testing::Return("testCultureGroup"));
	EXPECT_CALL(theGraphicsMapper, getGraphicalCulture("testCultureGroup"))
		 .WillOnce(testing::Return("testGraphicalCulture"));
	EXPECT_CALL(theGraphicsMapper, get2dGraphicalCulture("testCultureGroup"))
		 .WillOnce(testing::Return("test2dGraphicalCulture"));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getGraphicalCulture(), "testGraphicalCulture");
	ASSERT_EQ(theCountry.getGraphicalCulture2d(), "test2dGraphicalCulture");
}


TEST_F(HoI4World_HoI4CountryTests, hasProvincesDefaultsToFalse)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_FALSE(theCountry.hasProvinces());
}


TEST_F(HoI4World_HoI4CountryTests, getProvincesDefaultsToEmpty)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_TRUE(theCountry.getProvinces().empty());
}


TEST_F(HoI4World_HoI4CountryTests, provincesCanBeAdded)
{
	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	const mockHoi4State state(foo, "TAG");
	EXPECT_CALL(state, getID).WillOnce(testing::Return(0));
	std::set<int> testProvinces{1, 2, 3};
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRef(testProvinces));

	theCountry.addState(state);

	ASSERT_TRUE(theCountry.hasProvinces());
	ASSERT_TRUE(theCountry.getProvinces().contains(1));
	ASSERT_TRUE(theCountry.getProvinces().contains(2));
	ASSERT_TRUE(theCountry.getProvinces().contains(3));
}


TEST_F(HoI4World_HoI4CountryTests, getStatesDefaultsToEmpty)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_TRUE(theCountry.getStates().empty());
}


TEST_F(HoI4World_HoI4CountryTests, statesCanBeAdded)
{
	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	const mockHoi4State state(foo, "");
	EXPECT_CALL(state, getID).WillOnce(testing::Return(42));
	std::set<int> testProvinces;
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRef(testProvinces));

	theCountry.addState(state);

	ASSERT_TRUE(theCountry.getStates().contains(42));
}


TEST_F(HoI4World_HoI4CountryTests, capitalDefaultsToNone)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getCapitalState(), std::nullopt);
	ASSERT_EQ(theCountry.getCapitalProvince(), std::nullopt);
}

#pragma optimize("", off)
TEST_F(HoI4World_HoI4CountryTests, capitalCanBeSetInOwnedState)
{
	EXPECT_CALL(sourceCountry, getCapital).WillOnce(testing::Return(42));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	mockHoi4State state(foo, "TAG");
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));

	std::map<int, HoI4::State> allStates;
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(84, 1));

	mappers::ProvinceMapper aProvinceMapper{{}, {{42, {84}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 84);
}
#pragma optimize("", on)

TEST_F(HoI4World_HoI4CountryTests, capitalSetInFirstOwnedStateIfFirstChoiceIsImpassible)
{
	EXPECT_CALL(sourceCountry, getCapital).WillOnce(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	std::map<int, HoI4::State> allStates;
	Vic2::State foo;
	mockHoi4State state(foo, "TAG");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{10}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "TAG");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "TAG");
	state3.addCores(std::set<std::string>{"TAG"});
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalSetInFirstOwnedStateIfFirstChoiceNotOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillOnce(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "TAG");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{10}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "TAG");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "NON");
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalCanGoInPreferredWastelandIfOnlyWastelandOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "TAG");
	state.makeImpassable();
	state.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "TAG");
	state2.makeImpassable();
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "TAG");
	state3.makeImpassable();
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 3);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
}


TEST_F(HoI4World_HoI4CountryTests, capitalCanGoInOtherWastelandIfOnlyWastelandOwnedAndPreferredNotOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "TAG");
	state.makeImpassable();
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{10}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "TAG");
	state2.makeImpassable();
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "NON");
	state3.makeImpassable();
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToCoredPreferredIfNoneOwned)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "NON");
	state.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "NON");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "NON");
	state3.addCores(std::set<std::string>{"TAG"});
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 3);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToCoredNonWastelandIfNoneOwnedAndPreferredIsWasteland)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "NON");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{10}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "NON");
	state2.addCores(std::set<std::string>{"TAG"});
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "NON");
	state3.addCores(std::set<std::string>{"TAG"});
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToPreferredWastelandIfNoneOwnedAndAllWasteland)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "NON");
	state.addCores(std::set<std::string>{"TAG"});
	state.makeImpassable();
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "NON");
	state2.addCores(std::set<std::string>{"TAG"});
	state2.makeImpassable();
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "NON");
	state3.addCores(std::set<std::string>{"TAG"});
	state3.addProvince(30);
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 3);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
}


TEST_F(HoI4World_HoI4CountryTests, capitalGoesToAnyWastelandIfNoneOwnedAllWastelandAndPreferredNotCored)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state(foo, "NON");
	state.addCores(std::set<std::string>{"TAG"});
	state.addProvince(10);
	state.makeImpassable();
	EXPECT_CALL(state, getID).WillOnce(testing::Return(1));
	EXPECT_CALL(state, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{10}));
	std::pair<int, HoI4::State> statePair(1, state);
	allStates.insert(statePair);
	theCountry.addState(state);

	mockHoi4State state2(foo, "NON");
	state2.addCores(std::set<std::string>{"TAG"});
	state2.makeImpassable();
	EXPECT_CALL(state2, getID).WillOnce(testing::Return(2));
	EXPECT_CALL(state2, getProvinces).WillOnce(testing::ReturnRefOfCopy(std::set<int>{}));
	std::pair<int, HoI4::State> statePair2(2, state2);
	allStates.insert(statePair2);
	theCountry.addState(state2);

	mockHoi4State state3(foo, "NON");
	state3.makeImpassable();
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(10, 1));
	provinceToStateIDMap.insert(std::make_pair(20, 2));
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_TRUE(theCountry.getCapitalState());
	ASSERT_EQ(*theCountry.getCapitalState(), 1);
	ASSERT_TRUE(theCountry.getCapitalProvince());
	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
}


TEST_F(HoI4World_HoI4CountryTests, capitalRemainsUnassignedIfNoCoresAndNoOwnedProvince)
{
	EXPECT_CALL(sourceCountry, getCapital).WillRepeatedly(testing::Return(3));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	Vic2::State foo;
	std::map<int, HoI4::State> allStates;
	mockHoi4State state3(foo, "NON");
	std::pair<int, HoI4::State> statePair3(3, state3);
	allStates.insert(statePair3);

	std::map<int, int> provinceToStateIDMap;
	provinceToStateIDMap.insert(std::make_pair(30, 3));

	mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};

	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);

	ASSERT_EQ(theCountry.getCapitalState(), std::nullopt);
	ASSERT_EQ(theCountry.getCapitalProvince(), std::nullopt);
}


TEST_F(HoI4World_HoI4CountryTests, governmentIdeologiesDefaultsToNeutrality)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);
	ASSERT_EQ(theCountry.getGovernmentIdeology(), "neutrality");
	ASSERT_EQ(theCountry.getLeaderIdeology(), "conservatism_neutral");
}


TEST_F(HoI4World_HoI4CountryTests, governmentIdeologiesCanBeSet)
{
	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testGovernmentIdeology"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testLeaderIdeology"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);
	ASSERT_EQ(theCountry.getGovernmentIdeology(), "testGovernmentIdeology");
	ASSERT_EQ(theCountry.getLeaderIdeology(), "testLeaderIdeology");
}


TEST_F(HoI4World_HoI4CountryTests, rulingPartyComesFromVic2Country)
{
	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testGovernmentIdeology"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testLeaderIdeology"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);
	ASSERT_EQ(theCountry.getRulingParty(), testParty);
}


TEST_F(HoI4World_HoI4CountryTests, missingRulingPartyThrowsException)
{
	const std::vector<Vic2::Party> testParties{};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties)).WillOnce(testing::Return(std::nullopt));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	const mockGovernmentMapper mockGovernmentMap;

	EXPECT_THROW(
		 theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations),
		 std::runtime_error);
}


TEST_F(HoI4World_HoI4CountryTests, partiesDefaultsToEmpty)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

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

	std::vector<Vic2::Party> testParties{testParty, testParty2};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	std::set<Vic2::Party> activeParties;
	activeParties.insert(testParty);
	activeParties.insert(testParty2);
	EXPECT_CALL(sourceCountry, getActiveParties(testParties)).WillOnce(testing::Return(activeParties));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testGovernmentIdeology"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testLeaderIdeology"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);
	ASSERT_EQ(theCountry.getParties().count(testParty), 1);
	ASSERT_EQ(theCountry.getParties().count(testParty2), 1);
}


TEST_F(HoI4World_HoI4CountryTests, defaultIdeologicalSupportIsAllNeutrality)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const std::map<std::string, int> expectedSupport{std::make_pair("neutrality", 100)};

	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
}


TEST_F(HoI4World_HoI4CountryTests, ideologicalSupportWithNoIdeologiesIsAllNeutrality)
{
	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);


	const mockGovernmentMapper mockGovernmentMap;
	theCountry.convertIdeologySupport({}, mockGovernmentMap);

	const std::map<std::string, int> expectedSupport{std::make_pair("neutrality", 100)};
	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
}


TEST_F(HoI4World_HoI4CountryTests, ideologicalSupportCanBeConverted)
{
	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const std::map<std::string, double> upperHouseComposition{{"conservative", 0.30}, {"liberal", 0.70}};
	EXPECT_CALL(sourceCountry, getUpperHouseComposition()).WillOnce(testing::Return(upperHouseComposition));

	std::set<std::string> majorIdeologies{"conservative"};

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getSupportedIdeology("neutrality", "conservative", majorIdeologies))
		 .WillOnce(testing::Return("conservative"));
	EXPECT_CALL(mockGovernmentMap, getSupportedIdeology("neutrality", "liberal", majorIdeologies))
		 .WillOnce(testing::Return("neutrality"));

	theCountry.convertIdeologySupport(majorIdeologies, mockGovernmentMap);

	const std::map<std::string, int> expectedSupport{std::make_pair("neutrality", 70),
		 std::make_pair("conservative", 30)};
	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
}


TEST_F(HoI4World_HoI4CountryTests, ideologicalSupportCombinesSameIdeologies)
{
	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const std::map<std::string, double> upperHouseComposition{{"conservative", 0.30}, {"liberal", 0.70}};
	EXPECT_CALL(sourceCountry, getUpperHouseComposition()).WillOnce(testing::Return(upperHouseComposition));

	std::set<std::string> majorIdeologies{"conservative"};

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getSupportedIdeology("neutrality", "conservative", majorIdeologies))
		 .WillOnce(testing::Return("conservative"));
	EXPECT_CALL(mockGovernmentMap, getSupportedIdeology("neutrality", "liberal", majorIdeologies))
		 .WillOnce(testing::Return("conservative"));

	theCountry.convertIdeologySupport(majorIdeologies, mockGovernmentMap);

	const std::map<std::string, int> expectedSupport{std::make_pair("conservative", 100)};
	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
}


TEST_F(HoI4World_HoI4CountryTests, lastElectionIsFromSourceCountry)
{
	EXPECT_CALL(sourceCountry, getLastElection()).WillOnce(testing::Return(date{"1234.5.6"}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getLastElection(), date{"1234.5.6"});
}


TEST_F(HoI4World_HoI4CountryTests, stabilityDefaultsToSixty)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getStability(), 60);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportDefaultsToSixty)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 60);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportIncreasedByJingosim)
{
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("jingoism")).WillOnce(testing::Return(8.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pro_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("anti_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pacifism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 63);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportIncreasedByProMilitary)
{
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("jingoism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pro_military")).WillOnce(testing::Return(16.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("anti_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pacifism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 63);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportDecreasedByAntiMilitary)
{
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("jingoism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pro_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("anti_military")).WillOnce(testing::Return(16.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pacifism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 57);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportDecreasedByPacifism)
{
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("jingoism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pro_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("anti_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pacifism")).WillOnce(testing::Return(8.0f));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 57);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportIncreasedByRevanchism)
{
	EXPECT_CALL(sourceCountry, getRevanchism()).WillOnce(testing::Return(100));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 80);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportDecreasedByWarExhaustion)
{
	EXPECT_CALL(sourceCountry, getWarExhaustion()).WillOnce(testing::Return(50));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 40);
}


TEST_F(HoI4World_HoI4CountryTests, warSupportHasMinimumOfFifteen)
{
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("jingoism")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pro_military")).WillOnce(testing::Return(0.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("anti_military")).WillOnce(testing::Return(80.0f));
	EXPECT_CALL(sourceCountry, getAverageIssueSupport("pacifism")).WillOnce(testing::Return(80.0f));
	EXPECT_CALL(sourceCountry, getWarExhaustion()).WillOnce(testing::Return(50));
	EXPECT_CALL(sourceCountry, getProvinces()).WillOnce(testing::Return(std::map<int, Vic2::Province*>{{1, nullptr}}));

	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getWarSupport(), 15);
}


TEST_F(HoI4World_HoI4CountryTests, mobilizationLawDefaultsToVolunteerOnly)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getMobilizationLaw(), "volunteer_only");
}


TEST_F(HoI4World_HoI4CountryTests, mobilizationLawIncreasesIfRulingPartyJingoistic)
{
	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology\n";
	partyInput << "war_policy = jingoism";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testGovernmentIdeology"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testLeaderIdeology"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);

	ASSERT_EQ(theCountry.getMobilizationLaw(), "limited_conscription");
}


TEST_F(HoI4World_HoI4CountryTests, mobilizationLawDecreasesIfRulingPartyPacifistic)
{
	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology\n";
	partyInput << "war_policy = pacifism";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testGovernmentIdeology"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testLeaderIdeology"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);

	ASSERT_EQ(theCountry.getMobilizationLaw(), "disarmed_nation");
}


TEST_F(HoI4World_HoI4CountryTests, economicLawDefaultsToCivilian)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getEconomicLaw(), "civilian_economy");
}


TEST_F(HoI4World_HoI4CountryTests, economicLawIncreasesIfAtWar)
{
	EXPECT_CALL(sourceCountry, isAtWar()).WillOnce(testing::Return(true));

	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = testSourceIdeology\n";
	partyInput << "war_policy = jingoism";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testGovernmentIdeology"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "testSourceIdeology"))
		 .WillOnce(testing::Return("testLeaderIdeology"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);

	ASSERT_EQ(theCountry.getEconomicLaw(), "low_economic_mobilisation");
}


TEST_F(HoI4World_HoI4CountryTests, economicLawIncreasesIfFascist)
{
	EXPECT_CALL(sourceCountry, isAtWar()).WillOnce(testing::Return(true));

	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = fascism\n";
	partyInput << "war_policy = jingoism";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "fascism"))
		 .WillOnce(testing::Return("fascism"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "fascism"))
		 .WillOnce(testing::Return("fascism"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);

	ASSERT_EQ(theCountry.getEconomicLaw(), "partial_economic_mobilisation");
}


TEST_F(HoI4World_HoI4CountryTests, tradeLawDefaultsToExport)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getTradeLaw(), "export_focus");
}


TEST_F(HoI4World_HoI4CountryTests, tradeLawChangesIfFascist)
{
	EXPECT_CALL(sourceCountry, isAtWar()).WillOnce(testing::Return(true));

	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = fascism\n";
	partyInput << "war_policy = jingoism";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "fascism"))
		 .WillOnce(testing::Return("fascism"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "fascism"))
		 .WillOnce(testing::Return("fascism"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);

	ASSERT_EQ(theCountry.getTradeLaw(), "limited_exports");
}


TEST_F(HoI4World_HoI4CountryTests, tradeLawChangesIfRadical)
{
	EXPECT_CALL(sourceCountry, isAtWar()).WillOnce(testing::Return(true));

	std::stringstream partyInput;
	partyInput << "name = testParty\n";
	partyInput << "ideology = radical\n";
	partyInput << "war_policy = jingoism";
	Vic2::Party testParty(partyInput);

	const std::vector<Vic2::Party> testParties{testParty};
	EXPECT_CALL(sourceCountry, getRulingParty(testParties))
		 .WillOnce(testing::Return(std::make_optional<Vic2::Party>(testParty)));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	const mockVic2World mockSourceWorld;
	EXPECT_CALL(mockSourceWorld, getParties()).WillRepeatedly(testing::Return(testParties));

	mockGovernmentMapper mockGovernmentMap;
	EXPECT_CALL(mockGovernmentMap, getIdeologyForCountry("TAG", "testGovernment", "radical"))
		 .WillOnce(testing::Return("radical"));
	EXPECT_CALL(mockGovernmentMap, getLeaderIdeologyForCountry("TAG", "testGovernment", "radical"))
		 .WillOnce(testing::Return("radical"));

	theCountry.convertGovernment(mockSourceWorld, mockGovernmentMap, *vic2Localisations, *hoi4Localisations);

	ASSERT_EQ(theCountry.getTradeLaw(), "free_trade");
}


TEST_F(HoI4World_HoI4CountryTests, technologyCountDefaultsToZero)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_EQ(theCountry.getTechnologyCount(), 0);
}


TEST_F(HoI4World_HoI4CountryTests, technologiesDefaultToNullopt)
{
	const HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	ASSERT_FALSE(theCountry.getTechnologies());
}


TEST_F(HoI4World_HoI4CountryTests, technologyCanBeConverted)
{
	EXPECT_CALL(sourceCountry, getTechs()).WillOnce(testing::Return(std::set<std::string>{"testTech"}));
	EXPECT_CALL(sourceCountry, getInventions()).WillOnce(testing::Return(std::set<std::string>{"testInvention"}));

	HoI4::Country theCountry("TAG",
		 &sourceCountry,
		 theNamesMapper,
		 theGraphicsMapper,
		 theCountryMapper,
		 *theFlagsToIdeasMapper,
		 *hoi4Localisations);

	std::map<std::string, std::set<std::string>> techMap;
	std::set<std::string> convertedTech{"convertedTech"};
	techMap.insert(std::make_pair("testTech", convertedTech));
	const mappers::techMapper theTechMapper(techMap,
		 std::map<std::string, std::set<std::string>>{},
		 std::map<std::string, std::set<std::string>>{},
		 std::map<std::string, std::map<std::string, int>>{});
	theCountry.convertTechnology(theTechMapper);

	ASSERT_EQ(theCountry.getTechnologyCount(), 1);
	ASSERT_TRUE(theCountry.getTechnologies()->hasTechnology("convertedTech"));
}