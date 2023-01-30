#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Pops/Pop.h"
#include "src/V2World/Provinces/Province.h"
#include "src/V2World/Provinces/ProvinceBuilder.h"
#include "src/V2World/States/State.h"
#include "src/V2World/States/StateBuilder.h"
#include "src/V2World/States/StateDefinitionsBuilder.h"



using Vic2::Pop;
using Vic2::PopOptions;



TEST(Vic2World_States_StateTests, ProvincesDefaultToEmpty)
{
	const Vic2::State state;

	ASSERT_EQ(0, state.getProvinces().size());
}


TEST(Vic2World_States_StateTests, ProvincesCanBeAdded)
{
	Vic2::State state;
	state.addProvince(Vic2::Province::Builder().setNumber(1).build());
	state.addProvince(Vic2::Province::Builder().setNumber(2).build());

	ASSERT_EQ(2, state.getProvinces().size());
}


TEST(Vic2World_States_StateTests, OwnerDefaultsToEmpty)
{
	const Vic2::State state;

	ASSERT_TRUE(state.getOwner().empty());
}


TEST(Vic2World_States_StateTests, OwnerCanBeSet)
{
	Vic2::State state;
	state.setOwner("TAG");

	ASSERT_EQ("TAG", state.getOwner());
}


TEST(Vic2World_States_StateTests, LanguageCategoryDefaultsToEmpty)
{
	const Vic2::State state;

	ASSERT_TRUE(state.getLanguageCategory().empty());
}


TEST(Vic2World_States_StateTests, LanguageCategoryCanBeSet)
{
	Vic2::State state;
	state.setLanguageCategory("msnc");

	ASSERT_EQ("msnc", state.getLanguageCategory());
}


TEST(Vic2World_States_StateTests, PopulationIsZeroWithNoProvinces)
{
	const Vic2::State state;

	ASSERT_EQ(0, state.getPopulation());
}


TEST(Vic2World_States_StateTests, PopulationComesFromAllProvinces)
{
	Vic2::State state;
	state.addProvince(Vic2::Province::Builder()
								 .setNumber(1)
								 .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 12})})
								 .build());
	state.addProvince(Vic2::Province::Builder()
								 .setNumber(2)
								 .setPops(std::vector{Pop(PopOptions{.type = "farmers", .size = 34})})
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
	state.addProvince(Vic2::Province::Builder().setNumber(1).setRailLevel(3).build());
	state.addProvince(Vic2::Province::Builder().setNumber(2).setRailLevel(1).build());

	ASSERT_EQ(2, state.getAverageRailLevel());
}


TEST(Vic2World_States_StateTests, UpperClassLocationReturnedFromAristocrats)
{
	Vic2::State state;
	state.addProvince(
		 Vic2::Province::Builder().setNumber(1).setPops({Pop(PopOptions{.type = "farmers", .size = 12})}).build());
	state.addProvince(
		 Vic2::Province::Builder().setNumber(2).setPops({Pop(PopOptions{.type = "aristocrats", .size = 1})}).build());

	ASSERT_EQ(2, state.getUpperClassLocation());
}


TEST(Vic2World_States_StateTests, UpperClassLocationReturnedFromBureaucrats)
{
	Vic2::State state;
	state.addProvince(
		 Vic2::Province::Builder().setNumber(1).setPops({Pop(PopOptions{.type = "farmers", .size = 12})}).build());
	state.addProvince(
		 Vic2::Province::Builder().setNumber(2).setPops({Pop(PopOptions{.type = "bureaucrats", .size = 1})}).build());

	ASSERT_EQ(2, state.getUpperClassLocation());
}


TEST(Vic2World_States_StateTests, UpperClassLocationReturnedFromCapitalists)
{
	Vic2::State state;
	state.addProvince(
		 Vic2::Province::Builder().setNumber(1).setPops({Pop(PopOptions{.type = "farmers", .size = 12})}).build());
	state.addProvince(
		 Vic2::Province::Builder().setNumber(2).setPops({Pop(PopOptions{.type = "capitalists", .size = 1})}).build());

	ASSERT_EQ(2, state.getUpperClassLocation());
}


TEST(Vic2World_States_StateTests, UpperClassLocationReturnesNulloptIfNoUpperClasses)
{
	Vic2::State state;
	state.addProvince(
		 Vic2::Province::Builder().setNumber(1).setPops({Pop(PopOptions{.type = "farmers", .size = 12})}).build());
	state.addProvince(
		 Vic2::Province::Builder().setNumber(2).setPops({Pop(PopOptions{.type = "farmers", .size = 1})}).build());

	ASSERT_EQ(std::nullopt, state.getUpperClassLocation());
}


TEST(Vic2World_States_StateTests, ProvincesAreOrderedByPopulation)
{
	Vic2::State state;
	state.addProvince(
		 Vic2::Province::Builder().setNumber(1).setPops({Pop(PopOptions{.type = "farmers", .size = 22})}).build());
	state.addProvince(
		 Vic2::Province::Builder().setNumber(2).setPops({Pop(PopOptions{.type = "farmers", .size = 11})}).build());
	state.addProvince(
		 Vic2::Province::Builder().setNumber(3).setPops({Pop(PopOptions{.type = "farmers", .size = 33})}).build());

	const auto expectedProvinces = std::vector<int>{3, 1, 2};
	ASSERT_EQ(expectedProvinces, state.getProvincesOrderedByPopulation());
}


TEST(Vic2World_States_StateTests, ForeignControlledProvincesAreReturned)
{
	Vic2::State state;
	state.addProvince(Vic2::Province::Builder().setNumber(1).setOwner("OWN").setController("ONE").build());
	state.addProvince(Vic2::Province::Builder().setNumber(2).setOwner("OWN").setController("TWO").build());
	state.addProvince(Vic2::Province::Builder().setNumber(3).setOwner("OWN").setController("REB").build());

	const auto expectedProvinces = std::vector<std::pair<int, std::string>>{{1, "ONE"}, {2, "TWO"}, {3, "REB"}};
	EXPECT_THAT(state.getForeignControlledProvinces(), ::testing::WhenSorted(expectedProvinces));
}


TEST(Vic2World_States_StateTests, NavalBasesAreReturned)
{
	Vic2::State state;
	state.addProvince(Vic2::Province::Builder().setNumber(1).setNavalBaseLevel(2).build());
	state.addProvince(Vic2::Province::Builder().setNumber(2).setNavalBaseLevel(4).build());
	state.addProvince(Vic2::Province::Builder().setNumber(4).setNavalBaseLevel(8).build());

	const auto expectedProvinces = std::map<int, int>{{1, 2}, {2, 4}, {4, 8}};
	ASSERT_EQ(expectedProvinces, state.getNavalBases());
}


TEST(Vic2World_States_StateTests, EmployedWorkersDefaultsToZero)
{
	Vic2::State state;
	state.determineEmployedWorkers();

	ASSERT_EQ(0, state.getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmenAddToEmployedWorkers)
{
	auto state = Vic2::State::Builder()
						  .setOwner("TAG")
						  .setProvinces({Vic2::Province::Builder()
													.setNumber(1)
													.setCores({"TAG"})
													.setPops(std::vector{Pop(PopOptions{.type = "craftsmen", .size = 12})})
													.build()})
						  .setFactoryLevel(1)
						  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmenLiteracyDoesNotAffectEmployedWorkers)
{
	auto state =
		 Vic2::State::Builder()
			  .setOwner("TAG")
			  .setProvinces({Vic2::Province::Builder()
										.setNumber(1)
										.setCores({"TAG"})
										.setPops(std::vector{Pop(PopOptions{.type = "craftsmen", .size = 12, .literacy = 1.0})})
										.build()})
			  .setFactoryLevel(1)
			  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(12, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ClerksAddTwoToEmployedWorkers)
{
	auto state = Vic2::State::Builder()
						  .setOwner("TAG")
						  .setProvinces({Vic2::Province::Builder()
													.setNumber(1)
													.setCores({"TAG"})
													.setPops(std::vector{Pop(PopOptions{.type = "clerks", .size = 12})})
													.build()})
						  .setFactoryLevel(1)
						  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ClerkLiteracyDoesNotAffectEmployedWorkers)
{
	auto state =
		 Vic2::State::Builder()
			  .setOwner("TAG")
			  .setProvinces({Vic2::Province::Builder()
										.setNumber(1)
										.setCores({"TAG"})
										.setPops(std::vector{Pop(PopOptions{.type = "clerks", .size = 12, .literacy = 1.0})})
										.build()})
			  .setFactoryLevel(1)
			  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(24, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisansAddHalfToEmployedWorkers)
{
	auto state = Vic2::State::Builder()
						  .setOwner("TAG")
						  .setProvinces({Vic2::Province::Builder()
													.setNumber(1)
													.setCores({"TAG"})
													.setPops(std::vector{Pop(PopOptions{.type = "artisans", .size = 12})})
													.build()})
						  .setFactoryLevel(1)
						  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisanLiteracyDoesNotAffectEmployedWorkers)
{
	auto state =
		 Vic2::State::Builder()
			  .setOwner("TAG")
			  .setProvinces({Vic2::Province::Builder()
										.setNumber(1)
										.setCores({"TAG"})
										.setPops(std::vector{Pop(PopOptions{.type = "artisans", .size = 12, .literacy = 1.0})})
										.build()})
			  .setFactoryLevel(1)
			  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(6, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistsAddTwoToEmployedWorkers)
{
	auto state =
		 Vic2::State::Builder()
			  .setOwner("TAG")
			  .setProvinces({Vic2::Province::Builder()
										.setNumber(1)
										.setCores({"TAG"})
										.setPops(std::vector{Pop(PopOptions{.type = "capitalists", .size = 10, .literacy = 1.0})})
										.build()})
			  .setFactoryLevel(1)
			  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(20, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistLiteracyAffectsEmployedWorkers)
{
	auto state =
		 Vic2::State::Builder()
			  .setOwner("TAG")
			  .setProvinces({Vic2::Province::Builder()
										.setNumber(1)
										.setCores({"TAG"})
										.setPops(std::vector{Pop(PopOptions{.type = "capitalists", .size = 10, .literacy = 0.0})})
										.build()})
			  .setFactoryLevel(1)
			  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(2, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CraftsmentAndClerksCappedByFactoryLevel)
{
	auto state = Vic2::State::Builder()
						  .setOwner("TAG")
						  .setProvinces({Vic2::Province::Builder()
													.setNumber(1)
													.setCores({"TAG"})
													.setPops(std::vector{Pop(PopOptions{.type = "craftsmen", .size = 10'000}),
														 Pop(PopOptions{.type = "clerks", .size = 5'000})})
													.build()})
						  .setFactoryLevel(1)
						  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(13333, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, ArtisansNotCappedByFactoryLevel)
{
	auto state = Vic2::State::Builder()
						  .setOwner("TAG")
						  .setProvinces({Vic2::Province::Builder()
													.setNumber(1)
													.setCores({"TAG"})
													.setPops(std::vector{Pop(PopOptions{.type = "artisans", .size = 30'000}),
														 Pop(PopOptions{.type = "clerks", .size = 20'000})})
													.build()})
						  .setFactoryLevel(0)
						  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(15000, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, CapitalistsNotCappedByFactoryLevel)
{
	auto state =
		 Vic2::State::Builder()
			  .setOwner("TAG")
			  .setProvinces(
					{Vic2::Province::Builder()
							  .setNumber(1)
							  .setCores({"TAG"})
							  .setPops(std::vector{Pop(PopOptions{.type = "capitalists", .size = 20'000, .literacy = 1.0}),
									Pop(PopOptions{.type = "clerks", .size = 20'000, .literacy = 1.0})})
							  .build()})
			  .setFactoryLevel(0)
			  .build();
	state->determineEmployedWorkers();

	ASSERT_EQ(40000, state->getEmployedWorkers());
}


TEST(Vic2World_States_StateTests, EatingStateAbsorbsProvinces)
{
	Vic2::State state;
	const auto state2 = Vic2::State::Builder()
									.setProvinceNumbers({1, 2, 3})
									.setProvinces({Vic2::Province::Builder().setNumber(1).build(),
										 Vic2::Province::Builder().setNumber(2).build(),
										 Vic2::Province::Builder().setNumber(3).build()})
									.build();

	state.eatState(*state2, Vic2::StateDefinitions());

	ASSERT_THAT(state.getProvinceNumbers(), testing::ElementsAre(1, 2, 3));
	std::set<int> provinceNumbers;
	for (const auto& province: state.getProvinces())
	{
		provinceNumbers.insert(province->getNumber());
	}
	ASSERT_THAT(provinceNumbers, testing::ElementsAre(1, 2, 3));
}


TEST(Vic2World_States_StateTests, EatingStateCanMakePartialStatesWhole)
{
	Vic2::State state;
	const auto state2 = Vic2::State::Builder().setProvinceNumbers({1, 2, 3}).build();

	state.eatState(*state2,
		 *Vic2::StateDefinitions::Builder().setStateMap({{1, {1, 2, 3}}, {2, {1, 2, 3}}, {3, {1, 2, 3}}}).build());

	ASSERT_FALSE(state.isPartialState());
}


TEST(Vic2World_States_StateTests, EatingStateCanLeavePartialStatesPartial)
{
	Vic2::State state;
	const auto state2 = Vic2::State::Builder().setProvinceNumbers({1, 2, 3}).build();

	state.eatState(*state2,
		 *Vic2::StateDefinitions::Builder()
				.setStateMap({{1, {1, 2, 3, 4}}, {2, {1, 2, 3, 4}}, {3, {1, 2, 3, 4}}, {4, {1, 2, 3, 4}}})
				.build());

	ASSERT_TRUE(state.isPartialState());
}


TEST(Vic2World_States_StateTests, EatingStateAbsorbsWorkers)
{
	auto state = Vic2::State::Builder()
						  .setProvinceNumbers({1})
						  .setProvinces({Vic2::Province::Builder()
													.setOwner("TAG")
													.setNumber(1)
													.setCores({"TAG"})
													.setPops(std::vector{Pop(PopOptions{.type = "craftsmen", .size = 12})})
													.build()})
						  .setFactoryLevel(1)
						  .build();
	const auto state2 = Vic2::State::Builder()
									.setProvinceNumbers({2})
									.setProvinces({Vic2::Province::Builder()
															 .setOwner("TAG")
															 .setNumber(2)
															 .setCores({"TAG"})
															 .setPops(std::vector{Pop(PopOptions{.type = "craftsmen", .size = 12})})
															 .build()})
									.setFactoryLevel(2)
									.build();

	state->eatState(*state2, Vic2::StateDefinitions());

	ASSERT_EQ(24, state->getEmployedWorkers());
}