#include "V2World/Pops/PopBuilder.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Provinces_ProvinceBuilderTests, NumberMustBeSet)
{
	ASSERT_THROW(Vic2::Province::Builder{}.build(), std::runtime_error);
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, NumberCanBeSet)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_EQ(province->getNumber(), 42);
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, OwnerDefaultsToEmpty)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_TRUE(province->getOwner().empty());
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, OwnerCanBeSet)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).setOwner("TAG").build();
	ASSERT_EQ(province->getOwner(), "TAG");
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, ControllerDefaultsToEmpty)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_TRUE(province->getController().empty());
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, ControllerCanBeSet)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).setController("TAG").build();
	ASSERT_EQ(province->getController(), "TAG");
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, CoresDefaultsToEmpty)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_TRUE(province->getCores().empty());
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, CoresCanBeSet)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).setCores({"TAG"}).build();
	ASSERT_EQ(province->getCores(), std::set<std::string>{"TAG"});
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, PopsDefaultsToEmpty)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_TRUE(province->getPops().empty());
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, PopsCanBeSet)
{
	const auto province =
		 Vic2::Province::Builder{}.setNumber(42).setPops({*Vic2::Pop::Builder{}.setType("farmers").build()}).build();

	ASSERT_EQ(province->getPops().size(), 1);
	ASSERT_EQ(province->getPops()[0].getType(), "farmers");
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, NavalBaseLevelDefaultsToEmpty)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_EQ(province->getNavalBaseLevel(), 0);
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, NavalBaseLevelCanBeSet)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).setNavalBaseLevel(8).build();
	ASSERT_EQ(province->getNavalBaseLevel(), 8);
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, RailLevelDefaultsToEmpty)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).build();
	ASSERT_EQ(province->getRailLevel(), 0);
}


TEST(Vic2World_Provinces_ProvinceBuilderTests, RailBaseLevelCanBeSet)
{
	const auto province = Vic2::Province::Builder{}.setNumber(42).setRailLevel(8).build();
	ASSERT_EQ(province->getRailLevel(), 8);
}