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



#include "UnitMappings.h"
#include "UnitMapping.h"



HoI4::UnitMappings::UnitMappings(std::istream& theStream)
{
	registerKeyword(std::regex("link"), [this](const std::string & unused, std::istream & theStream)
	{
		UnitMapping newMapping(theStream);
		unitMap.insert(newMapping.getMappings());
	});

	parseStream(theStream);
}


bool HoI4::UnitMappings::hasMatchingType(const std::string& Vic2Type) const
{
	return unitMap.count(Vic2Type) > 0;
}


HoI4::HoI4UnitType HoI4::UnitMappings::getMatchingUnitInfo(const std::string& Vic2Type) const
{
	if (hasMatchingType(Vic2Type))
	{
		return unitMap.find(Vic2Type)->second;
	}
	else
	{
		HoI4UnitType unitMap;
		return unitMap;
	}
}