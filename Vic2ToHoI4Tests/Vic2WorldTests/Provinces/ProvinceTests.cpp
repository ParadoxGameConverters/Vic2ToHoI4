#include "../Vic2ToHoI4/Source/V2World/Issues/Issues.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/ProvinceFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_ProvinceTests: public testing::Test
{
  protected:
	Vic2World_ProvinceTests();

	Vic2::Pop::Factory popFactory;
	Vic2::Province::Factory provinceFactory;
};


Vic2World_ProvinceTests::Vic2World_ProvinceTests(): popFactory(Vic2::Issues({})), provinceFactory(popFactory)
{
}


TEST_F(Vic2World_ProvinceTests, getTotalPopulationDefaultsToZero)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getTotalPopulation(), 0);
}


TEST_F(Vic2World_ProvinceTests, getTotalPopulationReturnsTotalPopulation)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tserfs={\n";
	input << "\t\tsize=1";
	input << "\t}\n";
	input << "\tslaves={\n";
	input << "\t\tsize=2";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getTotalPopulation(), 3);
}


TEST_F(Vic2World_ProvinceTests, getPopulationDefaultsToZero)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPopulation(), 0);
}


TEST_F(Vic2World_ProvinceTests, getPopulationWithNoTypeGivesTotalPopulation)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tserfs={\n";
	input << "\t\tsize=1";
	input << "\t}\n";
	input << "\tslaves={\n";
	input << "\t\tsize=2";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPopulation(), 3);
}


TEST_F(Vic2World_ProvinceTests, getPopulationDiscriminatesBySpecifiedPopType)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tserfs={\n";
	input << "\t\tsize=1";
	input << "\t}\n";
	input << "\tslaves={\n";
	input << "\t\tsize=2";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPopulation("slaves"), 2);
}


TEST_F(Vic2World_ProvinceTests, getLiteracyWeightedPopulationDefaultsToZero)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation(), 0);
}


TEST_F(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesTenPercentAtNoLiteracy)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 10);
}


TEST_F(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesOneHundredPercentAtFullLiteracy)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tliteracy=1.0";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 100);
}


TEST_F(Vic2World_ProvinceTests, getLiteracyWeightedPopulationDiscriminatesByPopType)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tliteracy=1.0";
	input << "\t}\n";
	input << "\tartisans={\n";
	input << "\t\tsize=100";
	input << "\t\tliteracy=0.5";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation("aristocrats"), 100);
}


TEST_F(Vic2World_ProvinceTests, getLiteracyWeightedPopulationGivesAllPopsWhenNoTypeSpecified)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tliteracy=1.0";
	input << "\t}\n";
	input << "\tartisans={\n";
	input << "\t\tsize=100";
	input << "\t\tliteracy=0.5";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getLiteracyWeightedPopulation(), 155);
}


TEST_F(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	const std::set<std::string> cultures;
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST_F(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoCulturesSpecified)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tculture=religion";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	const std::set<std::string> cultures;
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST_F(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsZeroIfNoCulturesMatch)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tculture=religion";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	std::set<std::string> cultures;
	cultures.insert("wrong_culture");
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.0);
}


TEST_F(Vic2World_ProvinceTests, getPercentageWithCulturesReturnsMatchedPercent)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tculture=religion";
	input << "\t}\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tculture2=religion";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	std::set<std::string> cultures;
	cultures.insert("culture");
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 0.5);
}


TEST_F(Vic2World_ProvinceTests, getPercentageWithCulturesCanMapMultipleCultures)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tculture=religion";
	input << "\t}\n";
	input << "\taristocrats={\n";
	input << "\t\tsize=100";
	input << "\t\tanother_culture=religion";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	std::set<std::string> cultures;
	cultures.insert("culture");
	cultures.insert("another_culture");
	ASSERT_EQ(theProvince->getPercentageWithCultures(cultures), 1.0);
}


TEST_F(Vic2World_ProvinceTests, ownerCanBeChanged)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\towner=\"TAG\"";
	input << "}";

	auto theProvince = provinceFactory.getProvince(42, input);
	theProvince->setOwner("NEW");

	ASSERT_EQ(theProvince->getOwner(), "NEW");
}


TEST_F(Vic2World_ProvinceTests, coresCanBeAdded)
{
	std::stringstream input;
	const auto theProvince = provinceFactory.getProvince(42, input);
	theProvince->addCore("TAG");

	ASSERT_EQ(theProvince->getCores().size(), 1);
	ASSERT_EQ(theProvince->getCores().count("TAG"), 1);
}


TEST_F(Vic2World_ProvinceTests, coresCanBeRemoved)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tcore=\"TAG\"";
	input << "\tcore=\"2ND\"";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);
	theProvince->removeCore("2ND");

	ASSERT_EQ(theProvince->getCores().size(), 1);
	ASSERT_EQ(theProvince->getCores().count("TAG"), 1);
}