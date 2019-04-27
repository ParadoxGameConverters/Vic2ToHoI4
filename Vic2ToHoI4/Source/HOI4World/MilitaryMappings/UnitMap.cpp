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



#include "UnitMap.h"
#include "ParserHelpers.h"



HoI4::UnitMap::UnitMap(std::istream& theStream)
{
	registerKeyword(std::regex("category"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString categoryString(theStream);
		category = categoryString.getString();
	});
	registerKeyword(std::regex("type"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword(std::regex("equipment"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString equipmentString(theStream);
		equipment = equipmentString.getString();
	});
	registerKeyword(std::regex("version"), [this](const std::string & unused, std::istream & theStream) {
		commonItems::singleString versionString(theStream);
		version = versionString.getString();
	});
	registerKeyword(std::regex("size"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt sizeInt(theStream);
		size = sizeInt.getInt();
	});

	parseStream(theStream);
}