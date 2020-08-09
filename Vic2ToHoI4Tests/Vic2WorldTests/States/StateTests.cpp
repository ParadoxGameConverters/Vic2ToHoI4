#include "../../../Vic2ToHoI4/Source/V2World/Pops/PopFactory.h"
#include "../../../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "../../../Vic2ToHoI4/Source/V2World/Provinces/ProvinceBuilder.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/State.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateDefinitions.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_States_StateTests: public testing::Test
{
  protected:
	Vic2World_States_StateTests();

	Vic2::Pop::Factory popFactory;
};


Vic2World_States_StateTests::Vic2World_States_StateTests(): popFactory(Vic2::Issues({}))
{
}



TEST_F(Vic2World_States_StateTests, PopulationIsZeroWithNoProvinces)
{
	const Vic2::State state;

	ASSERT_EQ(0, state.getPopulation());
}


TEST_F(Vic2World_States_StateTests, PopulationComesFromAllProvinces)
{
	Vic2::State state;

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t}";
	const auto farmers = popFactory.getPop("farmers", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setPops(std::vector<Vic2::Pop>{*farmers}).build();
	state.addProvince(provinceOne);

	std::stringstream popInput2;
	popInput2 << "={\n";
	popInput2 << "\t\tsize=34\n";
	popInput2 << "\t}";
	const auto farmers2 = popFactory.getPop("farmers", popInput2);
	const std::shared_ptr<Vic2::Province> provinceTwo =
		 Vic2::Province::Builder{}.setNumber(2).setPops(std::vector<Vic2::Pop>{*farmers2}).build();
	state.addProvince(provinceTwo);

	ASSERT_EQ(46, state.getPopulation());
}


TEST_F(Vic2World_States_StateTests, RailLevelIsZeroWithNoProvinces)
{
	const Vic2::State state;

	ASSERT_EQ(0, state.getAverageRailLevel());
}


TEST_F(Vic2World_States_StateTests, RailLevelIsAverageOfProvinceRailLevels)
{
	Vic2::State state;

	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder{}.setNumber(1).setRailLevel(3).build();
	state.addProvince(provinceOne);

	const std::shared_ptr<Vic2::Province> provinceTwo = Vic2::Province::Builder{}.setNumber(2).setRailLevel(1).build();
	state.addProvince(provinceTwo);

	ASSERT_EQ(2, state.getAverageRailLevel());
}


TEST_F(Vic2World_States_StateTests, EmployedWorkersDefaultsToZero)
{
	Vic2::State state;
	state.determineEmployedWorkers();

	ASSERT_EQ(0, state.getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, CraftsmenAddToEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t}";
	const auto craftsmen = popFactory.getPop("craftsmen", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*craftsmen}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, CraftsmenLiteracyDoesNotAffectEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t\tliteracy = 1.00\n";
	popInput << "\t}";
	const auto craftsmen = popFactory.getPop("craftsmen", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*craftsmen}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, ClerksAddTwoToEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t}";
	const auto clerks = popFactory.getPop("clerks", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*clerks}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, ClerkLiteracyDoesNotAffectEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t\tliteracy = 1.00\n";
	popInput << "\t}";
	const auto clerks = popFactory.getPop("clerks", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*clerks}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, ArtisansAddHalfToEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t}";
	const auto artisans = popFactory.getPop("artisans", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*artisans}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, ArtisanLiteracyDoesNotAffectEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12\n";
	popInput << "\t\tliteracy = 1.00\n";
	popInput << "\t}";
	const auto artisans = popFactory.getPop("artisans", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*artisans}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, CapitalistsAddTwoToEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=10\n";
	popInput << "\t\tliteracy = 1.00\n";
	popInput << "\t}";
	const auto capitalists = popFactory.getPop("capitalists", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*capitalists}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(20, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, CapitalistLiteracyAffectsEmployedWorkers)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=10\n";
	popInput << "\t\tliteracy = 0.00\n";
	popInput << "\t}";
	const auto capitalists = popFactory.getPop("capitalists", popInput);
	const std::shared_ptr<Vic2::Province> provinceOne =
		 Vic2::Province::Builder{}.setNumber(1).setCores({"TAG"}).setPops(std::vector<Vic2::Pop>{*capitalists}).build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(2, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, CraftsmentAndClerksCappedByFactoryLevel)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream craftsmenInput;
	craftsmenInput << "={\n";
	craftsmenInput << "\t\tsize=10000\n";
	craftsmenInput << "\t}";
	const auto craftsmen = popFactory.getPop("craftsmen", craftsmenInput);
	std::stringstream clerksInput;
	clerksInput << "={\n";
	clerksInput << "\t\tsize=5000\n";
	clerksInput << "\t}";
	const auto clerks = popFactory.getPop("clerks", clerksInput);
	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder{}
																			  .setNumber(1)
																			  .setCores({"TAG"})
																			  .setPops(std::vector<Vic2::Pop>{*craftsmen, *clerks})
																			  .build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(13333, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, ArtisansNotCappedByFactoryLevel)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 0\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream artisansInput;
	artisansInput << "={\n";
	artisansInput << "\t\tsize=30000\n";
	artisansInput << "\t}";
	const auto artisans = popFactory.getPop("artisans", artisansInput);
	std::stringstream clerksInput;
	clerksInput << "={\n";
	clerksInput << "\t\tsize=20000\n";
	clerksInput << "\t}";
	const auto clerks = popFactory.getPop("clerks", clerksInput);
	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder{}
																			  .setNumber(1)
																			  .setCores({"TAG"})
																			  .setPops(std::vector<Vic2::Pop>{*artisans, *clerks})
																			  .build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(15000, state->getEmployedWorkers());
}


TEST_F(Vic2World_States_StateTests, CapitalistsNotCappedByFactoryLevel)
{
	const Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 0\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	std::stringstream capitalistsInput;
	capitalistsInput << "={\n";
	capitalistsInput << "\t\tsize=20000\n";
	capitalistsInput << "\t\tliteracy = 1.00\n";
	capitalistsInput << "\t}";
	const auto capitalists = popFactory.getPop("capitalists", capitalistsInput);
	std::stringstream clerksInput;
	clerksInput << "={\n";
	clerksInput << "\t\tsize=20000\n";
	clerksInput << "\t\tliteracy = 1.00\n";
	clerksInput << "\t}";
	const auto clerks = popFactory.getPop("clerks", clerksInput);
	const std::shared_ptr<Vic2::Province> provinceOne = Vic2::Province::Builder{}
																			  .setNumber(1)
																			  .setCores({"TAG"})
																			  .setPops(std::vector<Vic2::Pop>{*capitalists, *clerks})
																			  .build();
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(40000, state->getEmployedWorkers());
}