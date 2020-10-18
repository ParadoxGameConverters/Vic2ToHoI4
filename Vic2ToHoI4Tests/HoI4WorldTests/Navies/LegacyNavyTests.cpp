#include "HOI4World/Navies/LegacyNavy.h"
#include "OutHoi4/Navies/OutLegacyNavy.h"
#include "gtest/gtest.h"



TEST(HoI4World_Navies_LegacyNavyTests, ZeroShipsByDefault)
{
	const HoI4::LegacyNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	ASSERT_EQ(0, navy.getNumShips());
}


TEST(HoI4World_Navies_LegacyNavyTests, ShipsAreCountedProperly)
{
	HoI4::LegacyNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	HoI4::LegacyShip ship1("", "", "", "");
	HoI4::LegacyShip ship2("", "", "", "");
	navy.addShip(ship1);
	navy.addShip(ship2);

	ASSERT_EQ(2, navy.getNumShips());
}


TEST(HoI4World_Navies_LegacyNavyTests, NameCanBeSet)
{
	const HoI4::LegacyNavy navy("theName", 0, 0);
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


TEST(HoI4World_Navies_LegacyNavyTests, LocationCanBeSet)
{
	const HoI4::LegacyNavy navy("", 15, 0);
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


TEST(HoI4World_Navies_LegacyNavyTests, BaseCanBeSet)
{
	const HoI4::LegacyNavy navy("", 0, 12);
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