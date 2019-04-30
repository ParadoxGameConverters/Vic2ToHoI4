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



#ifndef UNIT_MAPPINGS_H_
#define UNIT_MAPPINGS_H_



#include "HoI4UnitType.h"
#include "newParser.h"
#include <map>



namespace HoI4
{

class UnitMappings: commonItems::parser
{
	public:
		UnitMappings(std::istream& theStream);
		UnitMappings() = delete;
		~UnitMappings() = default;
		UnitMappings(const UnitMappings&) = default;
		UnitMappings(UnitMappings&&) = default;
		UnitMappings& operator=(const UnitMappings&) = default;
		UnitMappings& operator=(UnitMappings&&) = default;

		bool hasMatchingType(const std::string& Vic2Type) const;
		HoI4::HoI4UnitType getMatchingUnitInfo(const std::string& Vic2Type) const;

	private:
		std::map<std::string, HoI4::HoI4UnitType> unitMap;
};

}



#endif // UNIT_MAPPINGS_H_