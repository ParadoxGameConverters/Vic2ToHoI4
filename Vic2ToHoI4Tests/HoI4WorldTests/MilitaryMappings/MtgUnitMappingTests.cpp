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
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/MtgUnitMapping.h"



TEST(HoI4World_mtgUnitMappingTests, defaultVic2TypeIsBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	HoI4::MtgUnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMapping().first, "");
}


TEST(HoI4World_mtgUnitMappingTests, Vic2TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t}\n";
	input << "\t}";

	HoI4::MtgUnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMapping().first, "irregular");
}


TEST(HoI4World_mtgUnitMappingTests, noHoI4MeansEmptyVector)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	HoI4::MtgUnitMapping theMapping(input);

	ASSERT_TRUE(theMapping.getMapping().second.empty());
}


TEST(HoI4World_mtgUnitMappingTests, MtgUnitMappingHandlesFilledHoI4UnitTypeCorrectly)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmap = {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";

	HoI4::MtgUnitMapping theMapping(input);
	ASSERT_EQ(std::string("land"), theMapping.getMapping().second[0].getType());
}


TEST(HoI4World_mtgUnitMappingTests, MtgUnitMappingHandlesMultipleHoI4Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmap = {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = sea\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";

	HoI4::MtgUnitMapping theMapping(input);
	ASSERT_EQ(std::string("sea"), theMapping.getMapping().second[1].getType());
}