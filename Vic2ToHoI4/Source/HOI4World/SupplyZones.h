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



#ifndef HOI4_SUPPLY_ZONES_H
#define HOI4_SUPPLY_ZONES_H



#include "newParser.h"
#include <map>
#include <set>
#include <string>



class HoI4States;
class HoI4SupplyZone;



namespace HoI4
{

class DefaultState;



class SupplyZones: commonItems::parser
{
	public:
		explicit SupplyZones(const std::map<int, HoI4::DefaultState>& defaultStates);
		void output();
		void convertSupplyZones(const HoI4States& states);

	private:
		SupplyZones(const SupplyZones&) = delete;
		SupplyZones& operator=(const SupplyZones&) = delete;

		void importStates(const std::map<int, HoI4::DefaultState>& defaultStates);

		std::map<int, std::set<int>> defaultStateToProvinceMap;
		std::map<int, std::string> supplyZonesFilenames;
		std::map<int, HoI4SupplyZone*> supplyZones;
		std::map<int, int> provinceToSupplyZoneMap;
};

}



#endif // HOI4_SUPPLY_ZONES_H