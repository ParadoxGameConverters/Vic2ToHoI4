//#include "Color.h"
//#include "HOI4World/HoI4Country.h"
//#include "HOI4World/HoI4Localisation.h"
//#include "HOI4World/Names/Names.h"
//#include "HOI4World/States/HoI4StateBuilder.h"
//#include "Mappers/CountryMapperBuilder.h"
//#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
//#include "Mappers/GovernmentMapperBuilder.h"
//#include "Mappers/GraphicsMappedBuilder.h"
//#include "V2World/CountryBuilder.h"
//#include "V2World/Localisations/Vic2Localisations.h"
//#include "V2World/Politics/PartyBuilder.h"
//#include "V2World/Pops/PopBuilder.h"
//#include "V2World/Provinces/ProvinceBuilder.h"
//#include "V2World/States/State.h"
//#include "V2World/World.h"
//#include "gtest/gtest.h"
//#include <sstream>
//
//
//
// class HoI4World_HoI4CountryTests: public testing::Test
//{
//  protected:
//	HoI4World_HoI4CountryTests();
//
//	std::unique_ptr<mappers::FlagsToIdeasMapper> theFlagsToIdeasMapper;
//
//	commonItems::Color defaultColor;
//
//	std::unique_ptr<Vic2::Localisations> vic2Localisations;
//	std::unique_ptr<HoI4::Localisation> hoi4Localisations;
//	std::unique_ptr<HoI4::Names> names;
//	Vic2::World sourceWorld;
//};
//
//
// HoI4World_HoI4CountryTests::HoI4World_HoI4CountryTests()
//{
//	std::stringstream input;
//	theFlagsToIdeasMapper = std::make_unique<mappers::FlagsToIdeasMapper>(input);
//
//	Vic2::KeyToLocalisationsMap localisations;
//	std::map<std::string, std::string> localisationToKeyMap;
//	vic2Localisations = std::make_unique<Vic2::Localisations>(localisations, localisationToKeyMap);
//
//	const auto theConfiguration = Configuration::Builder{}.build();
//	hoi4Localisations = HoI4::Localisation::Importer{}.generateLocalisations(*theConfiguration);
//	names = std::make_unique<HoI4::Names>(
//		std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{},
//		 std::map<std::string, std::vector<std::string>>{});
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, tagCanBeAssigned)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//	ASSERT_EQ(theCountry.getTag(), "TAG");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, filenamesDefaultToTag)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//	ASSERT_EQ(theCountry.getFilename(), "TAG.txt");
//	ASSERT_EQ(theCountry.getCommonCountryFile(), "TAG.txt");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, filenamesBasedOnSourceCountryName)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.addNameInLanguage("english", "source country name").Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//	ASSERT_EQ(theCountry.getFilename(), "TAG - source country name.txt");
//	ASSERT_EQ(theCountry.getCommonCountryFile(), "source country name.txt");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, filenamesReplaceBadCharacters)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.addNameInLanguage("english", "hardname|><").Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//	ASSERT_EQ(theCountry.getFilename(), "TAG - hardname.txt");
//	ASSERT_EQ(theCountry.getCommonCountryFile(), "hardname.txt");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, filenamesConvertFrom1252ToUtf8)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.addNameInLanguage("english", "1252\xC7").Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getFilename(), "TAG - 1252\xC3\x87.txt");
//	ASSERT_EQ(theCountry.getCommonCountryFile(), "1252\xC3\x87.txt");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, isHumanDefaultsToFalse)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.isHuman(), false);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, isHumanCanBetSetTrue)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setHuman().Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.isHuman(), true);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, colorIsFromSourceCountry)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setColor(commonItems::Color{std::array<int, 3>{33, 66, 99}}).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	const auto expectedColor = commonItems::Color{std::array<int, 3>{33, 66, 99}};
//	ASSERT_EQ(theCountry.getColor(), expectedColor);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, graphicalCultureDefaultsToWesternEuropean)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getGraphicalCulture(), "western_european_gfx");
//	ASSERT_EQ(theCountry.getGraphicalCulture2d(), "western_european_2d");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, graphicalCultureIsFromSourceCountryCultureGroup)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}
//				.addGraphicalCultureMapping("testCultureGroup", "testGraphicalCulture")
//				.add2dGraphicalCultureMapping("testCultureGroup", "test2dGraphicalCulture")
//				.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getGraphicalCulture(), "testGraphicalCulture");
//	ASSERT_EQ(theCountry.getGraphicalCulture2d(), "test2dGraphicalCulture");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, hasProvincesDefaultsToFalse)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_FALSE(theCountry.hasProvinces());
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, getProvincesDefaultsToEmpty)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_TRUE(theCountry.getProvinces().empty());
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, provincesCanBeAdded)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.addState(*HoI4::State::Builder{}.setProvinces({1, 2, 3}).Build());
//
//	ASSERT_TRUE(theCountry.hasProvinces());
//	ASSERT_TRUE(theCountry.getProvinces().contains(1));
//	ASSERT_TRUE(theCountry.getProvinces().contains(2));
//	ASSERT_TRUE(theCountry.getProvinces().contains(3));
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, getStatesDefaultsToEmpty)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_TRUE(theCountry.getStates().empty());
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, statesCanBeAdded)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.addState(*HoI4::State::Builder{}.setId(42).Build());
//
//	ASSERT_TRUE(theCountry.getStates().contains(42));
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalDefaultsToNone)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getCapitalState(), std::nullopt);
//	ASSERT_EQ(theCountry.getCapitalProvince(), std::nullopt);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalCanBeSetInOwnedState)
//{
//	const auto sourceCountry = Vic2::Country::Builder{}.setCapital(42).Build();
//	HoI4::Country theCountry("TAG",
//		 &*sourceCountry,
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("TAG").Build();
//
//	std::map<int, HoI4::State> allStates;
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(84, 1));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{42, {84}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 1);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 84);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalSetInFirstOwnedStateIfFirstChoiceIsImpassible)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("TAG").addCore("TAG").setProvinces({10}).Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("TAG").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("TAG").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 1);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalSetInFirstOwnedStateIfFirstChoiceNotOwned)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("TAG").addCore("TAG").setProvinces({10}).Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("TAG").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("NON").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 1);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalCanGoInPreferredWastelandIfOnlyWastelandOwned)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("TAG").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("TAG").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("TAG").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 3);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalCanGoInOtherWastelandIfOnlyWastelandOwnedAndPreferredNotOwned)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//	const auto state =
//		 *HoI4::State::Builder{}.setId(1).setOwner("TAG").addCore("TAG").setProvinces({10}).makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("TAG").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("NON").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 1);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalGoesToCoredPreferredIfNoneOwned)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("NON").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("NON").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("NON").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 3);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalGoesToCoredNonWastelandIfNoneOwnedAndPreferredIsWasteland)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("NON").addCore("TAG").setProvinces({10}).Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("NON").addCore("TAG").Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("NON").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 1);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalGoesToPreferredWastelandIfNoneOwnedAndAllWasteland)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("NON").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("NON").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 =
//		 *HoI4::State::Builder{}.setOwner("NON").addCore("TAG").setProvinces({30}).makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 3);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 30);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalGoesToAnyWastelandIfNoneOwnedAllWastelandAndPreferredNotCored)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//
//	const auto state = *HoI4::State::Builder{}.setId(1).setOwner("NON").addCore("TAG").setProvinces({10}).Build();
//	std::pair<int, HoI4::State> statePair(1, state);
//	allStates.insert(statePair);
//	theCountry.addState(state);
//
//	const auto state2 = *HoI4::State::Builder{}.setId(2).setOwner("NON").addCore("TAG").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair2(2, state2);
//	allStates.insert(statePair2);
//	theCountry.addState(state2);
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("NON").makeImpassable().Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(10, 1));
//	provinceToStateIDMap.insert(std::make_pair(20, 2));
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_TRUE(theCountry.getCapitalState());
//	ASSERT_EQ(*theCountry.getCapitalState(), 1);
//	ASSERT_TRUE(theCountry.getCapitalProvince());
//	ASSERT_EQ(*theCountry.getCapitalProvince(), 10);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, capitalRemainsUnassignedIfNoCoresAndNoOwnedProvince)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setCapital(3).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<int, HoI4::State> allStates;
//
//	const auto state3 = *HoI4::State::Builder{}.setOwner("NON").Build();
//	std::pair<int, HoI4::State> statePair3(3, state3);
//	allStates.insert(statePair3);
//
//	std::map<int, int> provinceToStateIDMap;
//	provinceToStateIDMap.insert(std::make_pair(30, 3));
//
//	Mappers::ProvinceMapper aProvinceMapper{{}, {{3, {30}}}};
//
//	theCountry.determineCapitalFromVic2(aProvinceMapper, provinceToStateIDMap, allStates);
//
//	ASSERT_EQ(theCountry.getCapitalState(), std::nullopt);
//	ASSERT_EQ(theCountry.getCapitalProvince(), std::nullopt);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, governmentIdeologiesDefaultsToNeutrality)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//	ASSERT_EQ(theCountry.getGovernmentIdeology(), "neutrality");
//	ASSERT_EQ(theCountry.getLeaderIdeology(), "conservatism_neutral");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, governmentIdeologiesCanBeSet)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setRulingParty(*Vic2::Party::Builder{}.setIdeology("testSourceIdeology").Build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testSourceIdeology",
//					 .HoI4GovernmentIdeology = "testGovernmentIdeology",
//					 .HoI4LeaderIdeology = "testLeaderIdeology",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//	ASSERT_EQ(theCountry.getGovernmentIdeology(), "testGovernmentIdeology");
//	ASSERT_EQ(theCountry.getLeaderIdeology(), "testLeaderIdeology");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, rulingPartyComesFromVic2Country)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setRulingParty(*Vic2::Party::Builder{}.setName("testParty").Build()).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testSourceIdeology",
//					 .HoI4GovernmentIdeology = "testGovernmentIdeology",
//					 .HoI4LeaderIdeology = "testLeaderIdeology",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//	ASSERT_EQ(theCountry.getRulingParty(), *Vic2::Party::Builder{}.setName("testParty").Build());
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, missingRulingPartyThrowsException)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	EXPECT_THROW(theCountry.convertGovernment(sourceWorld,
//						  *governmentMapper::Builder{}.Build(),
//						  *vic2Localisations,
//						  *hoi4Localisations,
//						  false),
//		 std::runtime_error);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, partiesDefaultsToEmpty)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	EXPECT_TRUE(theCountry.getParties().empty());
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, partiesComeFromVic2Country)
//{
//	const auto testParty = Vic2::Party::Builder{}.setName("TAG_testParty").Build();
//	const auto testParty2 = Vic2::Party::Builder{}.setName("TAG_testParty2").Build();
//
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .addActiveParty(*testParty)
//				 .addActiveParty(*testParty2)
//				 .setRulingParty(*testParty)
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "testGovernmentIdeology",
//					 .HoI4LeaderIdeology = "testLeaderIdeology",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//	ASSERT_TRUE(theCountry.getParties().contains(*testParty));
//	ASSERT_TRUE(theCountry.getParties().contains(*testParty2));
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, defaultIdeologicalSupportIsAllNeutrality)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	const std::map<std::string, int> expectedSupport{std::make_pair("neutrality", 100)};
//
//	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, ideologicalSupportWithNoIdeologiesIsAllNeutrality)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//
//	theCountry.convertIdeologySupport({}, *governmentMapper::Builder{}.Build());
//
//	const std::map<std::string, int> expectedSupport{std::make_pair("neutrality", 100)};
//	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, ideologicalSupportCanBeConverted)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setUpperHouseComposition({{"conservative", 0.30}, {"liberal", 0.70}}).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::set<std::string> majorIdeologies{"conservative"};
//
//	theCountry.convertIdeologySupport(majorIdeologies,
//		 *governmentMapper::Builder{}
//				.addPartyMapping(partyMapping{"neutrality", "conservative", "conservative"})
//				.addPartyMapping(partyMapping{"neutrality", "liberal", "neutrality"})
//				.Build());
//
//	const std::map<std::string, int> expectedSupport{std::make_pair("neutrality", 70),
//		 std::make_pair("conservative", 30)};
//	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, ideologicalSupportCombinesSameIdeologies)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setUpperHouseComposition({{"conservative", 0.30}, {"liberal", 0.70}}).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::set<std::string> majorIdeologies{"conservative"};
//
//	theCountry.convertIdeologySupport(majorIdeologies,
//		 *governmentMapper::Builder{}
//				.addPartyMapping(partyMapping{"neutrality", "conservative", "conservative"})
//				.addPartyMapping(partyMapping{"neutrality", "liberal", "conservative"})
//				.Build());
//
//	const std::map<std::string, int> expectedSupport{std::make_pair("conservative", 100)};
//	ASSERT_EQ(theCountry.getIdeologySupport(), expectedSupport);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, lastElectionIsFromSourceCountry)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setLastElection(date{"1234.5.6"}).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getLastElection(), date{"1234.5.6"});
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, stabilityDefaultsToSixty)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getStability(), 60);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportDefaultsToSixty)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 60);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportIncreasedByJingosim)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .addProvince(1,
//					  Vic2::Province::Builder{}
//							.setPops({*Vic2::Pop::Builder{}.setSize(1).setIssues({{"jingoism", 8.0f}}).build()})
//							.build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 63);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportIncreasedByProMilitary)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .addProvince(1,
//					  Vic2::Province::Builder{}
//							.setPops({*Vic2::Pop::Builder{}.setSize(1).setIssues({{"pro_military", 16.0f}}).build()})
//							.build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 63);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportDecreasedByAntiMilitary)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .addProvince(1,
//					  Vic2::Province::Builder{}
//							.setPops({*Vic2::Pop::Builder{}.setSize(1).setIssues({{"anti_military", 16.0f}}).build()})
//							.build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 57);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportDecreasedByPacifism)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .addProvince(1,
//					  Vic2::Province::Builder{}
//							.setPops({*Vic2::Pop::Builder{}.setSize(1).setIssues({{"pacifism", 8.0f}}).build()})
//							.build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 57);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportIncreasedByRevanchism)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setRevanchism(100).addProvince(1, nullptr).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 80);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportDecreasedByWarExhaustion)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.setWarExhaustion(50).addProvince(1, nullptr).Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 40);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, warSupportHasMinimumOfFifteen)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setWarExhaustion(50)
//				 .addProvince(1,
//					  Vic2::Province::Builder{}
//							.setPops({*Vic2::Pop::Builder{}
//												.setSize(1)
//												.setIssues({{"anti_military", 80.0f}, {"pacifism", 80.0f}})
//												.build()})
//							.build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getWarSupport(), 15);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, mobilizationLawDefaultsToVolunteerOnly)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getMobilizationLaw(), "volunteer_only");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, mobilizationLawIncreasesIfRulingPartyJingoistic)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .setRulingParty(*Vic2::Party::Builder{}.setWarPolicy("jingoism").Build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "testGovernmentIdeology",
//					 .HoI4LeaderIdeology = "testLeaderIdeology",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//
//	ASSERT_EQ(theCountry.getMobilizationLaw(), "limited_conscription");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, mobilizationLawDecreasesIfRulingPartyPacifistic)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .setRulingParty(*Vic2::Party::Builder{}.setWarPolicy("pacifism").Build())
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "testGovernmentIdeology",
//					 .HoI4LeaderIdeology = "testLeaderIdeology",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//
//	ASSERT_EQ(theCountry.getMobilizationLaw(), "disarmed_nation");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, economicLawDefaultsToCivilian)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getEconomicLaw(), "civilian_economy");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, economicLawIncreasesIfAtWar)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .setRulingParty(*Vic2::Party::Builder{}.setWarPolicy("jingoism").Build())
//				 .setAtWar(true)
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "testGovernmentIdeology",
//					 .HoI4LeaderIdeology = "testLeaderIdeology",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//
//	ASSERT_EQ(theCountry.getEconomicLaw(), "low_economic_mobilisation");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, economicLawIncreasesIfFascist)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .setRulingParty(*Vic2::Party::Builder{}.setIdeology("fascism").Build())
//				 .setAtWar(true)
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "fascism",
//					 .HoI4LeaderIdeology = "fascism",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//
//	ASSERT_EQ(theCountry.getEconomicLaw(), "partial_economic_mobilisation");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, tradeLawDefaultsToExport)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getTradeLaw(), "export_focus");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, tradeLawChangesIfFascist)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .setRulingParty(*Vic2::Party::Builder{}.setIdeology("fascism").Build())
//				 .setAtWar(true)
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "fascism",
//					 .HoI4LeaderIdeology = "fascism",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//
//	ASSERT_EQ(theCountry.getTradeLaw(), "limited_exports");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, tradeLawChangesIfRadical)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}
//				 .setGovernment("testGovernment")
//				 .setRulingParty(*Vic2::Party::Builder{}.setIdeology("radical").Build())
//				 .setAtWar(true)
//				 .Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	theCountry.convertGovernment(sourceWorld,
//		 *governmentMapper::Builder{}
//				.addGovernmentMapping(governmentMapping{.vic2Government = "testGovernment",
//					 .HoI4GovernmentIdeology = "radical",
//					 .HoI4LeaderIdeology = "radical",
//					 .rulingPartyRequired = false})
//				.Build(),
//		 *vic2Localisations,
//		 *hoi4Localisations,
//		 false);
//
//	ASSERT_EQ(theCountry.getTradeLaw(), "free_trade");
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, technologyCountDefaultsToZero)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_EQ(theCountry.getTechnologyCount(), 0);
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, technologiesDefaultToNullopt)
//{
//	const HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	ASSERT_FALSE(theCountry.getTechnologies());
//}
//
//
// TEST_F(HoI4World_HoI4CountryTests, technologyCanBeConverted)
//{
//	HoI4::Country theCountry("TAG",
//		 &*Vic2::Country::Builder{}.addTech("testTech").addDiscoveredInvention("testInvention").Build(),
//		 *names,
//		 *graphicsMapper::Builder{}.Build(),
//		 *CountryMapper::Builder{}.Build(),
//		 *theFlagsToIdeasMapper,
//		 *hoi4Localisations);
//
//	std::map<std::string, std::set<std::string>> techMap;
//	std::set<std::string> convertedTech{"convertedTech"};
//	techMap.insert(std::make_pair("testTech", convertedTech));
//	const mappers::techMapper theTechMapper(techMap,
//		 std::map<std::string, std::set<std::string>>{},
//		 std::map<std::string, std::set<std::string>>{},
//		 std::map<std::string, std::map<std::string, int>>{});
//	theCountry.convertTechnology(theTechMapper);
//
//	ASSERT_EQ(theCountry.getTechnologyCount(), 1);
//	ASSERT_TRUE(theCountry.getTechnologies()->hasTechnology("convertedTech"));
//}