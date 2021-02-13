#include "Configuration.h"
#include "HOI4World/Map/CoastalProvinces.h"
#include "HOI4World/Map/CoastalProvincesBuilder.h"
#include "HOI4World/States/HoI4State.h"
#include "HOI4World/States/StateCategoriesBuilder.h"
#include "Mappers/Country/CountryMapperBuilder.h"
#include "Mappers/Provinces/ProvinceMapperBuilder.h"
#include "OutHoi4/States/OutHoI4State.h"
#include "V2World/Pops/PopBuilder.h"
#include "V2World/Provinces/Province.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "V2World/States/StateBuilder.h"
#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>
#include <optional>
#include <sstream>


TEST(HoI4World_States_StateTests, IdDefaultsToZero)
{
	const HoI4::State theState;

	ASSERT_EQ(0, theState.getID());
}


TEST(HoI4World_States_StateTests, IdIsReturned)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getID(), 42);
}


TEST(HoI4World_States_StateTests, ProvincesDefaultToEmpty)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getProvinces().empty());
}


TEST(HoI4World_States_StateTests, ProvincesCanbeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(5);
	theState.addProvince(13);

	ASSERT_EQ(2, theState.getProvinces().size());
	ASSERT_TRUE(theState.getProvinces().contains(5));
	ASSERT_TRUE(theState.getProvinces().contains(13));
}


TEST(HoI4World_States_StateTests, OwnerDefaultsToEmpty)
{
	const HoI4::State theState;

	ASSERT_TRUE(theState.getOwner().empty());
}


TEST(HoI4World_States_StateTests, OwnerIsReturned)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getOwner(), "TAG");
}


TEST(HoI4World_States_StateTests, CoresDefaultToEmpty)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getCores().empty());
}


TEST(HoI4World_States_StateTests, CoresCanbeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	std::set<std::string> cores;
	cores.insert("TAG");
	cores.insert("COR");
	theState.addCores(cores);

	ASSERT_EQ(2, theState.getCores().size());
	ASSERT_TRUE(theState.getCores().contains("TAG"));
	ASSERT_TRUE(theState.getCores().contains("COR"));
}


TEST(HoI4World_States_StateTests, ClaimsDefaultToEmpty)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getClaims().empty());
}


TEST(HoI4World_States_StateTests, ClaimsCanbeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	std::set<std::string> claims;
	claims.insert("TAG");
	claims.insert("CLM");
	theState.addClaims(claims);

	ASSERT_EQ(2, theState.getClaims().size());
	ASSERT_TRUE(theState.getClaims().contains("TAG"));
	ASSERT_TRUE(theState.getClaims().contains("CLM"));
}


TEST(HoI4World_States_StateTests, ControlledProvincesDefaultToEmpty)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, ControllersCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	theState.convertControlledProvinces({{12, "NOT"}},
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 *Mappers::CountryMapper::Builder{}.addMapping("NOT", "NOT").Build());

	std::map<std::string, std::set<int>> expectedControlledProvinces{{"NOT", {12}}};
	ASSERT_EQ(expectedControlledProvinces, theState.getControlledProvinces());
}


TEST(HoI4World_States_StateTests, ControllersConvertWithHoI4Tag)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	theState.convertControlledProvinces({{12, "NOT"}},
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 *Mappers::CountryMapper::Builder{}.addMapping("NOT", "HOI").Build());

	std::map<std::string, std::set<int>> expectedControlledProvinces{{"HOI", {12}}};
	ASSERT_EQ(expectedControlledProvinces, theState.getControlledProvinces());
}


TEST(HoI4World_States_StateTests, ControllersDontConvertForRebels)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	theState.convertControlledProvinces({{12, "REB"}},
		 *Mappers::ProvinceMapper::Builder().Build(),
		 *Mappers::CountryMapper::Builder{}.addMapping("REB", "REB").Build());

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, SetControlledProvinceSetsControlledProvinces)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setControlledProvince(1, "ONE");

	ASSERT_THAT(theState.getControlledProvinces(),
		 testing::UnorderedElementsAre(testing::Pair(std::string("ONE"), std::set<int>{1})));
}


TEST(HoI4World_States_StateTests, SetControlledProvinceSetsMultipleControlledProvincesForOneNations)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setControlledProvince(1, "ONE");
	theState.setControlledProvince(2, "ONE");

	ASSERT_THAT(theState.getControlledProvinces(),
		 testing::UnorderedElementsAre(testing::Pair(std::string("ONE"), std::set<int>{1, 2})));
}


TEST(HoI4World_States_StateTests, SetControlledProvinceDoesNotSetControlledProvincesForOwner)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setControlledProvince(1, "TAG");

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST(HoI4World_States_StateTests, ImpassableDefaultsToFalse)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.isImpassable());
}


TEST(HoI4World_States_StateTests, ImpassableCanBeSet)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.makeImpassable();

	ASSERT_TRUE(theState.isImpassable());
}


TEST(HoI4World_States_StateTests, DockyardsDefaultsToZero)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getDockyards());
}


TEST(HoI4World_States_StateTests, CivFactoriesDefaultsToZero)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getCivFactories());
}


TEST(HoI4World_States_StateTests, MilFactoriesDefaultsToZero)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getMilFactories(), 0);
}


TEST(HoI4World_States_StateTests, TotalFactoriesCanBeSet)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(60000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(70000).build()})
																	 .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addCores({"TAG"});

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(8, "mockedCategory").Build(),
		 theCoastalProvinces);

	ASSERT_EQ(6, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, TotalFactoriesHalvedByMissingCore)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(60000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(70000).build()})
																	 .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(8, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

	ASSERT_EQ(3, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, TotalFactoriesCappedAtTwelve)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(500000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(60000).build()})
																	 .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addCores({"TAG"});

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(14, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

	ASSERT_EQ(12, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST(HoI4World_States_StateTests, categoryCanBeChanged)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(500000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(60000).build()})
																	 .setRailLevel(0)
																	 .build()})
											.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(14, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

	ASSERT_EQ("mockedCategory", theState.getCategory());
}


TEST(HoI4World_States_StateTests, InfrastructureDefaultsToThree)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(3, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureAddedPerTwoRailLevels)
{
	const auto sourceState =
		 *Vic2::State::Builder{}.setProvinces({Vic2::Province::Builder{}.setNumber(0).setRailLevel(6).build()}).build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(2, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

	ASSERT_EQ(6, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForOverFourFactories)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(50000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(100000).build()})
																	 .setRailLevel(6)
																	 .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(7, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

	ASSERT_EQ(7, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForOverSixFactories)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(70000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(100000).build()})
																	 .setRailLevel(6)
																	 .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(9, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

	ASSERT_EQ(8, theState.getInfrastructure());
}


TEST(HoI4World_States_StateTests, InfrastructureForOverTenFactories)
{
	const auto sourceState = *Vic2::State::Builder{}
											.setEmployedWorkers(110000)
											.setProvinces({Vic2::Province::Builder{}
																	 .setNumber(0)
																	 .setPops({*Vic2::Pop::Builder{}.setSize(100000).build()})
																	 .setRailLevel(6)
																	 .build()})
											.build();

	HoI4::State theState(sourceState, 42, "TAG");

	theState.convertIndustry(0.0001,
		 *HoI4::StateCategories::Builder{}.addCategory(13, "mockedCategory").Build(),
		 *HoI4::CoastalProvinces::Builder{}.Build());

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

	theState.convertNavalBases({{1, 1}, {2, 1}},
		 *HoI4::CoastalProvinces::Builder{}.addCoastalProvince(1, {}).addCoastalProvince(2, {}).Build(),
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(1, {1}).addVic2ToHoI4ProvinceMap(2, {2}).Build());

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
	theState.addAirBase(3);

	ASSERT_EQ(5, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, AirbaseLevelCappedAtTen)
{
	HoI4::State theState;
	theState.addAirBase(5);
	theState.addAirBase(10);

	ASSERT_EQ(10, theState.getAirbaseLevel());
}


TEST(HoI4World_States_StateTests, ManpowerReturnsMinimumOfOne)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(1, theState.getManpower());
}


TEST(HoI4World_States_StateTests, ManpowerCanBeSet)
{
	const std::shared_ptr<Vic2::Province> theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(0)
			  .setNumber(12)
			  .setOwner("TAG")
			  .setController("REB")
			  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("farmers").setSize(12345).build()})
			  .build();
	std::set<std::shared_ptr<Vic2::Province>> provinces;
	provinces.insert(theProvince);

	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const Configuration theConfiguration;
	theState.addManpower(provinces,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 theConfiguration);

	ASSERT_EQ(49380, theState.getManpower());
}


TEST(HoI4World_States_StateTests, HasResourcesDefaultsToFalse)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.hasResources());
}


TEST(HoI4World_States_StateTests, ResourcesCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
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
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, false);

	ASSERT_TRUE(theState.hasResources());
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionDefaultsToMissing)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetManually)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setVPLocation(12);

	ASSERT_EQ(12, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapital)
{
	const auto sourceState = *Vic2::State::Builder{}.setCapitalProvince(12).build();
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 theConfiguration);

	ASSERT_EQ(theState.getVPLocation(), 12);
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaAristocrats)
{
	const auto sourceState =
		 *Vic2::State::Builder{}
				.setProvinces({Vic2::Province::Builder{}
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector<Vic2::Pop>{
											  *Vic2::Pop::Builder{}.setType("farmers").setSize(123456).build()})
										 .build(),
					 Vic2::Province::Builder{}
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(
								std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("aristocrats").setSize(12345).build()})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaBureaucrats)
{
	const auto sourceState =
		 *Vic2::State::Builder{}
				.setProvinces({Vic2::Province::Builder{}
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector<Vic2::Pop>{
											  *Vic2::Pop::Builder{}.setType("farmers").setSize(123456).build()})
										 .build(),
					 Vic2::Province::Builder{}
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(
								std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("bureaucrats").setSize(12345).build()})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaCapitalists)
{
	const auto sourceState =
		 *Vic2::State::Builder{}
				.setProvinces({Vic2::Province::Builder{}
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector<Vic2::Pop>{
											  *Vic2::Pop::Builder{}.setType("farmers").setSize(123456).build()})
										 .build(),
					 Vic2::Province::Builder{}
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(
								std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("capitalists").setSize(12345).build()})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromMostPopulousProvince)
{
	const auto sourceState =
		 *Vic2::State::Builder{}
				.setProvinces({Vic2::Province::Builder{}
										 .setNumber(0)
										 .setNumber(12)
										 .setOwner("TAG")
										 .setController("REB")
										 .setPops(std::vector<Vic2::Pop>{
											  *Vic2::Pop::Builder{}.setType("farmers").setSize(12345).build()})
										 .build(),
					 Vic2::Province::Builder{}
						  .setNumber(0)
						  .setNumber(24)
						  .setOwner("TAG")
						  .setController("REB")
						  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("farmers").setSize(123456).build()})
						  .build()})
				.build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(24, {24}).Build(),
		 theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST(HoI4World_States_StateTests, VictoryPointPositionLoggedIfNotSet)
{
	const auto sourceState = *Vic2::State::Builder{}.build();

	HoI4::State theState(sourceState, 42, "TAG");

	const Configuration theConfiguration;

	const std::stringstream log;
	const auto coutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	theState.tryToCreateVP(sourceState, *Mappers::ProvinceMapper::Builder().Build(), theConfiguration);

	std::cout.rdbuf(coutBuffer);

	ASSERT_EQ(std::nullopt, theState.getVPLocation());
	ASSERT_EQ(log.str(), " [WARNING] Could not create VP for state 42\n");
}


TEST(HoI4World_States_StateTests, DebugVPsCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.setProvinceNumbers({12}).build();

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12}).Build(),
		 theConfiguration);

	ASSERT_EQ(std::set<int>{12}, theState.getDebugVPs());
}


TEST(HoI4World_States_StateTests, SecondaryDebugVPsCanBeAdded)
{
	const auto sourceState = *Vic2::State::Builder{}.setProvinceNumbers({12}).build();

	HoI4::State theState(sourceState, 42, "TAG");

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState,
		 *Mappers::ProvinceMapper::Builder().addVic2ToHoI4ProvinceMap(12, {12, 13}).Build(),
		 theConfiguration);

	const std::set<int> expectedVps{12, 13};
	ASSERT_EQ(expectedVps, theState.getSecondaryDebugVPs());
}


TEST(HoI4World_States_StateTests, DebugVpsAreOutput)
{
	const auto sourceState = *Vic2::State::Builder{}.setProvinceNumbers({12, 24}).setCapitalProvince(12).build();

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
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, true);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationDefaultsToMissing)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationCanBeAssigned)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);

	ASSERT_EQ(12, *theState.getMainNavalLocation());
}


TEST(HoI4World_States_StateTests, MainNavalBaseLocationGoesToLargestBase)
{
	const auto sourceState = *Vic2::State::Builder{}.build();
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);
	theState.addProvince(24);
	theState.addNavalBase(5, 24);

	ASSERT_EQ(24, *theState.getMainNavalLocation());
}