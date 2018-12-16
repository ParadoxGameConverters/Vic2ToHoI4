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



#include "VersionedMappings.h"
#include "ProvinceMapping.h"



versionMappings::versionMappings(std::istream& theStream)
{
	registerKeyword(std::regex("link"), [this](const std::string& unused, std::istream& theStream){
		mapping theMapping(theStream);
		insertIntoHoI4ToVic2ProvinceMap(theMapping.getVic2Nums(), theMapping.getHoI4Nums());
		insertIntoVic2ToHoI4ProvinceMap(theMapping.getVic2Nums(), theMapping.getHoI4Nums());
	});

	parseStream(theStream);
}


void versionMappings::insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Nums, const std::vector<int>& HoI4Nums)
{
	for (auto num: HoI4Nums)
	{
		if (num != 0)
		{
			HoI4ToVic2ProvinceMap.insert(make_pair(num, Vic2Nums));
		}
	}
}


void versionMappings::insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Nums, const std::vector<int>& HoI4Nums)
{
	for (auto num: Vic2Nums)
	{
		if (num != 0)
		{
			Vic2ToHoI4ProvinceMap.insert(make_pair(num, HoI4Nums));
		}
	}
}