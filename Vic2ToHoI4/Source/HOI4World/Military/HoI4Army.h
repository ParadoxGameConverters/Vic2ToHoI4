#ifndef HOI4_ARMY_H_
#define HOI4_ARMY_H_



#include "Division.h"
#include "DivisionTemplate.h"
#include "../MilitaryMappings/MilitaryMappings.h"
#include "../States/HoI4States.h"
#include "../../V2World/Army.h"
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