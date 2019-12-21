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
#include "../Vic2ToHoI4/Source/HOI4World/States/StateBuildings.h"
#include <sstream>



TEST(HoI4World_StateBuildingsTests, civFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getCivFactories(), 0);
}


TEST(HoI4World_StateBuildingsTests, civFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tindustrial_complex = 5\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getCivFactories(), 5);
}


TEST(HoI4World_StateBuildingsTests, milFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getMilFactories(), 0);
}


TEST(HoI4World_StateBuildingsTests, milFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tarms_factory = 7\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getMilFactories(), 7);
}


TEST(HoI4World_StateBuildingsTests, dockyardsDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getMilFactories(), 0);
}


TEST(HoI4World_StateBuildingsTests, dockyardsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getDockyards(), 1);
}


TEST(HoI4World_StateBuildingsTests, dockyardsCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t\t5678 = {\n";
	input << "\t\t\t\tnaval_base = 3";
	input << "\t\t\t}\n";
	input << "\t\t}";
	HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(theStateBuildings.getDockyards(), 4);
}