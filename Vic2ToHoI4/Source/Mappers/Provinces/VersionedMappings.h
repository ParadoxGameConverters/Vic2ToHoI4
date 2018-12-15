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



#include "ProvinceMappingTypes.h"
#include "newParser.h"



class versionMappings: commonItems::parser
{
	public:
	versionMappings(std::istream& theStream);

	auto getVic2ToHoI4Mapping() const { return Vic2ToHoI4ProvinceMap; }
	auto getHoI4ToVic2Mapping() const { return HoI4ToVic2ProvinceMap; }

	private:
	void insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Nums, const std::vector<int>& HoI4nums);
	void insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Nums, const std::vector<int>& HoI4nums);

	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};
