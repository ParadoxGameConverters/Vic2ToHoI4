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
#include "../Vic2ToHoI4/Source/HoI4World/Navies/LegacyShip.h"



TEST(HoI4World_LegacyShipTests, BlankShipOutputsProperly)
{
	HoI4::LegacyShip ship("", "", "", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_LegacyShipTests, NameCanBeSet)
{
	HoI4::LegacyShip ship("theName", "", "", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"theName\" definition =  equipment = {  = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_LegacyShipTests, TypeCanBeSet)
{
	HoI4::LegacyShip ship("", "theType", "", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = theType equipment = {  = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_LegacyShipTests, EquipmentCanBeSet)
{
	HoI4::LegacyShip ship("", "", "theEquipment", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = { theEquipment = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_LegacyShipTests, OwnerCanBeSet)
{
	HoI4::LegacyShip ship("", "", "", "OWN");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner = OWN } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_LegacyShipTests, CarrierGetsAirWings)
{
	HoI4::LegacyShip ship("", "carrier", "", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = carrier equipment = {  = { amount = 1 owner =  } }\n";
	expectedOutput << "\t\t\t\tair_wings = {\n";
	expectedOutput << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"\" amount = 8 } # historical: 36\n";
	expectedOutput << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"\" amount = 14 } # historical: 15\n";
	expectedOutput << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"\" amount = 8 } # historical: 12\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_LegacyShipTests, AirWingsOwnerCanBeSet)
{
	HoI4::LegacyShip ship("", "carrier", "", "OWN");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = carrier equipment = {  = { amount = 1 owner = OWN } }\n";
	expectedOutput << "\t\t\t\tair_wings = {\n";
	expectedOutput << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"OWN\" amount = 8 } # historical: 36\n";
	expectedOutput << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"OWN\" amount = 14 } # historical: 15\n";
	expectedOutput << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"OWN\" amount = 8 } # historical: 12\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}