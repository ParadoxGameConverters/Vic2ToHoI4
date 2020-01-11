/*Copyright (c) 2018 The Paradox Game Converters Project

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



#ifndef V2PARTY_H_
#define V2PARTY_H_



#include "newParser.h"
#include <memory>



namespace Vic2
{

class Party: commonItems::parser
{
	public:
		Party() = default;
		Party(const Party&) = default;
		Party& operator=(const Party&) = default;
		Party(Party&&) = default;
		Party& operator=(Party&&) = default;
		explicit Party(std::istream& theStream);

		std::string getName() const { return name; }
		std::string getIdeology() const { return ideology; }
		std::string getWarPolicy() const { return warPolicy; }

	private:
		std::string name = "";
		std::string ideology = "conservative";
		std::string economic_policy = "interventionism";
		std::string trade_policy = "protectionism";
		std::string religious_policy = "moralism";
		std::string citizenship_policy = "residency";
		std::string warPolicy = "pro_military";
};

bool operator==(const Party& one, const Party& other);
bool operator<(const Party& one, const Party& other);

}



#endif // V2PARTY_H_
