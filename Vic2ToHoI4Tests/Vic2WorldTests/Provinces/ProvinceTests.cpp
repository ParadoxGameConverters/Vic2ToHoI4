#include "V2World/Issues/Issues.h"
#include "V2World/Pops/PopBuilder.h"
#include "V2World/Provinces/Province.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_ProvinceTests, getTotalPopulationDefaultsToZero)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).build();

	ASSERT_EQ(theProvince->getTotalPopulation(), 0);
}


TEST(Vic2World_ProvinceTests, getTotalPopulationReturnsTotalPopulation)
{
	const auto theProvince = Vic2::Province::Builder{}
										  .setNumber(42)
										  .setPops({*Vic2::Pop::Builder{}.setType("serfs").setSize(1).build(),
												*Vic2::Pop::Builder{}.setType("slaves").setSize(2).build()})
										  .build();

	ASSERT_EQ(theProvince->getTotalPopulation(), 3);
}


TEST(Vic2World_ProvinceTests, getPopulationDefaultsToZero)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).build();

	ASSERT_EQ(theProvince->getPopulation(), 0);
}


TEST(Vic2World_ProvinceTests, getPopulationWithNoTypeGivesTotalPopulation)
{
	const auto theProvince = Vic2::Province::Builder{}
										  .setNumber(42)
										  .setPops({*Vic2::Pop::Builder{}.setType("serfs").setSize(1).build(),
												*Vic2::Pop::Builder{}.setType("slaves").setSize(2).build()})
										  .build();

	ASSERT_EQ(theProvince->getPopulation(), 3);
}


TEST(Vic2World_ProvinceTests, getPopulationDiscriminatesBySpecifiedPopType)
{
	const auto theProvince = Vic2::Province::Builder{}
										  .setNumber(42)
										  .setPops({*Vic2::Pop::Builder{}.setType("serfs").setSize(1).build(),
												*Vic2::Pop::Builder{}.setType("slaves").setSize(2).build()})
										  .build();

	ASSERT_EQ(theProvince->getPopulation("slaves"), 2);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationDefaultsToZero)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation(), 0);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesTenPercentAtNoLiteracy)
{
	const auto theProvince = Vic2::Province::Builder{}
										  .setNumber(42)
										  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).build()})
										  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 10);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesOneHundredPercentAtFullLiteracy)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setLiteracy(1.0).build()})
			  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 100);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationDiscriminatesByPopType)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setLiteracy(1.0).build(),
					*Vic2::Pop::Builder{}.setType("artisans").setSize(100).setLiteracy(0.5).build()})
			  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 100);
}


TEST(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesAllPopsWhenNoTypeSpecified)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setLiteracy(1.0).build(),
					*Vic2::Pop::Builder{}.setType("artisans").setSize(100).setLiteracy(0.5).build()})
			  .build();

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation(), 155);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoPops)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).build();

	const std::set<std::string> cultures;
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoCulturesSpecified)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setCulture("culture").build()})
			  .build();

	const std::set<std::string> cultures;
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoCulturesMatch)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setCulture("culture").build()})
			  .build();

	std::set<std::string> cultures;
	cultures.insert("wrong_culture");
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsMatchedPercent)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setCulture("culture").build(),
					*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setCulture("culture2").build()})
			  .build();

	std::set<std::string> cultures;
	cultures.insert("culture");
	ASSERT_NEAR(theProvince->getPercentageWithCultures(cultures), 0.5, 0.0001);
}


TEST(Vic2World_ProvinceTests, getPercentageWithCulturesCanMapMultipleCultures)
{
	const auto theProvince =
		 Vic2::Province::Builder{}
			  .setNumber(42)
			  .setPops({*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setCulture("culture").build(),
					*Vic2::Pop::Builder{}.setType("aristocrats").setSize(100).setCulture("another_culture").build()})
			  .build();

	std::set<std::string> cultures;
	cultures.insert("culture");
	cultures.insert("another_culture");
	ASSERT_NEAR(theProvince->getPercentageWithCultures(cultures), 1.0, 0.0001);
}


TEST(Vic2World_ProvinceTests, ownerCanBeChanged)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).setOwner("TAG").build();
	theProvince->setOwner("NEW");

	ASSERT_EQ(theProvince->getOwner(), "NEW");
}


TEST(Vic2World_ProvinceTests, coresCanBeAdded)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).build();
	theProvince->addCore("TAG");

	ASSERT_EQ(theProvince->getCores().size(), 1);
	ASSERT_TRUE(theProvince->getCores().contains("TAG"));
}


TEST(Vic2World_ProvinceTests, coresCanBeRemoved)
{
	const auto theProvince = Vic2::Province::Builder{}.setNumber(42).setCores({"TAG", "2ND"}).build();
	theProvince->removeCore("2ND");

	ASSERT_EQ(theProvince->getCores().size(), 1);
	ASSERT_TRUE(theProvince->getCores().contains("TAG"));
}