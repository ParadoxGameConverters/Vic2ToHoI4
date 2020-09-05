#include "../../../Vic2ToHoI4/Source/V2World/Pops/PopBuilder.h"
#include "../../../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "../../../Vic2ToHoI4/Source/V2World/Provinces/ProvinceBuilder.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/State.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateDefinitionsBuilder.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_States_StateTests, PopulationIsZeroWithNoProvinces)
{
	const Vic2::State state;

	ASSERT_EQ(0, state.getPopulation());
}


TEST(Vic2World_States_StateTests, PopulationComesFromAllProvinces)
{
	Vic2::State state;
	state.addProvince(Vic2::Province::Builder{}
								 .setNumber(1)
								 .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("farmers").setSize(12).build()})
								 .build());
	state.addProvince(Vic2::Province::Builder{}
								 .setNumber(2)
								 .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("farmers").setSize(34).build()})
								 .build());

	ASSERT_EQ(46, state.getPopulation());
}


TEST(Vic2World_States_StateTests, RailLevelIsZeroWithNoProvinces)
{
	const Vic2::State state;

	ASSERT_EQ(0, state.getAverageRailLevel());
}


TEST(Vic2World_States_StateTests, RailLevelIsAverageOfProvinceRailLevels)
{
	Vic2::State state;

	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder{}.setNumber(1).setRailLevel(3).build();
	state.addProvince(provinceOne);

	const std::shared_ptr<Vic2::Province> provinceTwo = Vic2::Province::Builder{}.setNumber(2).setRailLevel(1).build();
	state.addProvince(provinceTwo);

	ASSERT_EQ(2, state.getAverageRailLevel());
}


TEST(Vic2World_States_StateTests, EmployedWorkersDefaultsToZero)
{
	Vic2::State state;
	state.determineEmployedWorkers();

	ASSERT_EQ(0, state.getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmenAddToEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(
		 Vic2::Province::Builder{}
			  .setNumber(1)
			  .setCores({"TAG"})
			  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("craftsmen").setSize(12).build()})
			  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmenLiteracyDoesNotAffectEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{
										*Vic2::Pop::Builder{}.setType("craftsmen").setSize(12).setLiteracy(1.0).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ClerksAddTwoToEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("clerks").setSize(12).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ClerkLiteracyDoesNotAffectEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{
										*Vic2::Pop::Builder{}.setType("clerks").setSize(12).setLiteracy(1.0).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisansAddHalfToEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(
		 Vic2::Province::Builder{}
			  .setNumber(1)
			  .setCores({"TAG"})
			  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("artisans").setSize(12).build()})
			  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisanLiteracyDoesNotAffectEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{
										*Vic2::Pop::Builder{}.setType("artisans").setSize(12).setLiteracy(1.0).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistsAddTwoToEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{
										*Vic2::Pop::Builder{}.setType("capitalists").setSize(10).setLiteracy(1.0).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(20, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistLiteracyAffectsEmployedWorkers)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{
										*Vic2::Pop::Builder{}.setType("capitalists").setSize(10).setLiteracy(0.0).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(2, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmentAndClerksCappedByFactoryLevel)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(
		 Vic2::Province::Builder{}
			  .setNumber(1)
			  .setCores({"TAG"})
			  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("craftsmen").setSize(10000).build(),
					*Vic2::Pop::Builder{}.setType("clerks").setSize(5000).build()})
			  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(13333, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisansNotCappedByFactoryLevel)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 0\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(
		 Vic2::Province::Builder{}
			  .setNumber(1)
			  .setCores({"TAG"})
			  .setPops(std::vector<Vic2::Pop>{*Vic2::Pop::Builder{}.setType("artisans").setSize(30000).build(),
					*Vic2::Pop::Builder{}.setType("clerks").setSize(20000).build()})
			  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(15000, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistsNotCappedByFactoryLevel)
{
	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 0\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", *Vic2::StateDefinitions::Builder{}.build());
	state->setOwner("TAG");
	state->addProvince(Vic2::Province::Builder{}
								  .setNumber(1)
								  .setCores({"TAG"})
								  .setPops(std::vector<Vic2::Pop>{
										*Vic2::Pop::Builder{}.setType("capitalists").setSize(20000).setLiteracy(1.0).build(),
										*Vic2::Pop::Builder{}.setType("clerks").setSize(20000).setLiteracy(1.0).build()})
								  .build());
	state->determineEmployedWorkers();

	ASSERT_EQ(40000, state->getEmployedWorkers());
}