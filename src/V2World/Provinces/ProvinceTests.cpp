#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Issues/Issues.h"
#include "src/V2World/Pops/Pop.h"
#include "src/V2World/Provinces/Province.h"
#include "src/V2World/Provinces/ProvinceBuilder.h"



using Vic2::Pop;
using Vic2::PopOptions;



TEST(Vic2World_ProvinceTests, getTotalPopulationDefaultsToZero)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).build();

	ASSERT_EQ(theProvince->getTotalPopulation(), 0);
}


TEST(Vic2World_ProvinceTests, getTotalPopulationReturnsTotalPopulation)
{
	const auto theProvince =
		 Vic2::Province::Builder()
			  .setNumber(42)
			  .setPops({Pop(PopOptions{.type = "serfs", .size = 1}), Pop(PopOptions{.type = "slaves", .size = 2})})
			  .build();

	ASSERT_EQ(theProvince->getTotalPopulation(), 3);
}


TEST(Vic2World_ProvinceTests, getPopulationDefaultsToZero)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).build();

	ASSERT_EQ(theProvince->getPopulation(), 0);
}


TEST(Vic2World_ProvinceTests, getPopulationWithNoTypeGivesTotalPopulation)
{
	const auto theProvince =
		 Vic2::Province::Builder()
			  .setNumber(42)
			  .setPops({Pop(PopOptions{.type = "serfs", .size = 1}), Pop(PopOptions{.type = "slaves", .size = 2})})
			  .build();

	ASSERT_EQ(theProvince->getPopulation(), 3);
}


TEST(Vic2World_ProvinceTests, getPopulationDiscriminatesBySpecifiedPopType)
{
	const auto theProvince =
		 Vic2::Province::Builder()
			  .setNumber(42)
			  .setPops({Pop(PopOptions{.type = "serfs", .size = 1}), Pop(PopOptions{.type = "slaves", .size = 2})})
			  .build();

	ASSERT_EQ(theProvince->getPopulation("slaves"), 2);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationDefaultsToZero)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation(), 0);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesTenPercentAtNoLiteracy)
{
	const auto theProvince =
		 Vic2::Province::Builder().setNumber(42).setPops({Pop(PopOptions{.type = "aristocrats", .size = 100})}).build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 10);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesOneHundredPercentAtFullLiteracy)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .size = 100, .literacy = 1.0})})
										  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 100);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationDiscriminatesByPopType)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .size = 100, .literacy = 1.0}),
												Pop(PopOptions{.type = "artisans", .size = 100, .literacy = 0.5})})
										  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 100);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesAllPopsWhenNoTypeSpecified)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .size = 100, .literacy = 1.0}),
												Pop(PopOptions{.type = "artisans", .size = 100, .literacy = 0.5})})
										  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation(), 155);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoPops)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).build();

	const std::set<std::string> cultures;
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoCulturesSpecified)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .culture = "culture", .size = 100})})
										  .build();

	const std::set<std::string> cultures;
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoCulturesMatch)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .culture = "culture", .size = 100})})
										  .build();

	std::set<std::string> cultures;
	cultures.insert("wrong_culture");
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsMatchedPercent)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .culture = "culture", .size = 100}),
												Pop(PopOptions{.type = "aristocrats", .culture = "culture2", .size = 100})})
										  .build();

	std::set<std::string> cultures;
	cultures.insert("culture");
	ASSERT_NEAR(theProvince->getPercentageWithCultures(cultures), 0.5, 0.0001);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesCanMapMultipleCultures)
{
	const auto theProvince = Vic2::Province::Builder()
										  .setNumber(42)
										  .setPops({Pop(PopOptions{.type = "aristocrats", .culture = "culture", .size = 100}),
												Pop(PopOptions{.type = "aristocrats", .culture = "another_culture", .size = 100})})
										  .build();

	std::set<std::string> cultures;
	cultures.insert("culture");
	cultures.insert("another_culture");
	ASSERT_NEAR(theProvince->getPercentageWithCultures(cultures), 1.0, 0.0001);
}


TEST(Vic2World_ProvinceTests, ownerCanBeChanged)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).setOwner("TAG").build();
	theProvince->setOwner("NEW");

	ASSERT_EQ(theProvince->getOwner(), "NEW");
}


TEST(Vic2World_ProvinceTests, coresCanBeAdded)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).build();
	theProvince->addCore("TAG");

	ASSERT_EQ(theProvince->getCores().size(), 1);
	ASSERT_TRUE(theProvince->getCores().contains("TAG"));
}


TEST(Vic2World_ProvinceTests, coresCanBeRemoved)
{
	const auto theProvince = Vic2::Province::Builder().setNumber(42).setCores({"TAG", "2ND"}).build();
	theProvince->removeCore("2ND");

	ASSERT_EQ(theProvince->getCores().size(), 1);
	ASSERT_TRUE(theProvince->getCores().contains("TAG"));
}