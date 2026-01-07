#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/CoastalProvinces.h"
#include "src/HOI4World/Map/CoastalProvincesBuilder.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/StateCategoriesBuilder.h"
#include "src/Mappers/Country/CountryMapperBuilder.h"
#include "src/Mappers/Provinces/ProvinceMapperBuilder.h"
#include "src/OutHoi4/States/OutHoI4State.h"
#include "src/V2World/Pops/Pop.h"
#include "src/V2World/Provinces/Province.h"
#include "src/V2World/Provinces/ProvinceBuilder.h"
#include "src/V2World/States/StateBuilder.h"
#include <optional>
#include <sstream>



using Vic2::Pop;
using Vic2::PopOptions;


TEST(HoI4World_States_StateTests, DefaultsAreAsSet)
{
	const HoI4::State theState;

	EXPECT_EQ(0, theState.getID());
	EXPECT_TRUE(theState.getProvinces().empty());
	EXPECT_TRUE(theState.getOwner().empty());
	EXPECT_TRUE(theState.getCores().empty());
	EXPECT_TRUE(theState.getClaims().empty());
	EXPECT_TRUE(theState.getControlledProvinces().empty());
	EXPECT_FALSE(theState.isImpassable());
	EXPECT_EQ(0, theState.getDockyards());
	EXPECT_EQ(0, theState.getCivFactories());
	EXPECT_EQ(theState.getMilFactories(), 0);
	EXPECT_FLOAT_EQ(1.0F, theState.getInfrastructure());
	EXPECT_TRUE(theState.getNavalBases().empty());
	EXPECT_EQ(0, theState.getAirbaseLevel());
	EXPECT_EQ(1, theState.getManpower());
	EXPECT_FALSE(theState.hasResources());
	EXPECT_FALSE(theState.getVPLocation());
	EXPECT_FALSE(theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, IdIsReturned)
{
	const auto sourceState = *Vic2::State::Builder().build();
	const HoI4::State theState(sourceState, 42, "TAG");

	EXPECT_EQ(theState.getID(), 42);
}


TEST(HoI4World_States_StateTests, ProvincesCanbeAdded)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(5);
	theState.addProvince(13);

	EXPECT_THAT(theState.getProvinces(), testing::UnorderedElementsAre(5, 13));
}


TEST(HoI4World_States_StateTests, OwnerIsReturned)
{
	const auto sourceState = *Vic2::State::Builder().build();
	const HoI4::State theState(sourceState, 42, "TAG");

	EXPECT_EQ(theState.getOwner(), "TAG");
}


TEST(HoI4World_States_StateTests, CoresCanbeAdded)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	std::set<std::string> cores;
	cores.insert("TAG");
	cores.insert("COR");
	theState.addCores(cores);

	EXPECT_THAT(theState.getCores(), testing::UnorderedElementsAre("TAG", "COR"));
}


TEST(HoI4World_States_StateTests, ClaimsCanbeAdded)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	std::set<std::string> claims;
	claims.insert("TAG");
	claims.insert("CLM");
	theState.addClaims(claims);

	EXPECT_THAT(theState.getClaims(), testing::UnorderedElementsAre("TAG", "CLM"));
}


TEST(HoI4World_States_StateTests, ControllersCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	theState.convertControlledProvinces({{12, "NOT"}},
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 *Mappers::CountryMapper::Builder().addMapping("NOT", "NOT").Build());

	EXPECT_THAT(theState.getControlledProvinces(), testing::ElementsAre(testing::Pair("NOT", std::set<int>{12})));
}


TEST(HoI4World_States_StateTests, ControllersConvertWithHoI4Tag)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	theState.convertControlledProvinces({{12, "NOT"}},
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 *Mappers::CountryMapper::Builder().addMapping("NOT", "HOI").Build());

	EXPECT_THAT(theState.getControlledProvinces(), testing::ElementsAre(testing::Pair("HOI", std::set<int>{12})));
}


TEST(HoI4World_States_StateTests, ControllersDontConvertForRebels)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	theState.convertControlledProvinces({{12, "REB"}},
		 *Mappers::ProvinceMapper::Builder().Build(),
		 *Mappers::CountryMapper::Builder().addMapping("REB", "REB").Build());

	EXPECT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, SetControlledProvinceSetsControlledProvinces)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setControlledProvince(1, "ONE");

	EXPECT_THAT(theState.getControlledProvinces(),
		 testing::UnorderedElementsAre(testing::Pair(std::string("ONE"), std::set{1})));
}


TEST(HoI4World_States_StateTests, SetControlledProvinceSetsMultipleControlledProvincesForOneNations)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setControlledProvince(1, "ONE");
	theState.setControlledProvince(2, "ONE");

	EXPECT_THAT(theState.getControlledProvinces(),
		 testing::UnorderedElementsAre(testing::Pair(std::string("ONE"), std::set{1, 2})));
}


TEST(HoI4World_States_StateTests, SetControlledProvinceDoesNotSetControlledProvincesForOwner)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setControlledProvince(1, "TAG");

	EXPECT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, ImpassableCanBeSet)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.makeImpassable();

	EXPECT_TRUE(theState.isImpassable());
}


TEST(HoI4World_States_StateTests, TotalFactoriesCanBeSet)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setEmployedWorkers(60000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 70000})}).build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addCores({"TAG"});

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(8, "mockedCategory").Build(),
		 theCoastalProvinces);

	EXPECT_EQ(6, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, TotalFactoriesHalvedByMissingCore)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setEmployedWorkers(60000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 70'000})}).build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(8, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_EQ(3, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, TotalFactoriesCappedAtTwelve)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setEmployedWorkers(500000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 60'000})}).build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addCores({"TAG"});

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(14, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_EQ(12, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, CappedFactoriesTransferToNextState)
{
	const auto sourceStateOne =
		 *Vic2::State::Builder()
				.setEmployedWorkers(150000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 60'000})}).build()})
				.build();
	const auto sourceStateTwo =
		 *Vic2::State::Builder()
				.setEmployedWorkers(100000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 60'000})}).build()})
				.build();

	HoI4::State stateOne(sourceStateOne, 42, "TAG");
	HoI4::State stateTwo(sourceStateTwo, 43, "TAG");
	stateOne.addCores({"TAG"});
	stateTwo.addCores({"TAG"});

	int ownerIndustryRemainder = 0;
	stateOne.convertIndustry(0.0001,
		 ownerIndustryRemainder,
		 *HoI4::StateCategories::Builder().addCategory(14, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());
	ownerIndustryRemainder = stateOne.getIndustryRemainder();

	stateTwo.convertIndustry(0.0001,
		 ownerIndustryRemainder,
		 *HoI4::StateCategories::Builder().addCategory(14, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());
	ownerIndustryRemainder = stateTwo.getIndustryRemainder();

	EXPECT_EQ(12, stateOne.getMilFactories() + stateOne.getCivFactories() + stateOne.getDockyards());
	EXPECT_EQ(12, stateTwo.getMilFactories() + stateTwo.getCivFactories() + stateTwo.getDockyards());
	EXPECT_EQ(1, ownerIndustryRemainder);
}


TEST(HoI4World_States_StateTests, categoryCanBeChanged)
{
	const auto sourceState = *Vic2::State::Builder()
											.setEmployedWorkers(500000)
											.setProvinces({Vic2::Province::Builder()
													  .setNumber(0)
													  .setPops({Pop(PopOptions{.size = 60'000})})
													  .setRailLevel(0)
													  .build()})
											.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(14, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_EQ("mockedCategory", theState.getCategory());
}


TEST(HoI4World_States_StateTests, InfrastructureAddedPerThreeRailLevels)
{
	const auto sourceState =
		 *Vic2::State::Builder().setProvinces({Vic2::Province::Builder().setNumber(0).setRailLevel(6).build()}).build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(2, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_FLOAT_EQ(3.0F, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForAnyFactories)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setEmployedWorkers(10'000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 100'000})}).build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(7, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_FLOAT_EQ(1.5F, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForSixFactories)
{
	const auto sourceState = *Vic2::State::Builder()
											.setEmployedWorkers(60'000)
											.setProvinces({Vic2::Province::Builder()
													  .setNumber(0)
													  .setPops({Pop(PopOptions{.size = 100'000})})

													  .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(9, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_FLOAT_EQ(2.0F, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForTenFactories)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setEmployedWorkers(100'000)
				.setProvinces({Vic2::Province::Builder().setNumber(0).setPops({Pop(PopOptions{.size = 100'000})}).build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 0,
		 *HoI4::StateCategories::Builder().addCategory(13, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder().Build());

	EXPECT_FLOAT_EQ(2.5F, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, NavalBasesCanBeConverted)
{
	HoI4::State theState;
	theState.addProvince(1);
	theState.addProvince(2);

	theState.convertNavalBases({{1, 1}, {2, 1}},
		 *HoI4::CoastalProvinces::Builder().addCoastalProvince(1, {}).addCoastalProvince(2, {}).Build(),
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(1, {1}).addVic2ToHoI4ProvinceMap(2, {2}).Build());

	EXPECT_THAT(theState.getNavalBases(), testing::ElementsAre(testing::Pair(1, 2), testing::Pair(2, 2)));
}


TEST(HoI4World_States_StateTests, AirbaseLevelCanBeSet)
{
	HoI4::State theState;
	theState.addAirBase(2);

	EXPECT_EQ(2, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, AirbaseLevelCanBeIncreased)
{
	HoI4::State theState;
	theState.addAirBase(2);
	theState.addAirBase(3);

	EXPECT_EQ(5, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, AirbaseLevelCappedAtTen)
{
	HoI4::State theState;
	theState.addAirBase(5);
	theState.addAirBase(10);

	EXPECT_EQ(10, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, ManpowerCanBeSet)
{
	const std::shared_ptr<Vic2::Province> theProvince =
		 Vic2::Province::Builder()
			  .setNumber(0)
			  .setNumber(12)
			  .setOwner("TAG")
			  .setController("REB")
			  .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 12'345})})
			  .build();
	std::vector<std::shared_ptr<Vic2::Province>> provinces;
	provinces.push_back(theProvince);

	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const Configuration theConfiguration;
	theState.addManpower(provinces,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 theConfiguration);

	EXPECT_EQ(49380, theState.getManpower());
}


TEST(HoI4World_States_StateTests, ResourcesCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder().build();
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
	expectedOutput << "\t\t\tinfrastructure = 1\n";
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
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "\n";
	expectedOutput << "\tlocal_supplies=10.0\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, false);

	EXPECT_TRUE(theState.hasResources());
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetManually)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setVPLocation(12);

	EXPECT_EQ(12, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapital)
{
	const auto sourceState = *Vic2::State::Builder().setCapitalProvince(12).build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 theConfiguration);

	EXPECT_EQ(theState.getVPLocation(), 12);
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaAristocrats)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setProvinces({Vic2::Province::Builder()
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 123'456})})
										 .build(),
					 Vic2::Province::Builder()
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(std::vector{Pop(PopOptions{.type = "aristocrats", .size = 12'345})})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	EXPECT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaBureaucrats)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setProvinces({Vic2::Province::Builder()
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 123'456})})
										 .build(),
					 Vic2::Province::Builder()
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(std::vector{Pop(PopOptions{.type = "bureaucrats", .size = 12'345})})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	EXPECT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaCapitalists)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setProvinces({Vic2::Province::Builder()
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 123'456})})
										 .build(),
					 Vic2::Province::Builder()
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(std::vector{Pop(PopOptions{.type = "capitalists", .size = 123'456})})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	EXPECT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromMostPopulousProvince)
{
	const auto sourceState =
		 *Vic2::State::Builder()
				.setProvinces({Vic2::Province::Builder()
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 123'456})})
										 .build(),
					 Vic2::Province::Builder()
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 123'456})})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	EXPECT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionLoggedIfNotSet)
{
	const auto sourceState = *Vic2::State::Builder().build();

	HoI4::State theState(sourceState, 42, "TAG");

	const Configuration theConfiguration;

	const std::stringstream log;
	const auto coutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	theState.tryToCreateVP(sourceState, *Mappers::ProvinceMapper::Builder().Build(), theConfiguration);

	std::cout.rdbuf(coutBuffer);

	EXPECT_EQ(std::nullopt, theState.getVPLocation());
	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Could not create VP for state 42"));
}


TEST(HoI4World_States_StateTests, DebugVPsCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder().setProvinceNumbers({12}).build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 theConfiguration);

	EXPECT_EQ(std::set{12}, theState.getDebugVPs());
}


TEST(HoI4World_States_StateTests, SecondaryDebugVPsCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder().setProvinceNumbers({12}).build();

	HoI4::State theState(sourceState, 42, "TAG");

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12, 13}).Build(),
		 theConfiguration);

	EXPECT_THAT(theState.getSecondaryDebugVPs(), testing::ElementsAre(12, 13));
}


TEST(HoI4World_States_StateTests, DebugVpsAreOutput)
{
	const auto sourceState = *Vic2::State::Builder().setProvinceNumbers({12, 24}).setCapitalProvince(12).build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(13);
	theState.addProvince(24);
	theState.addProvince(25);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder()
			  .addVic2ToHoI4ProvinceMap(12, {12, 13})
			  .addVic2ToHoI4ProvinceMap(24, {24, 25})
			  .Build(),
		 theConfiguration);

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
	expectedOutput << "\t\t\t12 10\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tvictory_points = { 24 5\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t\tvictory_points = { 13 1 }\n";
	expectedOutput << "\t\tvictory_points = { 24 1 }\n";
	expectedOutput << "\t\tvictory_points = { 25 1 }\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 1\n";
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
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "\n";
	expectedOutput << "\tlocal_supplies=10.0\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, true);

	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationCanBeAssigned)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);

	EXPECT_EQ(12, *theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationGoesToLargestBase)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);
	theState.addProvince(24);
	theState.addNavalBase(5, 24);

	EXPECT_EQ(24, *theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, LandmarksCanBeAssigned)
{
	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addLandmark({"landmark_test", 1, "has_dlc = \"Gotterdammerung\""}, 12);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={"
						<< "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 1\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\t\t\t12 = {\n";
	expectedOutput << "\t\t\t\tlandmark_test = {\n";
	expectedOutput << "\t\t\t\t\tlevel = 1\n";
	expectedOutput << "\t\t\t\t\tallowed = {\n";
	expectedOutput << "\t\t\t\t\t\thas_dlc = \"Gotterdammerung\"\n";
	expectedOutput << "\t\t\t\t\t}\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 ";
	expectedOutput << "\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "\n";
	expectedOutput << "\tlocal_supplies=10.0\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, false);

	EXPECT_EQ(expectedOutput.str(), output.str());
}