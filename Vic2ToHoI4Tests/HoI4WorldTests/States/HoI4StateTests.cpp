/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../../Mocks/CountryMapperMock.h"
#include "../../Mocks/ProvinceMapperMock.h"
#include "../../Mocks/StateCategoriesMock.h"
#include "../../Mocks/Vic2StateMock.h"
#include "../Vic2ToHoI4/Source/Configuration.h"
#include "../Vic2ToHoI4/Source/Hoi4Outputter/States/HoI4StateOutputter.h"
#include "../Vic2ToHoI4/Source/HOI4World/CoastalProvinces.h"
#include "../Vic2ToHoI4/Source/HOI4World/States/HoI4State.h"
#include "../Vic2ToHoI4/Source/HoI4World/States/StateCategories.h"
#include "../Vic2ToHoI4/Source/V2World/Province.h"
#include "../Vic2ToHoI4/Source/V2World/State.h"
#include <optional>
#include <sstream>



TEST(HoI4World_StateTests, sourceStateIsReturned)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	Vic2::State* sourceState = new Vic2::State(input, "");
	HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getSourceState(), sourceState);
}


TEST(HoI4World_StateTests, idIsReturned)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getID(), 42);
}


TEST(HoI4World_StateTests, idIsOutput)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "");

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, provincesDefaultToEmpty)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getProvinces().size(), 0);
}


TEST(HoI4World_StateTests, provincesCanbeAdded)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	theState.addProvince(5);
	theState.addProvince(13);

	ASSERT_EQ(theState.getProvinces().size(), 2);
	ASSERT_EQ(theState.getProvinces().count(5), 1);
	ASSERT_EQ(theState.getProvinces().count(13), 1);
}


TEST(HoI4World_StateTests, provincesAreOutput)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "");
	theState.addProvince(5);
	theState.addProvince(13);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t5 13 \n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tmanpower=0\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	std::stringstream output;
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, ownerIsReturned)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getOwner(), "TAG");
}


TEST(HoI4World_StateTests, ownerIsOutput)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, coresDefaultToEmpty)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getCores().size(), 0);
}


TEST(HoI4World_StateTests, coresCanbeAdded)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	std::set<std::string> cores;
	cores.insert("TAG");
	cores.insert("COR");
	theState.addCores(cores);

	ASSERT_EQ(theState.getCores().size(), 2);
	ASSERT_EQ(theState.getCores().count("TAG"), 1);
	ASSERT_EQ(theState.getCores().count("COR"), 1);
}


TEST(HoI4World_StateTests, coresAreOutput)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	std::set<std::string> cores;
	cores.insert("TAG");
	cores.insert("COR");
	theState.addCores(cores);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tadd_core_of = COR\n";
	expectedOutput << "\t\tadd_core_of = TAG\n";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, impassableDefaultsToFalse)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_FALSE(theState.isImpassable());
}


TEST(HoI4World_StateTests, impassableCanBeSet)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	theState.makeImpassable();

	ASSERT_TRUE(theState.isImpassable());
}


TEST(HoI4World_StateTests, impassableIsOutput)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.makeImpassable();

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\timpassable = yes\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, dockyardsDefaultsToZero)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getDockyards(), 0);
}


TEST(HoI4World_StateTests, civFactoriesDefaultsToZero)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getCivFactories(), 0);
}


TEST(HoI4World_StateTests, milFactoriesDefaultsToZero)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getMilFactories(), 0);
}


TEST(HoI4World_StateTests, totalFactoriesCanBeSet)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(50000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(7)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards(), 5);
}


TEST(HoI4World_StateTests, totalFactoriesCappedAtTwelve)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(500000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(14)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards(), 12);
}

/* Test is flaky due to randomness in industry assignment
TEST(HoI4World_StateTests, categoryCanBeChanged)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(500000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(0));
	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(14)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 6\n";
	expectedOutput << "\t\t\tindustrial_complex = 8\n";
	expectedOutput << "\t\t\tarms_factory = 4\n";
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
	expectedOutput << "\tstate_category=mockedCategory\n";
	expectedOutput << "}\n";

	std::stringstream output;
	theState.output(output);

	ASSERT_EQ(expectedOutput.str(), output.str());
}*/


TEST(HoI4World_StateTests, infrastructureDefaultsToZero)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getInfrastructure(), 0);
}


TEST(HoI4World_StateTests, infrastructureCanBeSet)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(0));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(2)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getInfrastructure(), 3);
}


TEST(HoI4World_StateTests, infrastructureIsOutput)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(0));
	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(2)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
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
	expectedOutput << "\tstate_category=mockedCategory\n";
	expectedOutput << "}\n";

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	std::stringstream output;
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, infrastructureAddedPerTwoRailLevels)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(2)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getInfrastructure(), 6);
}


TEST(HoI4World_StateTests, infrastructureForOverFourFactories)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(50000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(7)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getInfrastructure(), 7);
}


TEST(HoI4World_StateTests, infrastructureForOverSixFactories)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(70000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(9)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getInfrastructure(), 8);
}


TEST(HoI4World_StateTests, infrastructureForOverTenFactories)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(110000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(13)).WillOnce(testing::Return("mockedCategory"));

	HoI4::coastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(theState.getInfrastructure(), 9);
}


TEST(HoI4World_StateTests, manpowerDefaultsToZero)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_EQ(theState.getManpower(), 0);
}


TEST(HoI4World_StateTests, manpowerCanBeSet)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=12345\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 12 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	configInput << "manpower_factor = 1.0";
	Configuration testConfig;
	testConfig.instantiate(configInput);
	theState.addManpower(theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getManpower(), 49380);
}


TEST(HoI4World_StateTests, victoryPointPositionDefaultsToMissing)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getVPLocation());
}


TEST(HoI4World_StateTests, victoryPointPositionCanBeSetManually)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	theState.setVPLocation(12);

	ASSERT_EQ(theState.getVPLocation(), 12);
}


TEST(HoI4World_StateTests, victoryPointPositionCanBeSetFromStateCapital)
{
	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(12));
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 12 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getVPLocation(), 12);
}


TEST(HoI4World_StateTests, victoryPointPositionCanBeSetFromStateCapitalDetectedViaAristocrats)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=123456\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\taristocrats={\n";
	provinceInput2 << "\t\tsize=12345\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	Vic2::Province* anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 24 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getVPLocation(), 24);
}


TEST(HoI4World_StateTests, victoryPointPositionCanBeSetFromStateCapitalDetectedViaBureaucrats)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=123456\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\tbureaucrats={\n";
	provinceInput2 << "\t\tsize=12345\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	Vic2::Province* anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 24 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getVPLocation(), 24);
}


TEST(HoI4World_StateTests, victoryPointPositionCanBeSetFromStateCapitalDetectedViaCapitalists)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=123456\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\tcapitalists={\n";
	provinceInput2 << "\t\tsize=12345\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	Vic2::Province* anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 24 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getVPLocation(), 24);
}


TEST(HoI4World_StateTests, victoryPointPositionCanBeSetFromMostPopulousProvince)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "\tfarmers={\n";
	provinceInput << "\t\tsize=12345\n";
	provinceInput << "\t}\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);

	std::stringstream provinceInput2;
	provinceInput2 << "={\n";
	provinceInput2 << "\towner=TAG\n";
	provinceInput2 << "\tcontroller=REB\n";
	provinceInput2 << "\tfarmers={\n";
	provinceInput2 << "\t\tsize=123456\n";
	provinceInput2 << "\t}\n";
	provinceInput2 << "}";
	Vic2::Province* anotherProvince = new Vic2::Province("24", provinceInput2);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);
	provinces.insert(anotherProvince);

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 24 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	ASSERT_EQ(theState.getVPLocation(), 24);
}


TEST(HoI4World_StateTests, victoryPointPositionLoggedIfNotSet)
{
	std::set<const Vic2::Province*> provinces;

	mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinceNums()).WillRepeatedly(testing::Return(std::set<int>{}));
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockProvinceMapper theProvinceMapper;

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	std::stringstream log;
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(log.rdbuf()); //redirect std::cout to log

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	std::cout.rdbuf(coutbuf); //reset to standard output again

	ASSERT_EQ(theState.getVPLocation(), std::nullopt);
	ASSERT_EQ("Could not create VP for state 42\n", log.str());
}


TEST(HoI4World_StateTests, debugVPsCanBeAdded)
{
	mockVic2State sourceState;
	std::set<int> hoi4Provinces;
	hoi4Provinces.insert(12);
	EXPECT_CALL(sourceState, getProvinceNums()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));
	std::set<const Vic2::Province*> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 12 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	ASSERT_EQ(std::set<int>{12}, theState.getDebugVPs());
}


TEST(HoI4World_StateTests, secondaryDebugVPsCanBeAdded)
{
	mockVic2State sourceState;
	std::set<int> hoi4Provinces;
	hoi4Provinces.insert(12);
	EXPECT_CALL(sourceState, getProvinceNums()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));
	std::set<const Vic2::Province*> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(&sourceState, 42, "TAG");

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 12, 13 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(mapping));

	std::stringstream configInput;
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	std::set<int> expectedVps{ 12, 13 };
	ASSERT_EQ(expectedVps, theState.getSecondaryDebugVPs());
}


TEST(HoI4World_StateTests, debugVpsAreOutput)
{
	mockVic2State sourceState;
	std::set<int> hoi4Provinces{ 12, 24 };
	EXPECT_CALL(sourceState, getProvinceNums()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(12));
	std::set<const Vic2::Province*> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(13);
	theState.addProvince(24);
	theState.addProvince(25);

	mockProvinceMapper theProvinceMapper;
	std::vector<int> mappingNums = { 12, 13 };
	std::optional<std::vector<int>> mapping = mappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillRepeatedly(testing::Return(mapping));
	std::vector<int> moreMappingNums = { 24, 25 };
	std::optional<std::vector<int>> anotherMapping = moreMappingNums;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(24)).WillRepeatedly(testing::Return(anotherMapping));

	std::stringstream configInput;
	configInput << "debug = yes";
	Configuration testConfig;
	testConfig.instantiate(configInput);

	theState.tryToCreateVP(theProvinceMapper, testConfig);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
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
	expectedOutput << "\t\t\tinfrastructure = 0\n";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, mainNavalBaseLocationDefaultsToMissing)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getMainNavalLocation());
}


TEST(HoI4World_StateTests, mainNavalBaseLocationCanBeAssigned)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);

	ASSERT_EQ(*theState.getMainNavalLocation(), 12);
}


TEST(HoI4World_StateTests, mainNavalBaseLocationGoesToLargestBase)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);
	theState.addProvince(24);
	theState.addNavalBase(5, 24);

	ASSERT_EQ(*theState.getMainNavalLocation(), 24);
}


TEST(HoI4World_StateTests, navalBasesAreOutput)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addNavalBase(1, 12);
	theState.addProvince(24);
	theState.addNavalBase(5, 24);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\t12 = {\n";
	expectedOutput << "\t\t\t\tnaval_base = 1\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\t24 = {\n";
	expectedOutput << "\t\t\t\tnaval_base = 5\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 24 ";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, resourcesCanBeAdded)
{
	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addResource("steel", 5.5);
	theState.addResource("oil", 7.25);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
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
	expectedOutput << "\t\t\tinfrastructure = 0\n";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, controllersCanBeAdded)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=NOT\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));

	mockProvinceMapper theProvinceMapper;
	std::optional<std::vector<int>> possibleMappedProvinces;
	std::vector<int> mappedProvinces;
	mappedProvinces.push_back(12);
	possibleMappedProvinces = mappedProvinces;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(possibleMappedProvinces));

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "NOT";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("NOT")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(theProvinceMapper, theCountryMapper);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tNOT = {\n";
	expectedOutput << "\t\t\tset_province_controller = 12\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 ";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, controllersConvertWithHoI4Tag)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=NOT\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));

	mockProvinceMapper theProvinceMapper;
	std::optional<std::vector<int>> possibleMappedProvinces;
	std::vector<int> mappedProvinces;
	mappedProvinces.push_back(12);
	possibleMappedProvinces = mappedProvinces;
	EXPECT_CALL(theProvinceMapper, getVic2ToHoI4ProvinceMapping(12)).WillOnce(testing::Return(possibleMappedProvinces));

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "HOI";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("NOT")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(theProvinceMapper, theCountryMapper);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tHOI = {\n";
	expectedOutput << "\t\t\tset_province_controller = 12\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 ";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_StateTests, controllersDontConvertForRebels)
{
	std::stringstream provinceInput;
	provinceInput << "={\n";
	provinceInput << "\towner=TAG\n";
	provinceInput << "\tcontroller=REB\n";
	provinceInput << "}";
	Vic2::Province* theProvince = new Vic2::Province("12", provinceInput);
	std::set<const Vic2::Province*> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(&sourceState, 42, "TAG");
	theState.addProvince(12);
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));

	mockProvinceMapper theProvinceMapper;

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "REB";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("REB")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(theProvinceMapper, theCountryMapper);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={" << "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 0\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 ";
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
	HoI4::outputHoI4State(output, theState, testConfig);

	ASSERT_EQ(expectedOutput.str(), output.str());
}