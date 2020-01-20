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



#ifndef HOI4_ARMY_H_
#define HOI4_ARMY_H_



#include "Division.h"
#include "DivisionTemplate.h"
#include "MilitaryMappings/MilitaryMappings.h"
#include "States/HoI4States.h"
#include "../V2World/Army.h"
#include <string>
#include <map>
#include <vector>



namespace Vic2
{

class Army;

}


namespace HoI4
{


typedef struct {
	double unitSize;
	Vic2::Regiment* regiment;
} sizedRegiment;


class Army
{
	public:
		Army() = default;

		void addSourceArmies(std::vector<const Vic2::Army*> _sourceArmies) { sourceArmies = std::move(_sourceArmies); }

		void convertArmies(
			const militaryMappings& theMilitaryMappings,
			int backupLocation,
			double forceMultiplier,
			const HoI4::States& theStates
		);

		friend std::ostream& operator << (std::ostream& output, const Army& theArmy);

	private:
		void convertArmyDivisions(const militaryMappings& theMilitaryMappings, std::map<std::string, std::vector<sizedRegiment>>& BattalionsAndCompanies, int location);
		bool sufficientUnits(const std::map<std::string, std::vector<sizedRegiment>>& units, const std::map<std::string, std::string>& subs, const std::map<std::string, int>& req);
		bool isWastelandProvince(int provinceNum, const HoI4::States& theStates);

		std::vector<const Vic2::Army*> sourceArmies;
		std::vector<DivisionType> divisions;
};

std::ostream& operator << (std::ostream& output, const Army& theArmy);

}



#endif // HOI4_ARMY_H_