#include "../../../Vic2ToHoI4/Source/V2World/Pops/PopFactory.h"
#include "../../../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/State.h"
#include "../../../Vic2ToHoI4/Source/V2World/States/StateDefinitions.h"
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

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tfarmers = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state.addProvince(provinceOne);

	std::stringstream provinceTwoInput;
	provinceTwoInput << "= {\n";
	provinceTwoInput << "\tfarmers = {\n";
	provinceTwoInput << "\t\tsize = 34\n";
	provinceTwoInput << "\t}\n";
	provinceTwoInput << "}\n";
	const auto provinceTwo = std::make_shared<Vic2::Province>("2", provinceTwoInput, popFactory);
	state.addProvince(provinceTwo);

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

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\trailroad = {\n";
	provinceOneInput << "\t\t3 = 3\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state.addProvince(provinceOne);

	std::stringstream provinceTwoInput;
	provinceTwoInput << "= {\n";
	provinceTwoInput << "\trailroad = {\n";
	provinceTwoInput << "\t\t1 = 1\n";
	provinceTwoInput << "\t}\n";
	provinceTwoInput << "}\n";
	const auto provinceTwo = std::make_shared<Vic2::Province>("2", provinceTwoInput, popFactory);
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
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tcraftsmen = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmenLiteracyDoesNotAffectEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tcraftsmen = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ClerksAddTwoToEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tclerks = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ClerkLiteracyDoesNotAffectEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tclerks = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisansAddHalfToEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tartisans = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisanLiteracyDoesNotAffectEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tartisans = {\n";
	provinceOneInput << "\t\tsize = 12\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistsAddTwoToEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tcapitalists = {\n";
	provinceOneInput << "\t\tsize = 10\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(20, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistLiteracyAffectsEmployedWorkers)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tcapitalists = {\n";
	provinceOneInput << "\t\tsize = 10\n";
	provinceOneInput << "\t\tliteracy = 0.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(2, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmentAndClerksCappedByFactoryLevel)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 1\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tcraftsmen = {\n";
	provinceOneInput << "\t\tsize = 10000\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "\tclerks = {\n";
	provinceOneInput << "\t\tsize = 5000\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(13333, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisansNotCappedByFactoryLevel)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 0\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tartisans = {\n";
	provinceOneInput << "\t\tsize = 30000\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "\tclerks = {\n";
	provinceOneInput << "\t\tsize = 20000\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(15000, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistsNotCappedByFactoryLevel)
{
	Vic2::StateDefinitions stateDefinitions{{}, {}, {}};

	std::stringstream stateInput;
	stateInput << "= {\n";
	stateInput << "\tstate_buildings = {\n";
	stateInput << "\t\tlevel = 0\n";
	stateInput << "\t}";
	stateInput << "}";
	auto state = Vic2::State::Factory{}.getState(stateInput, "TAG", stateDefinitions);
	state->setOwner("TAG");

	Vic2::Issues issues({});
	Vic2::Pop::Factory popFactory(issues);

	std::stringstream provinceOneInput;
	provinceOneInput << "= {\n";
	provinceOneInput << "\tcore = TAG\n";
	provinceOneInput << "\tcapitalists = {\n";
	provinceOneInput << "\t\tsize = 20000\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "\tclerks = {\n";
	provinceOneInput << "\t\tsize = 20000\n";
	provinceOneInput << "\t\tliteracy = 1.00\n";
	provinceOneInput << "\t}\n";
	provinceOneInput << "}\n";
	const auto provinceOne = std::make_shared<Vic2::Province>("1", provinceOneInput, popFactory);
	state->addProvince(provinceOne);

	state->determineEmployedWorkers();

	ASSERT_EQ(40000, state->getEmployedWorkers());
}