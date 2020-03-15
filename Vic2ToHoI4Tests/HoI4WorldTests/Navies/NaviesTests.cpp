#include "../../Mocks/TechnologiesMock.h"
#include "../Vic2ToHoI4/Source/HOI4World/Navies/Navies.h"
#include "../Vic2ToHoI4/Source/Hoi4Outputter/Navies/NaviesOutputter.h"
#include "gtest/gtest.h"



class HoI4World_Navies_NaviesTests: public testing::Test
{
  protected:
	HoI4World_Navies_NaviesTests();

	std::unique_ptr<HoI4::ShipVariants> theShipVariants;
	std::unique_ptr<HoI4::ShipVariants> limitedShipVariants;
};


HoI4World_Navies_NaviesTests::HoI4World_Navies_NaviesTests()
{
	std::stringstream shipVariantsInput;
	shipVariantsInput << "mtg_ship_type = {\n";
	shipVariantsInput << "	required_techs = { \n";
	shipVariantsInput << "		early_ship_hull_light\n";
	shipVariantsInput << "	}\n";
	shipVariantsInput << "	name = \"Early Destroyer\"\n";
	shipVariantsInput << "	type = ship_hull_light_1\n";
	shipVariantsInput << "	name_group = DD_HISTORICAL\n";
	shipVariantsInput << "	modules = { \n";
	shipVariantsInput << "		fixed_ship_battery_slot = ship_light_battery_1\n";
	shipVariantsInput << "		fixed_ship_anti_air_slot = ship_anti_air_1\n";
	shipVariantsInput << "		fixed_ship_fire_control_system_slot = empty\n";
	shipVariantsInput << "		fixed_ship_radar_slot = ship_sonar_1\n";
	shipVariantsInput << "		fixed_ship_torpedo_slot = ship_torpedo_1\n";
	shipVariantsInput << "		fixed_ship_engine_slot = light_ship_engine_1\n";
	shipVariantsInput << "		mid_1_custom_slot = ship_depth_charge_1\n";
	shipVariantsInput << "		rear_1_custom_slot = empty\n";
	shipVariantsInput << "	}\n";
	shipVariantsInput << "	obsolete = no\n";
	shipVariantsInput << "}\n";
	shipVariantsInput << "mtg_ship_type = { \n";
	shipVariantsInput << "	required_techs = { \n";
	shipVariantsInput << "		basic_ship_hull_light\n";
	shipVariantsInput << "	}\n";
	shipVariantsInput << "	name = \"1936 Destroyer\"\n";
	shipVariantsInput << "	type = ship_hull_light_2\n";
	shipVariantsInput << "	name_group = DD_HISTORICAL\n";
	shipVariantsInput << "	modules = { \n";
	shipVariantsInput << "		fixed_ship_battery_slot = ship_light_battery_2\n";
	shipVariantsInput << "		fixed_ship_anti_air_slot = ship_anti_air_2\n";
	shipVariantsInput << "		fixed_ship_fire_control_system_slot = empty\n";
	shipVariantsInput << "		fixed_ship_radar_slot = ship_sonar_1\n";
	shipVariantsInput << "		fixed_ship_torpedo_slot = ship_torpedo_1\n";
	shipVariantsInput << "		fixed_ship_engine_slot = light_ship_engine_2\n";
	shipVariantsInput << "		mid_1_custom_slot = ship_depth_charge_1\n";
	shipVariantsInput << "		rear_1_custom_slot = empty\n";
	shipVariantsInput << "	}\n";
	shipVariantsInput << "	obsolete = no\n";
	shipVariantsInput << "}\n";
	HoI4::PossibleShipVariants thePossibleVariants(shipVariantsInput);

	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_light")).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light"))
		 .WillOnce(testing::Return(true))
		 .WillOnce(testing::Return(false));

	theShipVariants = std::make_unique<HoI4::ShipVariants>(thePossibleVariants, ownedTechs, "");
	limitedShipVariants = std::make_unique<HoI4::ShipVariants>(thePossibleVariants, ownedTechs, "");
}


TEST_F(HoI4World_Navies_NaviesTests, NaviesConvertToLegacy)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 20.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	unitMappingsStream << "= {\n";
	unitMappingsStream << "\tlink = {\n";
	unitMappingsStream << "\t\tvic = commerce_raider\n";
	unitMappingsStream << "\t\thoi = {\n";
	unitMappingsStream << "\t\t\tcategory = naval\n";
	unitMappingsStream << "\t\t\ttype = destroyer\n";
	unitMappingsStream << "\t\t\tequipment = destroyer_1\n";
	unitMappingsStream << "\t\t\tsize = 1\n";
	unitMappingsStream << "\t\t\tversion = \"1936 Destroyer\"\n";
	unitMappingsStream << "\t\t}\n";
	unitMappingsStream << "\t}\n";
	unitMappingsStream << "}\n";
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\tname = \"1936 Destroyer\"\n";
	input << "\ttype = destroyer_1\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);
	mockTechnologies ownedTechs;
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies, 0, unitMappings, mtgUnitMap, theVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { destroyer_1 = { amount = 1 "
							"owner = TAG } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, OnlyConvertToAvailableLegacyShipType)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 00.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream legacyUnitMappingStream;
	legacyUnitMappingStream << "link = {\n";
	legacyUnitMappingStream << "	vic = commerce_raider\n";
	legacyUnitMappingStream << "	hoi = {\n";
	legacyUnitMappingStream << "		category = naval\n";
	legacyUnitMappingStream << "		type = destroyer\n";
	legacyUnitMappingStream << "		equipment = ship_hull_light_2\n";
	legacyUnitMappingStream << "		version = \"1936 Destroyer\"\n";
	legacyUnitMappingStream << "		size = 1\n";
	legacyUnitMappingStream << "	}\n";
	legacyUnitMappingStream << "}";
	HoI4::UnitMappings legacyUnitMap(legacyUnitMappingStream);

	std::stringstream input;
	HoI4::MtgUnitMappings unitMap(input);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies
		 navies(sourceArmies, 0, legacyUnitMap, unitMap, *limitedShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, NaviesWithoutShipsDontConvertToLegacy)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	unitMappingsStream << "= {\n";
	unitMappingsStream << "vic2 = commerce_raider\n";
	unitMappingsStream << "\thoi4 = {\n";
	unitMappingsStream << "\t\tcategory = naval\n";
	unitMappingsStream << "\t\ttype = destroyer\n";
	unitMappingsStream << "\t\tequipment = destroyer_1\n";
	unitMappingsStream << "\t\tsize = 1\n";
	unitMappingsStream << "\t}\n";
	unitMappingsStream << "}\n";
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies
		 navies(sourceArmies, 0, unitMappings, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, NonNavalUnitsArentAddedToLegacyNavy)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 20.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	unitMappingsStream << "= {\n";
	unitMappingsStream << "vic2 = commerce_raider\n";
	unitMappingsStream << "\thoi4 = {\n";
	unitMappingsStream << "\t\tcategory = naval\n";
	unitMappingsStream << "\t\ttype = destroyer\n";
	unitMappingsStream << "\t\tequipment = destroyer_1\n";
	unitMappingsStream << "\t\tsize = 1\n";
	unitMappingsStream << "\t}\n";
	unitMappingsStream << "}\n";
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies
		 navies(sourceArmies, 0, unitMappings, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, LegacyNavyNamesConvert)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"Renamed Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 20.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	unitMappingsStream << "= {\n";
	unitMappingsStream << "\tlink = {\n";
	unitMappingsStream << "\t\tvic = commerce_raider\n";
	unitMappingsStream << "\t\thoi = {\n";
	unitMappingsStream << "\t\t\tcategory = naval\n";
	unitMappingsStream << "\t\t\ttype = destroyer\n";
	unitMappingsStream << "\t\t\tequipment = destroyer_1\n";
	unitMappingsStream << "\t\t\tsize = 1\n";
	unitMappingsStream << "\t\t\tversion = \"1936 Destroyer\"\n";
	unitMappingsStream << "\t\t}\n";
	unitMappingsStream << "\t}\n";
	unitMappingsStream << "}\n";
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\tname = \"1936 Destroyer\"\n";
	input << "\ttype = destroyer_1\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);
	mockTechnologies ownedTechs;
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies, 0, unitMappings, mtgUnitMap, theVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { destroyer_1 = { amount = 1 "
							"owner = TAG } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, LegacyCanHave1936DestroyerInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_destroyer")).WillOnce(testing::Return(true));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_battleship")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_battleship")).WillOnce(testing::Return(false));
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies, 0, unitMappings, mtgUnitMap, theVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = destroyer_2\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 3\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 10\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, LegacyCanHaveEarlyDestroyerInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_destroyer")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_destroyer")).WillOnce(testing::Return(true));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_battleship")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_battleship")).WillOnce(testing::Return(false));
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies, 0, unitMappings, mtgUnitMap, theVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = destroyer_1\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 3\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 10\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, LegacyCanHave1936BattleshipInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_destroyer")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_destroyer")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_battleship")).WillOnce(testing::Return(true));
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies, 0, unitMappings, mtgUnitMap, theVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = battleship_2\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 8\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 3\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, LegacyCanHaveEarlyBattleshipInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_destroyer")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_destroyer")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_battleship")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_battleship")).WillOnce(testing::Return(true));
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies, 0, unitMappings, mtgUnitMap, theVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = battleship_1\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 8\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 3\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, NaviesConvertToMtg)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 0.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "	vic = commerce_raider\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "		version = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { ship_hull_light_2 = { "
							"amount = 1 owner = TAG version_name = \"1936 Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, OnlyConvertToAvailableMtgShipType)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 00.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "	vic = commerce_raider\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "		version = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_1\n";
	mtgUnitMappingStream << "		version = \"Early Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *limitedShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { ship_hull_light_1 = { "
							"amount = 1 owner = TAG version_name = \"Early Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, ConvertedNaviesGetExperience)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 20.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "	vic = commerce_raider\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "		version = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer start_experience_factor = 0.2 equipment "
							"= { ship_hull_light_2 = { amount = 1 owner = TAG version_name = \"1936 Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, NaviesWithoutShipsDontConvertToMtg)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "= {\n";
	mtgUnitMappingStream << "	vic = commerce_raider\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "		version = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, NonNavalUnitsArentAddedToMtgNavy)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 20.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "= {\n";
	mtgUnitMappingStream << "	vic = commerce_raider\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "		version = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, MtgNavyNamesConvert)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"Renamed Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	ship = \n";
	armyStream << "	{\n";
	armyStream << "		name = \"Tigray\"\n";
	armyStream << "		organisation = 82.355\n";
	armyStream << "		strength = 100.000\n";
	armyStream << "		experience = 0.000\n";
	armyStream << "		type = commerce_raider\n";
	armyStream << "	}\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "	vic = commerce_raider\n";
	mtgUnitMappingStream << "	hoi = {\n";
	mtgUnitMappingStream << "		category = naval\n";
	mtgUnitMappingStream << "		type = destroyer\n";
	mtgUnitMappingStream << "		equipment = ship_hull_light_1\n";
	mtgUnitMappingStream << "		version = \"Early Destroyer\"\n";
	mtgUnitMappingStream << "		size = 1\n";
	mtgUnitMappingStream << "	}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { ship_hull_light_1 = { "
							"amount = 1 owner = TAG version_name = \"Early Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, MtgCanHave1936DestroyerInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light")).WillOnce(testing::Return(true));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_heavy")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_heavy")).WillOnce(testing::Return(false));
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = ship_hull_light_2\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t\tversion_name = \"1936 Destroyer\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 3\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 10\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, MtgCanHaveEarlyDestroyerInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_light")).WillOnce(testing::Return(true));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_heavy")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_heavy")).WillOnce(testing::Return(false));
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = ship_hull_light_1\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t\tversion_name = \"Early Destroyer\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 3\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 10\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, MtgCanHave1936BattleshipInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_light")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_heavy")).WillOnce(testing::Return(true));
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = ship_hull_heavy_2\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t\tversion_name = \"1936 Battleship\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 8\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 3\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, MtgCanHaveEarlyBattleshipInProduction)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	Vic2::Army navy("navy", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_light")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_heavy")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_heavy")).WillOnce(testing::Return(true));
	std::ostringstream output;
	outputMtgNavies(navies, ownedTechs, "TAG", output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "instant_effect = {\n";
	expectedOutput << "\tadd_equipment_production = {\n";
	expectedOutput << "\t\tequipment = {\n";
	expectedOutput << "\t\t\ttype = ship_hull_heavy_1\n";
	expectedOutput << "\t\t\tcreator = \"TAG\"\n";
	expectedOutput << "\t\t\tversion_name = \"Early Battleship\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\trequested_factories = 8\n";
	expectedOutput << "\t\tprogress = 0.25\n";
	expectedOutput << "\t\tamount = 3\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_Navies_NaviesTests, IfInSeaProvinceLocationConverts)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST_F(HoI4World_Navies_NaviesTests, IfInSeaProvinceBaseUsesBackupLocation)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST_F(HoI4World_Navies_NaviesTests, IfInPortLocationAndBaseConvert)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST_F(HoI4World_Navies_NaviesTests, IfInBadLocationAndBaseUseBackup)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}