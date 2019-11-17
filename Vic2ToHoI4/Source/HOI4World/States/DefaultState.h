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


#ifndef HOI4_DEFAULT_STATES_H_
#define HOI4_DEFAULT_STATES_H_


#include "newParser.h"
#include <set>
#include <string>



namespace HoI4
{

class DefaultState: commonItems::parser
{
	public:
		explicit DefaultState(std::istream& theStream);

		bool isImpassable() const { return impassable; }
		std::string getOwner() const { return ownerTag; }
		std::set<int> getProvinces() const { return provinces; }
		int getCivFactories() const { return civFactories; }
		int getMilFactories() const { return milFactories; }
		int getDockyards() const { return dockyards; }

	private:
		bool impassable = false;
		std::string ownerTag;
		std::set<int> provinces;
		int civFactories = 0;
		int milFactories = 0;
		int dockyards = 0;
};

}



#endif // HOI4_DEFAULT_STATES_H_