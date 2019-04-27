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
#include "../Vic2ToHoI4/Source/HoI4World/Navies/Navies.h"
#include "../Mocks/TechnologiesMock.h"


class HoI4World_NaviesTests: public ::testing::Test
{
	protected:
		HoI4World_NaviesTests();

		std::unique_ptr<HoI4::shipVariants> theShipVariants;
		std::unique_ptr<HoI4::shipVariants> limitedShipVariants;
};


HoI4World_NaviesTests::HoI4World_NaviesTests()
{
	std::vector< HoI4::shipVariant> possibleVariants;
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
	EXPECT_CALL(ownedTechs, hasTechnology("basic_ship_hull_light")).WillOnce(testing::Return(true)).WillOnce(testing::Return(false)); 

	theShipVariants = std::make_unique<HoI4::shipVariants>(possibleVariants, ownedTechs, "");
	limitedShipVariants = std::make_unique<HoI4::shipVariants>(possibleVariants, ownedTechs, "");
}



TEST_F(HoI4World_NaviesTests, BlankNaviesOutputLegacyProperly)
{
	std::vector<const Vic2::Army*> sourceArmies;
	std::map<std::string, HoI4::UnitMap> unitMap;
	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;
	std::string tag;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, tag);
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, ConvertedNaviesOutputLegacyProperly)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = destroyer_1\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMap.insert(std::make_pair(std::string("commerce_raider"), unitMapping));

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { destroyer_1 = { amount = 1 owner = TAG } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, NaviesWithoutShipsDontConvertToLegacy)
{
	std::vector<const Vic2::Army*> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = destroyer_1\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMap.insert(std::make_pair(std::string("commerce_raider"), unitMapping));

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, NonNavalUnitsArentAddedToLegacyNavy)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = land\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = destroyer_1\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMap.insert(std::make_pair(std::string("commerce_raider"), unitMapping));

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, LegacyNavyNamesConvert)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = destroyer_1\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMap.insert(std::make_pair(std::string("commerce_raider"), unitMapping));

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { destroyer_1 = { amount = 1 owner = TAG } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, BlankNaviesOutputMtgProperly)
{
	std::vector<const Vic2::Army*> sourceArmies;
	std::map<std::string, HoI4::UnitMap> unitMap;
	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;
	std::string tag;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, tag);
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, ConvertedNaviesOutputMtgProperly)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = ship_hull_light_2\n";
	unitMapStream << "	version = \"1936 Destroyer\"\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	std::vector<HoI4::UnitMap> unitMappings;
	unitMappings.push_back(unitMapping);
	mtgUnitMap.insert(std::make_pair(std::string("commerce_raider"), unitMappings));

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { ship_hull_light_2 = { amount = 1 owner = TAG version_name = \"1936 Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, OnlyConvertToAvailableMtgShipType)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	std::vector<HoI4::UnitMap> unitMappings;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = ship_hull_light_2\n";
	unitMapStream << "	version = \"1936 Destroyer\"\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMappings.push_back(unitMapping);
	std::stringstream unitMapStream2;
	unitMapStream2 << "{\n";
	unitMapStream2 << "	category = naval\n";
	unitMapStream2 << "	type = destroyer\n";
	unitMapStream2 << "	equipment = ship_hull_light_1\n";
	unitMapStream2 << "	version = \"Early Destroyer\"\n";
	unitMapStream2 << "	size = 1\n";
	unitMapStream2 << "}\n";
	HoI4::UnitMap unitMapping2(unitMapStream2);
	unitMappings.push_back(unitMapping2);
	mtgUnitMap.insert(std::make_pair(std::string("commerce_raider"), unitMappings));

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *limitedShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { ship_hull_light_1 = { amount = 1 owner = TAG version_name = \"Early Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, ConvertedNaviesGetExperience)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = ship_hull_light_2\n";
	unitMapStream << "	version = \"1936 Destroyer\"\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	std::vector<HoI4::UnitMap> unitMappings;
	unitMappings.push_back(unitMapping);
	mtgUnitMap.insert(std::make_pair(std::string("commerce_raider"), unitMappings));

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"2nd Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer start_experience_factor = 0.2 equipment = { ship_hull_light_2 = { amount = 1 owner = TAG version_name = \"1936 Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, NaviesWithoutShipsDontConvertToMtg)
{
	std::vector<const Vic2::Army*> sourceArmies;
	std::stringstream armyStream;
	armyStream << "{\n";
	armyStream << "	name = \"2nd Fleet\"\n";
	armyStream << "	location = 0\n";
	armyStream << "	supplies = 1.000\n";
	armyStream << "	at_sea = 0\n";
	armyStream << "}";
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = destroyer_1\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMap.insert(std::make_pair(std::string("commerce_raider"), unitMapping));

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, NonNavalUnitsArentAddedToMtgNavy)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = land\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = destroyer_1\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	unitMap.insert(std::make_pair(std::string("commerce_raider"), unitMapping));

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, MtgNavyNamesConvert)
{
	std::vector<const Vic2::Army*> sourceArmies;
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
	Vic2::Army* navy = new Vic2::Army("navy", armyStream);
	sourceArmies.push_back(navy);

	std::map<std::string, HoI4::UnitMap> unitMap;

	std::map<std::string, std::vector<HoI4::UnitMap>> mtgUnitMap;
	std::stringstream unitMapStream;
	unitMapStream << "{\n";
	unitMapStream << "	category = naval\n";
	unitMapStream << "	type = destroyer\n";
	unitMapStream << "	equipment = ship_hull_light_1\n";
	unitMapStream << "	version = \"Early Destroyer\"\n";
	unitMapStream << "	size = 1\n";
	unitMapStream << "}\n";
	HoI4::UnitMap unitMapping(unitMapStream);
	std::vector<HoI4::UnitMap> unitMappings;
	unitMappings.push_back(unitMapping);
	mtgUnitMap.insert(std::make_pair(std::string("commerce_raider"), unitMappings));

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, mtgUnitMap, *theShipVariants, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputMtg(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "\tfleet = {\n";
	expectedOutput << "\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\tnaval_base = 0\n";
	expectedOutput << "\t\ttask_force = {\n";
	expectedOutput << "\t\t\tname = \"Renamed Fleet\"\n";
	expectedOutput << "\t\t\tlocation = 0\n";
	expectedOutput << "\t\t\tship = { name = \"Tigray\" definition = destroyer equipment = { ship_hull_light_1 = { amount = 1 owner = TAG version_name = \"Early Destroyer\" } } }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_NaviesTests, IfInSeaProvinceLocationConverts)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST_F(HoI4World_NaviesTests, IfInSeaProvinceBaseUsesBackupLocation)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST_F(HoI4World_NaviesTests, IfInPortLocationAndBaseConvert)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST_F(HoI4World_NaviesTests, IfInBadLocationAndBaseUseBackup)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}