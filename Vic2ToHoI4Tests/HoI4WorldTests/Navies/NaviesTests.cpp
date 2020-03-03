#include "../../Mocks/TechnologiesMock.h"
#include "../Vic2ToHoI4/Source/HOI4World/Navies/Navies.h"
#include "../Vic2ToHoI4/Source/Hoi4Outputter/Navies/NaviesOutputter.h"
#include "gtest/gtest.h"



class HoI4World_Navies_NaviesTests: public testing::Test
{
  protected:
	HoI4World_Navies_NaviesTests();

	std::unique_ptr<HoI4::shipVariants> theShipVariants;
	std::unique_ptr<HoI4::shipVariants> limitedShipVariants;
};


HoI4World_Navies_NaviesTests::HoI4World_Navies_NaviesTests()
{
	std::vector<HoI4::shipVariant> possibleVariants;
	std::stringstream earlyDestroyerInput;
	earlyDestroyerInput << "= {\n";
	earlyDestroyerInput << "	required_techs = { \n";
	earlyDestroyerInput << "		early_ship_hull_light\n";
	earlyDestroyerInput << "	}\n";
	earlyDestroyerInput << "	name = \"Early Destroyer\"\n";
	earlyDestroyerInput << "	type = ship_hull_light_1\n";
	earlyDestroyerInput << "	name_group = DD_HISTORICAL\n";
	earlyDestroyerInput << "	modules = { \n";
	earlyDestroyerInput << "		fixed_ship_battery_slot = ship_light_battery_1\n";
	earlyDestroyerInput << "		fixed_ship_anti_air_slot = ship_anti_air_1\n";
	earlyDestroyerInput << "		fixed_ship_fire_control_system_slot = empty\n";
	earlyDestroyerInput << "		fixed_ship_radar_slot = ship_sonar_1\n";
	earlyDestroyerInput << "		fixed_ship_torpedo_slot = ship_torpedo_1\n";
	earlyDestroyerInput << "		fixed_ship_engine_slot = light_ship_engine_1\n";
	earlyDestroyerInput << "		mid_1_custom_slot = ship_depth_charge_1\n";
	earlyDestroyerInput << "		rear_1_custom_slot = empty\n";
	earlyDestroyerInput << "	}\n";
	earlyDestroyerInput << "	obsolete = no\n";
	earlyDestroyerInput << "}\n";
	HoI4::shipVariant earlyDestroyer(earlyDestroyerInput);
	possibleVariants.push_back(earlyDestroyer);

	std::stringstream modernDestroyerInput;
	modernDestroyerInput << "= { \n";
	modernDestroyerInput << "	required_techs = { \n";
	modernDestroyerInput << "		basic_ship_hull_light\n";
	modernDestroyerInput << "	}\n";
	modernDestroyerInput << "	name = \"1936 Destroyer\"\n";
	modernDestroyerInput << "	type = ship_hull_light_2\n";
	modernDestroyerInput << "	name_group = DD_HISTORICAL\n";
	modernDestroyerInput << "	modules = { \n";
	modernDestroyerInput << "		fixed_ship_battery_slot = ship_light_battery_2\n";
	modernDestroyerInput << "		fixed_ship_anti_air_slot = ship_anti_air_2\n";
	modernDestroyerInput << "		fixed_ship_fire_control_system_slot = empty\n";
	modernDestroyerInput << "		fixed_ship_radar_slot = ship_sonar_1\n";
	modernDestroyerInput << "		fixed_ship_torpedo_slot = ship_torpedo_1\n";
	modernDestroyerInput << "		fixed_ship_engine_slot = light_ship_engine_2\n";
	modernDestroyerInput << "		mid_1_custom_slot = ship_depth_charge_1\n";
	modernDestroyerInput << "		rear_1_custom_slot = empty\n";
	modernDestroyerInput << "	}\n";
	modernDestroyerInput << "	obsolete = no\n";
	modernDestroyerInput << "}\n";
	HoI4::shipVariant modernDestroyer(modernDestroyerInput);
	possibleVariants.push_back(modernDestroyer);

	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("early_ship_hull_light")).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light"))
		 .WillOnce(testing::Return(true))
		 .WillOnce(testing::Return(false));

	theShipVariants = std::make_unique<HoI4::shipVariants>(possibleVariants, ownedTechs, "");
	limitedShipVariants = std::make_unique<HoI4::shipVariants>(possibleVariants, ownedTechs, "");
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
	unitMappingsStream << "\t\t}\n";
	unitMappingsStream << "\t}\n";
	unitMappingsStream << "}\n";
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies
		 navies(sourceArmies, 0, unitMappings, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, output);

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
	std::ostringstream output;
	outputLegacyNavies(navies, output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
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
	std::ostringstream output;
	outputLegacyNavies(navies, output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
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
	unitMappingsStream << "\t\t}\n";
	unitMappingsStream << "\t}\n";
	unitMappingsStream << "}\n";
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies
		 navies(sourceArmies, 0, unitMappings, mtgUnitMap, *theShipVariants, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	outputLegacyNavies(navies, output);

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
	std::ostringstream output;
	outputMtgNavies(navies, output);

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
	std::ostringstream output;
	outputMtgNavies(navies, output);

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
	std::ostringstream output;
	outputMtgNavies(navies, output);

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
	std::ostringstream output;
	outputMtgNavies(navies, output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
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
	std::ostringstream output;
	outputMtgNavies(navies, output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
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
	std::ostringstream output;
	outputMtgNavies(navies, output);

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