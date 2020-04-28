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



#ifndef WAR_H_
#define WAR_H_



#include "Parser.h"
#include <set>
#include <string>



namespace Vic2
{


class War: commonItems::parser
{
	public:
		War(std::istream& theStream);

		std::string getOriginalAttacker() const { return originalAttacker; }
		std::set<std::string> getAttackers() const { return attackers; }
		std::string getOriginalDefender() const { return originalDefender; }
		std::set<std::string> getDefenders() const { return defenders; }
		std::string getCB() const { return CB; }

	private:
		std::string originalAttacker;
		std::set<std::string> attackers;
		std::string originalDefender;
		std::set<std::string> defenders;
		std::string CB;
};


}



#endif // WAR_H_