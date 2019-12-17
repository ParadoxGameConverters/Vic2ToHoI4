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
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/UnitMappings.h"



TEST(HoI4World_unitMappingsTests, NonExistingMappingNotAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	HoI4::UnitMappings theMappings(input);
	ASSERT_FALSE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_unitMappingsTests, Vic2UnitAddedToUnitMapping)
{
	std::stringstream input(
		"= {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = irregular\n"\
		"\t\t}\n"\
		"\t}"
	);
	HoI4::UnitMappings theMappings(input);
	ASSERT_TRUE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_unitMappingsTests, UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = infantry\n"\
		"\t\t\thoi = {\n"\
		"\t\t\t\ttype = land\n"\
		"\t\t\t}\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	HoI4::UnitMappings theMappings(input);

	auto mapping = theMappings.getMatchingUnitInfo("infantry");
	ASSERT_TRUE(mapping);
	ASSERT_EQ(std::string("land"), mapping->getType());
}