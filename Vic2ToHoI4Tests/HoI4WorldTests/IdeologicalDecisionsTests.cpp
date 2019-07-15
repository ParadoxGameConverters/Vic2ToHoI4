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
#include "../Vic2ToHoI4/Source/HOI4World/Decisions/IdeologicalDecisions.h"
#include <sstream>



TEST(HoI4World_IdeologicalDecisionsTests, defaultsToEmptyList)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	ASSERT_EQ(ideologicalDecisions.getCategories().size(), 0);
}


TEST(HoI4World_IdeologicalDecisionsTests, categoriesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcategoryOne = {}\n";
	input << "\tcategoryTwo = {}\n";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	ASSERT_EQ(ideologicalDecisions.getCategories().size(), 2);
}


TEST(HoI4World_IdeologicalDecisionsTests, handlesNoRequiredIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	ASSERT_TRUE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_IdeologicalDecisionsTests, falseIfRequiredIdeologyMissing)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	ASSERT_FALSE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_IdeologicalDecisionsTests, trueIfRequiredIdeologyPresent)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutism");
	ASSERT_TRUE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_IdeologicalDecisionsTests, falseIfAnyRequiredIdeologyMissing)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t\tdemocracy\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutism");
	ASSERT_FALSE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_IdeologicalDecisionsTests, trueIfAllRequiredIdeologiesPresent)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t\tdemocracy\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutism");
	majorIdeologies.insert("democracy");
	ASSERT_TRUE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}