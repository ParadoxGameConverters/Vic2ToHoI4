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



#include "ProvinceMapping.h"
#include "ParserHelpers.h"



mapping::mapping(std::istream& theStream)
{
	registerKeyword(std::regex("vic2"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt provinceNum(theStream);
		Vic2Nums.push_back(provinceNum.getInt());
	});
	registerKeyword(std::regex("hoi4"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt provinceNum(theStream);
		HoI4Nums.push_back(provinceNum.getInt());
	});

	parseStream(theStream);

	if (Vic2Nums.size() == 0)
	{
		Vic2Nums.push_back(0);
	}
	if (HoI4Nums.size() == 0)
	{
		HoI4Nums.push_back(0);
	}
}