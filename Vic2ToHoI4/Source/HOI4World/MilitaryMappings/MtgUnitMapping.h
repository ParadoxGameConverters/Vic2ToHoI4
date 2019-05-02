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



#ifndef MTG_UNIT_MAPPING_H_
#define MTG_UNIT_MAPPING_H_



#include "HoI4UnitType.h"
#include "newParser.h"



namespace HoI4
{

class MtgUnitMapping: commonItems::parser
{
	public:
		MtgUnitMapping(std::istream& theStream);

		auto getMapping() const { return std::make_pair(Vic2Type, HoI4Types); }

	private:
		std::string Vic2Type;
		std::vector<HoI4UnitType> HoI4Types;
};

}



#endif // MTG_UNIT_MAPPING_H_