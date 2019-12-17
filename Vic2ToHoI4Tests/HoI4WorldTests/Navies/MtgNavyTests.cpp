#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/Navies/MtgNavy.h"
#include "../Vic2ToHoI4/Source/Hoi4Outputter/Navies/MtgNavyOutputter.h"



TEST(HoI4World_Navies_MtgNavyTests, BlankNavyOutputsProperly)
{
	const HoI4::MtgNavy navy("", 0, 0);
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


TEST(HoI4World_Navies_MtgNavyTests, ShipsAreOutputProperly)
{
	HoI4::MtgNavy navy("", 0, 0);

	HoI4::MtgShip ship1("ship1", "type1", "equip1", "OWN", "version1", 0.0);
	HoI4::MtgShip ship2("ship2", "type2", "equip2", "PWN", "version2", 0.5);
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
		"\t\t\tship = { name = \"ship1\" definition = type1 equipment = { equip1 = { amount = 1 owner = OWN version_name = \"version1\" } } }\n";
	expectedOutput <<
		"\t\t\tship = { name = \"ship2\" definition = type2 start_experience_factor = 0.5 equipment = { equip2 = { amount = 1 owner = PWN version_name = \"version2\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
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