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



#ifndef NAVIES_H_
#define NAVIES_H_



#include "CoastalProvinces.h"
#include "HoI4State.h"
#include "MilitaryMappings/UnitMap.h"
#include "Navies/LegacyNavy.h"
#include "../V2World/Army.h"
#include <map>
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{

class Navies
{
	public:
		Navies(
			std::vector<const Vic2::Army*> srcArmies,
			int backupNavalLocation,
			const std::map<std::string, HoI4::UnitMap>& unitMap,
			const HoI4::coastalProvinces& theCoastalProvinces,
			const std::map<int, int>& provinceToStateIDMap,
			std::map<int, HoI4::State*> states,
			const std::string& tag);
		Navies() = delete;
		~Navies() = default;
		Navies(const Navies&) = default;
		Navies(Navies&&) = default;
		Navies& operator=(const Navies&) = default;
		Navies& operator=(Navies&&) = default;

		void outputLegacy(std::ostream& output);

	private:
		std::vector<HoI4::LegacyNavy> navies;
};

}



#endif // NAVIES_H_