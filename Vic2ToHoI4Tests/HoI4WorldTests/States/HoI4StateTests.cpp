#include "../../Mocks/CoastalProvincesMock.h"
#include "../../Mocks/CountryMapperMock.h"
#include "../../Mocks/ProvinceMapperMock.h"
#include "../../Mocks/StateCategoriesMock.h"
#include "../../Mocks/Vic2StateMock.h"
#include "../Vic2ToHoI4/Source/Configuration.h"
#include "../Vic2ToHoI4/Source/HOI4World/Map/CoastalProvinces.h"
#include "../Vic2ToHoI4/Source/HOI4World/States/HoI4State.h"
#include "../Vic2ToHoI4/Source/Hoi4Outputter/States/HoI4StateOutputter.h"
#include "../Vic2ToHoI4/Source/V2World/Province.h"
#include "gtest/gtest.h"
#include <optional>
#include <sstream>



TEST(HoI4World_States_StateTests, IdDefaultsToZero)
{
	const HoI4::State theState;

	ASSERT_EQ(0, theState.getID());
}


TEST(HoI4World_States_StateTests, IdIsReturned)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getID(), 42);
}


TEST(HoI4World_States_StateTests, ProvincesDefaultToEmpty)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getProvinces().empty());
}


TEST(HoI4World_States_StateTests, ProvincesCanbeAdded)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(5);
	theState.addProvince(13);

	ASSERT_EQ(2, theState.getProvinces().size());
	ASSERT_EQ(1, theState.getProvinces().count(5));
	ASSERT_EQ(1, theState.getProvinces().count(13));
}


TEST(HoI4World_States_StateTests, OwnerDefaultsToEmpty)
{
	const HoI4::State theState;

	ASSERT_TRUE(theState.getOwner().empty());
}


TEST(HoI4World_States_StateTests, OwnerIsReturned)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getOwner(), "TAG");
}


TEST(HoI4World_States_StateTests, CoresDefaultToEmpty)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getCores().empty());
}


TEST(HoI4World_States_StateTests, CoresCanbeAdded)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	std::set<std::string> cores;
	cores.insert("TAG");
	cores.insert("COR");
	theState.addCores(cores);

	ASSERT_EQ(2, theState.getCores().size());
	ASSERT_EQ(1, theState.getCores().count("TAG"));
	ASSERT_EQ(1, theState.getCores().count("COR"));
}


TEST(HoI4World_States_StateTests, ControlledProvincesDefaultToEmpty)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, ControllersCanBeAdded)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=NOT\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::optional<std::vector<int>> possibleMappedProvinces;
	std::vector<int> mappedProvinces;
	mappedProvinces.push_back(12);
	possibleMappedProvinces = mappedProvinces;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(possibleMappedProvinces));

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "NOT";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("NOT")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(provinces, theProvinceMapper, theCountryMapper);

	std::map<std::string, std::set<int>> expectedControlledProvinces{{"NOT", {12}}};
	ASSERT_EQ(expectedControlledProvinces, theState.getControlledProvinces());
}


TEST(HoI4World_States_StateTests, ControllersConvertWithHoI4Tag)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=NOT\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::optional<std::vector<int>> possibleMappedProvinces;
	std::vector<int> mappedProvinces;
	mappedProvinces.push_back(12);
	possibleMappedProvinces = mappedProvinces;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(possibleMappedProvinces));

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "HOI";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("NOT")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(provinces, theProvinceMapper, theCountryMapper);

	std::map<std::string, std::set<int>> expectedControlledProvinces{{"HOI", {12}}};
	ASSERT_EQ(expectedControlledProvinces, theState.getControlledProvinces());
}


TEST(HoI4World_States_StateTests, ControllersDontConvertForRebels)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "REB";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("REB")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(provinces, theProvinceMapper, theCountryMapper);

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, ImpassableDefaultsToFalse)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.isImpassable());
}


TEST(HoI4World_States_StateTests, ImpassableCanBeSet)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.makeImpassable();

	ASSERT_TRUE(theState.isImpassable());
}


TEST(HoI4World_States_StateTests, DockyardsDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getDockyards());
}


TEST(HoI4World_States_StateTests, CivFactoriesDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getCivFactories());
}


TEST(HoI4World_States_StateTests, MilFactoriesDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getMilFactories(), 0);
}


TEST(HoI4World_States_StateTests, TotalFactoriesCanBeSet)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(50000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(7)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(5, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, TotalFactoriesCappedAtTwelve)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(500000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(14)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(12, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, categoryCanBeChanged)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(500000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(0.0f));
	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(14)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ("mockedCategory", theState.getCategory());
}


TEST(HoI4World_States_StateTests, InfrastructureDefaultsToThree)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(3, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureAddedPerTwoRailLevels)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(2)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(6, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForOverFourFactories)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(50000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(7)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(7, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForOverSixFactories)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(70000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(9)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(8, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForOverTenFactories)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(110000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(13)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(9, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, NavalBasesConvertsToEmpty)
{
	const HoI4::State theState;

	ASSERT_TRUE(theState.getNavalBases().empty());
}


TEST(HoI4World_States_StateTests, NavalBasesCanBeConverted)
{
	HoI4::State theState;
	theState.addProvince(1);
	theState.addProvince(2);

	std::stringstream input;
	input << "= {\n";
	input << "\tnaval_base = 1.0";
	input << "}";
	Vic2::Province sourceProvince("1", input);
	std::stringstream input2;
	input2 << "= {\n";
	input2 << "\tnaval_base = 1.0";
	input2 << "}";
	Vic2::Province sourceProvince2("2", input2);
	const std::set<const Vic2::Province*> sourceProvinces{&sourceProvince, &sourceProvince2};

	const mockCoastalProvinces theCoastalProvinces;
	EXPECT_CALL(theCoastalProvinces, isProvinceCoastal(1)).WillOnce(testing::Return(true));
	EXPECT_CALL(theCoastalProvinces, isProvinceCoastal(2)).WillOnce(testing::Return(true));

	mockProvinceMapper theProvinceMapper;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(1)).WillOnce(testing::Return(std::vector<int>{1}));
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(2)).WillOnce(testing::Return(std::vector<int>{2}));

	theState.convertNavalBases(sourceProvinces, theCoastalProvinces, theProvinceMapper);

	const std::map<int, int> expectedNavalBases{{1, 2}, {2, 2}};
	ASSERT_EQ(expectedNavalBases, theState.getNavalBases());
}


TEST(HoI4World_States_StateTests, AirbaseLevelDefaultsToZero)
{
	const HoI4::State theState;

	ASSERT_EQ(0, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, AirbaseLevelCanBeSet)
{
	HoI4::State theState;
	theState.addAirBase(2);

	ASSERT_EQ(2, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, AirbaseLevelCanBeIncreased)
{
	HoI4::State theState;
	theState.addAirBase(2);
	theState.addAirBase(2);

	ASSERT_EQ(4, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, AirbaseLevelCappedAtTen)
{
	HoI4::State theState;
	theState.addAirBase(2);
	theState.addAirBase(2);
	theState.addAirBase(10);

	ASSERT_EQ(10, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, ManpowerDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getManpower());
}


TEST(HoI4World_States_StateTests, ManpowerCanBeSet)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=12345\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {12};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	configInput << "manpower_factor = 1.0";
	Configuration testConfig;
	testConfig.instantiate(configInput);
	theState.addManpower(provinces, theProvinceMapper, testConfig);

	ASSERT_EQ(49380, theState.getManpower());
}


TEST(HoI4World_States_StateTests, HasResourcesDefaultsToFalse)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.hasResources());
}


TEST(HoI4World_States_StateTests, ResourcesCanBeAdded)
{
	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addResource("steel", 5.5);
	theState.addResource("oil", 7.25);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={"
						<< "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\tresources={\n";
	expectedOutput << "\t\toil=7.250\n";
	expectedOutput << "\t\tsteel=5.500\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 3\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t";
	expectedOutput << "\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tmanpower=0\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	std::stringstream output;
	outputHoI4State(output, theState, testConfig);

	ASSERT_TRUE(theState.hasResources());
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionDefaultsToMissing)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetManually)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setVPLocation(12);

	ASSERT_EQ(12, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapital)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(12));
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {12};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getVPLocation(), 12);
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaAristocrats)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=123456\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\taristocrats={\n";
	provinceInput2 << "\t\tsize=12345\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	auto anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {24};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaBureaucrats)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=123456\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\tbureaucrats={\n";
	provinceInput2 << "\t\tsize=12345\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	auto anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {24};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaCapitalists)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=123456\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\tcapitalists={\n";
	provinceInput2 << "\t\tsize=12345\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	auto anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {24};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromMostPopulousProvince)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=12345\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	auto theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\tfarmers={\n";
	provinceInput2 << "\t\tsize=123456\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	auto anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {24};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionLoggedIfNotSet)
{
	std::set<const Vic2::Province*> provinces;

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillRepeatedly(testing::Return(std::set<int>{}));
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");

	mockProvinceMapper theProvinceMapper;

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	std::stringstream log;
	auto coutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	std::cout.rdbuf(coutBuffer);

	ASSERT_EQ(std::nullopt, theState.getVPLocation());
	ASSERT_EQ(log.str(), "Could not create VP for state 42\n");
}


TEST(HoI4World_States_StateTests, DebugVPsCanBeAdded)
{
	mockVic2State sourceState;
	std::set<int> hoi4Provinces;
	hoi4Provinces.insert(12);
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));
	std::set<const Vic2::Province*> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {12};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	ASSERT_EQ(std::set<int>{12}, theState.getDebugVPs());
}


TEST(HoI4World_States_StateTests, SecondaryDebugVPsCanBeAdded)
{
	mockVic2State sourceState;
	std::set<int> hoi4Provinces;
	hoi4Provinces.insert(12);
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));
	std::set<const Vic2::Province*> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(sourceState, 42, "TAG");

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {12, 13};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	std::set<int> expectedVps{12, 13};
	ASSERT_EQ(expectedVps, theState.getSecondaryDebugVPs());
}


TEST(HoI4World_States_StateTests, DebugVpsAreOutput)
{
	mockVic2State sourceState;
	std::set<int> hoi4Provinces{12, 24};
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(12));
	std::set<const Vic2::Province*> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(13);
	theState.addProvince(24);
	theState.addProvince(25);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNumbers = {12, 13};
	std::optional<std::vector<int>> mapping = mappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillRepeatedly(testing::Return(mapping));
	std::vector<int> moreMappingNumbers = {24, 25};
	std::optional<std::vector<int>> anotherMapping = moreMappingNumbers;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillRepeatedly(testing::Return(anotherMapping));

	std::stringstream configInput;
	configInput << "debug = yes";
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(sourceState, theProvinceMapper, testConfig);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={"
						<< "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tvictory_points = {\n";
	expectedOutput << "\t\t\t12 11\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tvictory_points = { 24 5\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t\tvictory_points = { 13 1 }\n";
	expectedOutput << "\t\tvictory_points = { 24 1 }\n";
	expectedOutput << "\t\tvictory_points = { 25 1 }\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 3\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 13 24 25 ";
	expectedOutput << "\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tmanpower=0\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationDefaultsToMissing)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationCanBeAssigned)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);

	ASSERT_EQ(12, *theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationGoesToLargestBase)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);
	theState.addProvince(24);
	theState.addNavalBase(5, 24);

	ASSERT_EQ(24, *theState.getMainNavalLocation());
}