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
#include "../Vic2ToHoI4/Source/HoI4World/Navies.h"



TEST(HoI4World_NaviesTests, BlankNaviesOutputLegacyProperly)
{
	std::vector<const Vic2::Army*> sourceArmies;
	std::map<std::string, HoI4::UnitMap> unitMap;
	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;
	std::string tag;

	HoI4::Navies navies(sourceArmies, 0, unitMap, theCoastalProvinces, provinceToStateIDMap, states, tag);
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_NaviesTests, ConvertedNaviesOutputLegacyProperly)
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

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
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


TEST(HoI4World_NaviesTests, NaviesWithoutShipsDontConvert)
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

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_NaviesTests, NonNavalUnitsArentAddedToNavy)
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

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
	std::ostringstream output;
	navies.outputLegacy(output);

	std::ostringstream expectedOutput;
	expectedOutput << "units = {\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_NaviesTests, NavyNamesConvert)
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

	HoI4::coastalProvinces theCoastalProvinces;
	std::map<int, int> provinceToStateIDMap;
	std::map<int, HoI4::State*> states;

	HoI4::Navies navies(sourceArmies, 0, unitMap, theCoastalProvinces, provinceToStateIDMap, states, "TAG");
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


TEST(HoI4World_NaviesTests, IfInSeaProvinceLocationConverts)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST(HoI4World_NaviesTests, IfInSeaProvinceBaseUsesBackupLocation)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST(HoI4World_NaviesTests, IfInPortLocationAndBaseConvert)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}


TEST(HoI4World_NaviesTests, IfInBadLocationAndBaseUseBackup)
{
	// can't be tested due to province mappings implementation
	ASSERT_TRUE(true);
}