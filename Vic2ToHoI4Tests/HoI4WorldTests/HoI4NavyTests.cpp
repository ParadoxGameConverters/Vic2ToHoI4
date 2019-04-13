/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HoI4World/HoI4Navy.h"



TEST(HoI4World_NavyTests, BlankNavyOutputsProperly)
{
	HoI4::Navy navy("", 0, 0);
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


TEST(HoI4World_NavyTests, ZeroShipsByDefault)
{
	HoI4::Navy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	ASSERT_EQ(navy.getNumShips(), 0);
}


TEST(HoI4World_NavyTests, ShipsAreCountedProperly)
{
	HoI4::Navy navy("", 0, 0);
	std::ostringstream output;
	output << navy;

	HoI4::Ship ship1("", "", "", "");
	HoI4::Ship ship2("", "", "", "");
	navy.addShip(ship1);
	navy.addShip(ship2);

	ASSERT_EQ(navy.getNumShips(), 2);
}


TEST(HoI4World_NavyTests, ShipsAreOutputProperly)
{
	HoI4::Navy navy("", 0, 0);

	HoI4::Ship ship1("ship1", "type1", "equip1", "OWN");
	HoI4::Ship ship2("ship2", "type2", "equip2", "PWN");
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
	expectedOutput << "\t\t\tship = { name = \"ship1\" definition = type1 equipment = { equip1 = { amount = 1 owner = OWN } } }\n";
	expectedOutput << "\t\t\tship = { name = \"ship2\" definition = type2 equipment = { equip2 = { amount = 1 owner = PWN } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_NavyTests, NameCanBeSet)
{
	HoI4::Navy navy("theName", 0, 0);
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


TEST(HoI4World_NavyTests, LocationCanBeSet)
{
	HoI4::Navy navy("", 15, 0);
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


TEST(HoI4World_NavyTests, BaseCanBeSet)
{
	HoI4::Navy navy("", 0, 12);
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