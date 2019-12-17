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
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/UnitMapping.h"



TEST(HoI4World_unitMappingTests, nulloptOnNoVic2Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	HoI4::UnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMappings(), std::nullopt);
}


TEST(HoI4World_unitMappingTests, Vic2TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";

	HoI4::UnitMapping theMapping(input);

	auto mapping = theMapping.getMappings();
	ASSERT_TRUE(mapping);
	ASSERT_EQ(mapping->first, "irregular");
}


TEST(HoI4World_unitMappingTests, nulloptOnNoHoI4Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	HoI4::UnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMappings(), std::nullopt);
}


TEST(HoI4World_unitMappingTests, UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
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

	HoI4::UnitMapping theMapping(input);

	auto mapping = theMapping.getMappings();
	ASSERT_TRUE(mapping);
	ASSERT_EQ(std::string("land"), mapping->second.getType());
}