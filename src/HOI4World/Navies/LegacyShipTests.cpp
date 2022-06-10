#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Navies/LegacyShip.h"
#include "src/OutHoi4/Navies/OutLegacyShip.h"



TEST(HoI4World_Navies_LegacyShipTests, NameCanBeSet)
{
	HoI4::LegacyShip ship("theName", "", "", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"theName\" definition =  equipment = {  = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_LegacyShipTests, TypeCanBeSet)
{
	HoI4::LegacyShip ship("", "theType", "", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = theType equipment = {  = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_LegacyShipTests, EquipmentCanBeSet)
{
	HoI4::LegacyShip ship("", "", "theEquipment", "");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput
		 << "\t\t\tship = { name = \"\" definition =  equipment = { theEquipment = { amount = 1 owner =  } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_LegacyShipTests, OwnerCanBeSet)
{
	HoI4::LegacyShip ship("", "", "", "OWN");
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner = OWN } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_LegacyShipTests, CarrierGetsAirWings)
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


TEST(HoI4World_Navies_LegacyShipTests, AirWingsOwnerCanBeSet)
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