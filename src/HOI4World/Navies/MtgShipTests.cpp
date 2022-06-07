#include "src/HOI4World/Navies/MtgShip.h"
#include "src/OutHoi4/Navies/OutMtgShip.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Navies_MtgShipTests, NameCanBeSet)
{
	HoI4::MtgShip ship("theName", "", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"theName\" definition =  equipment = {  = { amount = 1 owner =  "
							"version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, TypeCanBeSet)
{
	HoI4::MtgShip ship("", "theType", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = theType equipment = {  = { amount = 1 owner =  "
							"version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, EquipmentCanBeSet)
{
	HoI4::MtgShip ship("", "", "theEquipment", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = { theEquipment = { amount = 1 owner =  "
							"version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, OwnerCanBeSet)
{
	HoI4::MtgShip ship("", "", "", "OWN", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner = OWN version_name "
							"= \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, VersionCanBeSet)
{
	HoI4::MtgShip ship("", "", "", "", "Ship Version", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  equipment = {  = { amount = 1 owner =  version_name = "
							"\"Ship Version\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, ExperienceCanBeSet)
{
	HoI4::MtgShip ship("", "", "", "", "", 0.5);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition =  start_experience_factor = 0.5 equipment = {  = { amount "
							"= 1 owner =  version_name = \"\" } } }\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, CarrierGetsAirWings)
{
	HoI4::MtgShip ship("", "carrier", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = carrier equipment = {  = { amount = 1 owner =  "
							"version_name = \"\" } }\n";
	expectedOutput << "\t\t\t\tair_wings = {\n";
	expectedOutput << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"\" amount = 8 } # historical: 36\n";
	expectedOutput << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"\" amount = 14 } # historical: 15\n";
	expectedOutput << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"\" amount = 8 } # historical: 12\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, AirWingsOwnerCanBeSet)
{
	HoI4::MtgShip ship("", "carrier", "", "OWN", "", 0.0);
	std::ostringstream output;
	output << ship;

	std::ostringstream expectedOutput;
	expectedOutput << "\t\t\tship = { name = \"\" definition = carrier equipment = {  = { amount = 1 owner = OWN "
							"version_name = \"\" } }\n";
	expectedOutput << "\t\t\t\tair_wings = {\n";
	expectedOutput << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"OWN\" amount = 8 } # historical: 36\n";
	expectedOutput << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"OWN\" amount = 14 } # historical: 15\n";
	expectedOutput << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"OWN\" amount = 8 } # historical: 12\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Navies_MtgShipTests, StrengthIsPointFiveForCarriers)
{
	const HoI4::MtgShip ship("", "carrier", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	ASSERT_NEAR(0.5, ship.getStrength(), 0.00001);
}


TEST(HoI4World_Navies_MtgShipTests, StrengthIsOneForBattleships)
{
	const HoI4::MtgShip ship("", "battleship", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	ASSERT_NEAR(1.0, ship.getStrength(), 0.00001);
}


TEST(HoI4World_Navies_MtgShipTests, StrengthIsPointEightForBattlecruisers)
{
	const HoI4::MtgShip ship("", "battle_cruiser", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	ASSERT_NEAR(0.8, ship.getStrength(), 0.00001);
}


TEST(HoI4World_Navies_MtgShipTests, StrengthIsPointFiveForHeavyCruisers)
{
	const HoI4::MtgShip ship("", "heavy_cruiser", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	ASSERT_NEAR(0.5, ship.getStrength(), 0.00001);
}


TEST(HoI4World_Navies_MtgShipTests, StrengthIsZeroForOthers)
{
	const HoI4::MtgShip ship("", "", "", "", "", 0.0);
	std::ostringstream output;
	output << ship;

	ASSERT_NEAR(0.0, ship.getStrength(), 0.00001);
}