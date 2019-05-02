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
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/AllMilitaryMappings.h"
#include <sstream>


class HoI4World_allMilitaryMappingsTests: public ::testing::Test
{
	protected:
		HoI4World_allMilitaryMappingsTests();

		std::unique_ptr<HoI4::allMilitaryMappings> allTheMappings;
};


HoI4World_allMilitaryMappingsTests::HoI4World_allMilitaryMappingsTests()
{
	std::stringstream input;
	input << "default = {\n";
	input << "\tunit_map = {}\n";
	input << "\tmtg_unit_map = {}\n";
	input << "}\n";
	input << "PDM = {\n";
	input << "\tunit_map = {}\n";
	input << "\tmtg_unit_map = {}\n";
	input << "}\n";
	allTheMappings = std::make_unique<HoI4::allMilitaryMappings>(input);
}



TEST_F(HoI4World_allMilitaryMappingsTests, getDefaultMappingsWithNoMods)
{
	std::vector<std::string> mods;
	const HoI4::militaryMappings& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_allMilitaryMappingsTests, getDefaultMappingsWithInvalidMod)
{
	std::vector<std::string> mods = { "NotAMod" };
	const HoI4::militaryMappings& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_allMilitaryMappingsTests, getPDMMappingsWithPDM)
{
	std::vector<std::string> mods = { "PDM" };
	const HoI4::militaryMappings& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("PDM"), specificMappings.getMappingsName());
}