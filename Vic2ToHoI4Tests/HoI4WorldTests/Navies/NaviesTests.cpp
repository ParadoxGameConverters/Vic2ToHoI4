#include "HOI4World/Navies/Navies.h"
#include "HOI4World/TechnologiesBuilder.h"
#include "Mappers/Provinces/ProvinceMapperBuilder.h"
#include "Maps/ProvinceDefinitions.h"
#include "OutHoi4/Navies/OutNavies.h"
#include "V2World/Military/ArmyFactory.h"
#include "gtest/gtest.h"



class HoI4World_Navies_NaviesTests: public testing::Test
{
  protected:
	HoI4World_Navies_NaviesTests();

	std::unique_ptr<HoI4::ShipVariants> theShipVariants;
	std::unique_ptr<HoI4::ShipVariants> limitedShipVariants;

	HoI4::ProvinceDefinitions provinceDefinitions;
	Mappers::ProvinceMapper provinceMapper;
};


HoI4World_Navies_NaviesTests::HoI4World_Navies_NaviesTests(): provinceDefinitions({}, {}, {})
{
	std::stringstream shipVariantsInput;
	shipVariantsInput << "mtg_ship_type = {\n";
	shipVariantsInput << "\trequired_techs = { \n";
	shipVariantsInput << "\t\tearly_ship_hull_light\n";
	shipVariantsInput << "\t}\n";
	shipVariantsInput << "\tname = \"Early Destroyer\"\n";
	shipVariantsInput << "\ttype = ship_hull_light_1\n";
	shipVariantsInput << "\tname_group = DD_HISTORICAL\n";
	shipVariantsInput << "\tmodules = { \n";
	shipVariantsInput << "\t\tfixed_ship_battery_slot = ship_light_battery_1\n";
	shipVariantsInput << "\t\tfixed_ship_anti_air_slot = ship_anti_air_1\n";
	shipVariantsInput << "\t\tfixed_ship_fire_control_system_slot = empty\n";
	shipVariantsInput << "\t\tfixed_ship_radar_slot = ship_sonar_1\n";
	shipVariantsInput << "\t\tfixed_ship_torpedo_slot = ship_torpedo_1\n";
	shipVariantsInput << "\t\tfixed_ship_engine_slot = light_ship_engine_1\n";
	shipVariantsInput << "\t\tmid_1_custom_slot = ship_depth_charge_1\n";
	shipVariantsInput << "\t\trear_1_custom_slot = empty\n";
	shipVariantsInput << "\t}\n";
	shipVariantsInput << "\tobsolete = no\n";
	shipVariantsInput << "}\n";
	shipVariantsInput << "mtg_ship_type = { \n";
	shipVariantsInput << "\trequired_techs = { \n";
	shipVariantsInput << "\t\tbasic_ship_hull_light\n";
	shipVariantsInput << "\t}\n";
	shipVariantsInput << "\tname = \"1936 Destroyer\"\n";
	shipVariantsInput << "\ttype = ship_hull_light_2\n";
	shipVariantsInput << "\tname_group = DD_HISTORICAL\n";
	shipVariantsInput << "\tmodules = { \n";
	shipVariantsInput << "\t\tfixed_ship_battery_slot = ship_light_battery_2\n";
	shipVariantsInput << "\t\tfixed_ship_anti_air_slot = ship_anti_air_2\n";
	shipVariantsInput << "\t\tfixed_ship_fire_control_system_slot = empty\n";
	shipVariantsInput << "\t\tfixed_ship_radar_slot = ship_sonar_1\n";
	shipVariantsInput << "\t\tfixed_ship_torpedo_slot = ship_torpedo_1\n";
	shipVariantsInput << "\t\tfixed_ship_engine_slot = light_ship_engine_2\n";
	shipVariantsInput << "\t\tmid_1_custom_slot = ship_depth_charge_1\n";
	shipVariantsInput << "\t\trear_1_custom_slot = empty\n";
	shipVariantsInput << "\t}\n";
	shipVariantsInput << "\tobsolete = no\n";
	shipVariantsInput << "}\n";
	HoI4::PossibleShipVariants thePossibleVariants(shipVariantsInput);

	theShipVariants = std::make_unique<HoI4::ShipVariants>(thePossibleVariants,
		 *HoI4::technologies::Builder()
				.addTechnology("early_ship_hull_light")
				.addTechnology("basic_ship_hull_light")
				.Build(),
		 "");
	limitedShipVariants = std::make_unique<HoI4::ShipVariants>(thePossibleVariants,
		 *HoI4::technologies::Builder().addTechnology("early_ship_hull_light").Build(),
		 "");

	provinceMapper = *Mappers::ProvinceMapper::Builder().Build();
}


TEST_F(HoI4World_Navies_NaviesTests, NaviesConvertToLegacy)
{
	std::vector<Vic2::Army> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 20.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
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

	const auto ownedTechs = *HoI4::technologies::Builder().Build();
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 theVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 00.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream legacyUnitMappingStream;
	legacyUnitMappingStream << "link = {\n";
	legacyUnitMappingStream << "\tvic = commerce_raider\n";
	legacyUnitMappingStream << "\thoi = {\n";
	legacyUnitMappingStream << "\t\tcategory = naval\n";
	legacyUnitMappingStream << "\t\ttype = destroyer\n";
	legacyUnitMappingStream << "\t\tequipment = ship_hull_light_2\n";
	legacyUnitMappingStream << "\t\tversion = \"1936 Destroyer\"\n";
	legacyUnitMappingStream << "\t\tsize = 1\n";
	legacyUnitMappingStream << "\t}\n";
	legacyUnitMappingStream << "}";
	HoI4::UnitMappings legacyUnitMap(legacyUnitMappingStream);

	std::stringstream input;
	HoI4::MtgUnitMappings unitMap(input);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 legacyUnitMap,
		 unitMap,
		 *limitedShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
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

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputLegacyNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 20.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
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

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputLegacyNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"Renamed Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 20.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
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
	const auto ownedTechs = *HoI4::technologies::Builder().Build();
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 theVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	const auto ownedTechs = *HoI4::technologies::Builder().addTechnology("basic_destroyer").Build();
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 theVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	const auto ownedTechs = *HoI4::technologies::Builder().addTechnology("early_destroyer").Build();
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 theVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	const auto ownedTechs = *HoI4::technologies::Builder().addTechnology("basic_battleship").Build();
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 theVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream unitMappingsStream;
	HoI4::UnitMappings unitMappings(unitMappingsStream);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);
	const auto ownedTechs = *HoI4::technologies::Builder().addTechnology("early_battleship").Build();
	HoI4::ShipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMappings,
		 mtgUnitMap,
		 theVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 0.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "\tvic = commerce_raider\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "\t\tversion = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 00.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "\tvic = commerce_raider\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "\t\tversion = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_1\n";
	mtgUnitMappingStream << "\t\tversion = \"Early Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *limitedShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 20.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "\tvic = commerce_raider\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "\t\tversion = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "= {\n";
	mtgUnitMappingStream << "\tvic = commerce_raider\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "\t\tversion = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"2nd Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 20.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "= {\n";
	mtgUnitMappingStream << "\tvic = commerce_raider\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_2\n";
	mtgUnitMappingStream << "\t\tversion = \"1936 Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	armyStream << "\tname = \"Renamed Fleet\"\n";
	armyStream << "\tlocation = 0\n";
	armyStream << "\tsupplies = 1.000\n";
	armyStream << "\tship = \n";
	armyStream << "\t{\n";
	armyStream << "\t\tname = \"Tigray\"\n";
	armyStream << "\t\torganisation = 82.355\n";
	armyStream << "\t\tstrength = 100.000\n";
	armyStream << "\t\texperience = 0.000\n";
	armyStream << "\t\ttype = commerce_raider\n";
	armyStream << "\t}\n";
	armyStream << "\tat_sea = 0\n";
	armyStream << "}";
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	mtgUnitMappingStream << "link = {\n";
	mtgUnitMappingStream << "\tvic = commerce_raider\n";
	mtgUnitMappingStream << "\thoi = {\n";
	mtgUnitMappingStream << "\t\tcategory = naval\n";
	mtgUnitMappingStream << "\t\ttype = destroyer\n";
	mtgUnitMappingStream << "\t\tequipment = ship_hull_light_1\n";
	mtgUnitMappingStream << "\t\tversion = \"Early Destroyer\"\n";
	mtgUnitMappingStream << "\t\tsize = 1\n";
	mtgUnitMappingStream << "\t}\n";
	mtgUnitMappingStream << "}";
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies, *HoI4::technologies::Builder().Build(), "TAG", output);

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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies,
		 *HoI4::technologies::Builder().addTechnology("basic_ship_hull_light").Build(),
		 "TAG",
		 output);

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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies,
		 *HoI4::technologies::Builder().addTechnology("early_ship_hull_light").Build(),
		 "TAG",
		 output);

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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies,
		 *HoI4::technologies::Builder().addTechnology("basic_ship_hull_heavy").Build(),
		 "TAG",
		 output);

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
	Vic2::Army::Factory armyFactory;
	auto navy = *armyFactory.getArmy("", armyStream);
	sourceArmies.push_back(navy);

	std::stringstream input;
	HoI4::UnitMappings unitMap(input);

	std::stringstream mtgUnitMappingStream;
	HoI4::MtgUnitMappings mtgUnitMap(mtgUnitMappingStream);

	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State> states;

	HoI4::Navies navies(sourceArmies,
		 0,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 states,
		 "TAG",
		 provinceDefinitions,
		 provinceMapper);
	std::ostringstream output;
	outputMtgNavies(navies,
		 *HoI4::technologies::Builder().addTechnology("early_ship_hull_heavy").Build(),
		 "TAG",
		 output);

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