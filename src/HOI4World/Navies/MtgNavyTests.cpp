#include "src/HOI4World/Navies/MtgNavy.h"
#include "src/OutHoi4/Navies/OutMtgNavy.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Navies_MtgNavyTests, ZeroShipsByDefault)
{
	const HoI4::MtgNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	ASSERT_EQ(navy.getNumShips(), 0);
}


TEST(HoI4World_Navies_MtgNavyTests, ShipsAreCountedProperly)
{
	HoI4::MtgNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	HoI4::MtgShip ship1("", "", "", "", "", 0);
	HoI4::MtgShip ship2("", "", "", "", "", 0);
	navy.addShip(ship1);
	navy.addShip(ship2);

	ASSERT_EQ(navy.getNumShips(), 2);
}


TEST(HoI4World_Navies_MtgNavyTests, ZeroStrentghByDefault)
{
	const HoI4::MtgNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	ASSERT_NEAR(navy.getStrength(), 0.0, 0.00001);
}


TEST(HoI4World_Navies_MtgNavyTests, ShipsAddStrengthToNavy)
{
	HoI4::MtgNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	HoI4::MtgShip ship1("", "carrier", "", "", "", 0);
	HoI4::MtgShip ship2("", "battleship", "", "", "", 0);
	navy.addShip(ship1);
	navy.addShip(ship2);

	ASSERT_NEAR(navy.getStrength(), 1.5, 0.00001);
}


TEST(HoI4World_Navies_MtgNavyTests, NameCanBeSet)
{
	const HoI4::MtgNavy navy("theName", 0, 0);
	std::ostringstream output;
	output << navy;

	std::ostringstream expectedOutput;
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"theName\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"theName\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgNavyTests, LocationCanBeSet)
{
	const HoI4::MtgNavy navy("", 15, 0);
	std::ostringstream output;
	output << navy;

	std::ostringstream expectedOutput;
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"\"\n";
	expectedOutput << "\t\t\tlocation = 15\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgNavyTests, BaseCanBeSet)
{
	const HoI4::MtgNavy navy("", 0, 12);
	std::ostringstream output;
	output << navy;

	std::ostringstream expectedOutput;
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\tnaval_base = 12\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}