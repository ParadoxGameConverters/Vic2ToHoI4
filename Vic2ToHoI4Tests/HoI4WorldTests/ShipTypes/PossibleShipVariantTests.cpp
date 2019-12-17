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
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/PossibleShipVariants.h"
#include <sstream>



TEST(HoI4World_possibleShipVariantsTests, variantsCanBeLoaded)
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
	input << "ship_type = {\n";
	input << "\tname = \"Early submarine2\"\n";
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
	HoI4::possibleShipVariants theShipVariants(input);

	ASSERT_EQ(theShipVariants.getPossibleVariants().size(), 2);
}