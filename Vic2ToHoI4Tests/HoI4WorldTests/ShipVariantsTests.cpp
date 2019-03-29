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
#include "../../Vic2ToHoI4/Source/HOI4World/ShipVariants.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipVariant.h"
#include <sstream>



TEST(HoI4World_shipVariantsTests, noInputGivesDefaultOutput)
{
	std::vector<HoI4::shipVariant> possibleVariants;
	std::set<std::string> ownedTechs;

	HoI4::shipVariants theVaraiants(possibleVariants, ownedTechs, "");

	std::stringstream output;
	output << theVaraiants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_shipVariantsTests, canReceiveVariant)
{
	std::stringstream input;
	input << "ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\tparent_version = 0\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::shipVariant theShipVariant(input);
	std::vector<HoI4::shipVariant> possibleVariants;
	possibleVariants.push_back(theShipVariant);

	std::set<std::string> ownedTechs;

	HoI4::shipVariants theVaraiants(possibleVariants, ownedTechs, "TAG");

	std::stringstream output;
	output << theVaraiants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tname_group = TAG_SS_HISTORICAL\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	expectedOutput << "\t\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_shipVariantsTests, variantsNeedRequiredTechs)
{
	std::vector<HoI4::shipVariant> possibleVariants;

	std::stringstream input;
	input << "ship_type = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\ttech1\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\tparent_version = 0\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::shipVariant theShipVariant(input);
	possibleVariants.push_back(theShipVariant);

	std::stringstream input2;
	input2 << "ship_type = {\n";
	input2 << "\trequired_techs = {\n";
	input2 << "\t\ttech2\n";
	input2 << "\t}\n";
	input2 << "\tname = \"Early submarine2\"\n";
	input2 << "\ttype = ship_hull_submarine_1\n";
	input2 << "\tname_group = SS_HISTORICAL\n";
	input2 << "\tparent_version = 0\n";
	input2 << "\t\tmodules = {\n";
	input2 << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input2 << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input2 << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input2 << "\t}\n";
	input2 << "\tobsolete = yes\n";
	input2 << "}\n";
	HoI4::shipVariant theShipVariant2(input2);
	possibleVariants.push_back(theShipVariant2);

	std::set<std::string> ownedTechs;
	ownedTechs.insert("tech2");

	HoI4::shipVariants theVaraiants(possibleVariants, ownedTechs, "TAG");

	std::stringstream output;
	output << theVaraiants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine2\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tname_group = TAG_SS_HISTORICAL\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	expectedOutput << "\t\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_shipVariantsTests, variantsCanBeBlocked)
{
	std::vector<HoI4::shipVariant> possibleVariants;

	std::stringstream input;
	input << "ship_type = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\ttech1\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\tparent_version = 0\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::shipVariant theShipVariant(input);
	possibleVariants.push_back(theShipVariant);

	std::stringstream input2;
	input2 << "ship_type = {\n";
	input2 << "\tblocking_techs = {\n";
	input2 << "\t\ttech2\n";
	input2 << "\t}\n";
	input2 << "\tname = \"Early submarine2\"\n";
	input2 << "\ttype = ship_hull_submarine_1\n";
	input2 << "\tname_group = SS_HISTORICAL\n";
	input2 << "\tparent_version = 0\n";
	input2 << "\t\tmodules = {\n";
	input2 << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input2 << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input2 << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input2 << "\t}\n";
	input2 << "\tobsolete = yes\n";
	input2 << "}\n";
	HoI4::shipVariant theShipVariant2(input2);
	possibleVariants.push_back(theShipVariant2);

	std::set<std::string> ownedTechs;
	ownedTechs.insert("tech2");

	HoI4::shipVariants theVaraiants(possibleVariants, ownedTechs, "TAG");

	std::stringstream output;
	output << theVaraiants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tname_group = TAG_SS_HISTORICAL\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	expectedOutput << "\t\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}