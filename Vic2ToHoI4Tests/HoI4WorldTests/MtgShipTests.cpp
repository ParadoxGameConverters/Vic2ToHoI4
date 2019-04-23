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
#include "../Vic2ToHoI4/Source/HoI4World/Navies/MtgShip.h"



TEST(HoI4World_MtgShipTests, BlankShipOutputsProperly)
{
	HoI4::MtgShip ship("", "", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner =  version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, NameCanBeSet)
{
	HoI4::MtgShip ship("theName", "", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"theName\" definition =  equipment = {  = { amount = 1 owner =  version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, TypeCanBeSet)
{
	HoI4::MtgShip ship("", "theType", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = theType equipment = {  = { amount = 1 owner =  version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, EquipmentCanBeSet)
{
	HoI4::MtgShip ship("", "", "theEquipment", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = { theEquipment = { amount = 1 owner =  version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, OwnerCanBeSet)
{
	HoI4::MtgShip ship("", "", "", "OWN", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner = OWN version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, VersionCanBeSet)
{
	HoI4::MtgShip ship("", "", "", "", "Ship Version", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner =  version_name = \"Ship Version\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, ExperienceCanBeSet)
{
	HoI4::MtgShip ship("", "", "", "", "", 0.5);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  start_experience_factor = 0.5 equipment = {  = { amount = 1 owner =  version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, CarrierGetsAirWings)
{
	HoI4::MtgShip ship("", "carrier", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = carrier equipment = {  = { amount = 1 owner =  version_name = \"\" } }\n";
	expectedOutput << "\t\t\t\tair_wings = {\n";
	expectedOutput << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"\" amount = 8 } # historical: 36\n";
	expectedOutput << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"\" amount = 14 } # historical: 15\n";
	expectedOutput << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"\" amount = 8 } # historical: 12\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_MtgShipTests, AirWingsOwnerCanBeSet)
{
	HoI4::MtgShip ship("", "carrier", "", "OWN", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = carrier equipment = {  = { amount = 1 owner = OWN version_name = \"\" } }\n";
	expectedOutput << "\t\t\t\tair_wings = {\n";
	expectedOutput << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"OWN\" amount = 8 } # historical: 36\n";
	expectedOutput << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"OWN\" amount = 14 } # historical: 15\n";
	expectedOutput << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"OWN\" amount = 8 } # historical: 12\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}