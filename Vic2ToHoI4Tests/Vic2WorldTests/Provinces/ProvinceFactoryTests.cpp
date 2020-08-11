#include "../Vic2ToHoI4/Source/V2World/Issues/Issues.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/ProvinceFactory.h"
#include "gtest/gtest.h"
#include <sstream>



class Vic2World_ProvinceFactoryTests: public testing::Test
{
  protected:
	Vic2World_ProvinceFactoryTests();

	Vic2::Pop::Factory popFactory;
	Vic2::Province::Factory provinceFactory;
};


Vic2World_ProvinceFactoryTests::Vic2World_ProvinceFactoryTests():
	 popFactory(Vic2::Issues({})), provinceFactory(popFactory)
{
}


TEST_F(Vic2World_ProvinceFactoryTests, numberCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getNumber(), 42);
}


TEST_F(Vic2World_ProvinceFactoryTests, ownerDefaultsToBlank)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getOwner(), "");
}


TEST_F(Vic2World_ProvinceFactoryTests, ownerCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\towner=\"TAG\"";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getOwner(), "TAG");
}


TEST_F(Vic2World_ProvinceFactoryTests, controllerDefaultsToBlank)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getController(), "");
}


TEST_F(Vic2World_ProvinceFactoryTests, controllerCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tcontroller=\"TAG\"";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getController(), "TAG");
}


TEST_F(Vic2World_ProvinceFactoryTests, coresDefaultToEmpty)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getCores().size(), 0);
}


TEST_F(Vic2World_ProvinceFactoryTests, coresCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tcore=\"TAG\"";
	input << "\tcore=\"2ND\"";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getCores().size(), 2);
	ASSERT_EQ(theProvince->getCores().count("TAG"), 1);
	ASSERT_EQ(theProvince->getCores().count("2ND"), 1);
}


TEST_F(Vic2World_ProvinceFactoryTests, popsDefaultToEmpty)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 0);
}


TEST_F(Vic2World_ProvinceFactoryTests, aristocratsCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\taristocrats={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "aristocrats");
}


TEST_F(Vic2World_ProvinceFactoryTests, artisansCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tartisans={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "artisans");
}


TEST_F(Vic2World_ProvinceFactoryTests, bureaucratsCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tbureaucrats={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "bureaucrats");
}


TEST_F(Vic2World_ProvinceFactoryTests, capitalistsCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tcapitalists={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "capitalists");
}


TEST_F(Vic2World_ProvinceFactoryTests, clergymenCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tclergymen={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "clergymen");
}


TEST_F(Vic2World_ProvinceFactoryTests, craftsmenCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tcraftsmen={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "craftsmen");
}


TEST_F(Vic2World_ProvinceFactoryTests, clerksCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tclerks={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "clerks");
}


TEST_F(Vic2World_ProvinceFactoryTests, farmersCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tfarmers={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "farmers");
}


TEST_F(Vic2World_ProvinceFactoryTests, soldiersCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tsoldiers={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "soldiers");
}


TEST_F(Vic2World_ProvinceFactoryTests, officersCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tofficers={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "officers");
}


TEST_F(Vic2World_ProvinceFactoryTests, labourersCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tlabourers={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "labourers");
}


TEST_F(Vic2World_ProvinceFactoryTests, slavesCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tslaves={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "slaves");
}


TEST_F(Vic2World_ProvinceFactoryTests, serfsCanBeAddedToPops)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tserfs={\n";
	input << "\t}\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getPops().size(), 1);
	ASSERT_EQ(theProvince->getPops()[0].getType(), "serfs");
}


TEST_F(Vic2World_ProvinceFactoryTests, navalBaseLevelDefaultsToZero)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getNavalBaseLevel(), 0);
}


TEST_F(Vic2World_ProvinceFactoryTests, navalBaseLevelCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tnaval_base =\n";
	input << "\t{\n";
	input << "  6.000 6.000 }\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getNavalBaseLevel(), 6);
}


TEST_F(Vic2World_ProvinceFactoryTests, railLevelDefaultsToZero)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getRailLevel(), 0);
}


TEST_F(Vic2World_ProvinceFactoryTests, railLevelCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\trailroad =\n";
	input << "\t{\n";
	input << "  5.000 5.000 }\n";
	input << "}";

	const auto theProvince = provinceFactory.getProvince(42, input);

	ASSERT_EQ(theProvince->getRailLevel(), 5);
}