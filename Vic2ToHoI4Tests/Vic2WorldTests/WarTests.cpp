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
#include "../Vic2ToHoI4/Source/V2World/Wars/War.h"
#include <sstream>



TEST(Vic2World_WarTests, OriginalAttackerDefaultsToBlank)
{
	std::stringstream input;

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getOriginalAttacker(), "");
}


TEST(Vic2World_WarTests, OriginalAttackerCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_attacker=\"TAG\"\n";
	input << "}";

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getOriginalAttacker(), "TAG");
}


TEST(Vic2World_WarTests, AttackersDefaultToEmpty)
{
	std::stringstream input;

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getAttackers().size(), 0);
}


TEST(Vic2World_WarTests, AttackersCanBeAdded)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tattacker=\"TAG\"\n";
	input << "\tattacker=\"TWO\"\n";
	input << "}";

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getAttackers().size(), 2);
	ASSERT_EQ(theWar.getAttackers().count("TAG"), 1);
	ASSERT_EQ(theWar.getAttackers().count("TWO"), 1);
}


TEST(Vic2World_WarTests, OriginalDefenderDefaultsToBlank)
{
	std::stringstream input;

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getOriginalDefender(), "");
}


TEST(Vic2World_WarTests, OriginalDefenderCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_defender=\"TAG\"\n";
	input << "}";

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getOriginalDefender(), "TAG");
}


TEST(Vic2World_WarTests, DefendersDefaultToEmpty)
{
	std::stringstream input;

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getDefenders().size(), 0);
}


TEST(Vic2World_WarTests, DefendersCanBeAdded)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tdefender=\"TAG\"\n";
	input << "\tdefender=\"TWO\"\n";
	input << "}";

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getDefenders().size(), 2);
	ASSERT_EQ(theWar.getDefenders().count("TAG"), 1);
	ASSERT_EQ(theWar.getDefenders().count("TWO"), 1);
}


TEST(Vic2World_WarTests, CBDefaultsToBlank)
{
	std::stringstream input;

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getCB(), "");
}


TEST(Vic2World_WarTests, CBCanBeSet)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\toriginal_wargoal={\n";
	input << "\t\tcasus_belli=\"theCB\"\n";
	input << "\t}\n";
	input << "}";

	Vic2::War theWar(input);

	ASSERT_EQ(theWar.getCB(), "theCB");
}