#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/Navies/LegacyNavy.h"
#include "../Vic2ToHoI4/Source/Hoi4Outputter/Navies/LegacyNavyOutputter.h"



TEST(HoI4World_Navies_LegacyNavyTests, BlankNavyOutputsProperly)
{
	const HoI4::LegacyNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	std::ostringstream expectedOutput;
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_LegacyNavyTests, ZeroShipsByDefault)
{
	const HoI4::LegacyNavy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	ASSERT_EQ(navy.getNumShips(), 0);
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

	ASSERT_EQ(navy.getNumShips(), 2);
}


TEST(HoI4World_Navies_LegacyNavyTests, ShipsAreOutputProperly)
{
	HoI4::LegacyNavy navy("", 0, 0);

	HoI4::LegacyShip ship1("ship1", "type1", "equip1", "OWN");
	HoI4::LegacyShip ship2("ship2", "type2", "equip2", "PWN");
	navy.addShip(ship1);
	navy.addShip(ship2);

	std::ostringstream output;
	output << navy;

	std::ostringstream expectedOutput;
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput <<
		"\t\t\tship = { name = \"ship1\" definition = type1 equipment = { equip1 = { amount = 1 owner = OWN } } }\n";
	expectedOutput <<
		"\t\t\tship = { name = \"ship2\" definition = type2 equipment = { equip2 = { amount = 1 owner = PWN } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
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