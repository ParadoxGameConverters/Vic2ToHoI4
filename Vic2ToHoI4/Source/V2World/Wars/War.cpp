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



#include "War.h"
#include "WarGoal.h"
#include "ParserHelpers.h"



Vic2::War::War(std::istream& theStream)
{
	registerKeyword(std::regex("attacker"), [this](const std::string& unused, std::istream& theStream)
	{
		commonItems::singleString attackerString(theStream);
		attackers.insert(attackerString.getString());
	});
	registerKeyword(std::regex("original_attacker"), [this](const std::string& unused, std::istream& theStream)
	{
		commonItems::singleString originalAttackerString(theStream);
		originalAttacker = originalAttackerString.getString();
	});
	registerKeyword(std::regex("defender"), [this](const std::string& unused, std::istream& theStream)
	{
		commonItems::singleString defenderString(theStream);
		defenders.insert(defenderString.getString());
	});
	registerKeyword(std::regex("original_defender"), [this](const std::string& unused, std::istream& theStream)
	{
		commonItems::singleString originalDefenderString(theStream);
		originalDefender = originalDefenderString.getString();
	});
	registerKeyword(std::regex("original_wargoal"), [this](const std::string& unused, std::istream& theStream)
	{
		Vic2::WarGoal theWarGoal(theStream);
		CB = theWarGoal.getCB();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}