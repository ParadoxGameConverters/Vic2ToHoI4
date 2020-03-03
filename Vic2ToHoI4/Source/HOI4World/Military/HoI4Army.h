#ifndef HOI4_ARMY_H
#define HOI4_ARMY_H



#include "../../V2World/Army.h"
#include "../MilitaryMappings/MilitaryMappings.h"
#include "../States/HoI4States.h"
#include "DivisionType.h"
#include <map>
#include <string>
#include <vector>



namespace Vic2
{

class Army;

}


namespace HoI4
{


typedef struct
{
	double unitSize = 0.0;
	double experience = 0.0;
} SizedRegiment;


class Army
{
  public:
	Army() = default;

	void addSourceArmies(const std::vector<Vic2::Army>& _sourceArmies) { sourceArmies = _sourceArmies; }

	void convertArmies(const militaryMappings& theMilitaryMappings,
		 int backupLocation,
		 double forceMultiplier,
		 const States& theStates);

	friend std::ostream& operator<<(std::ostream& output, const Army& theArmy);

  private:
	void convertArmyDivisions(const militaryMappings& theMilitaryMappings,
		 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
		 int location);

	std::vector<Vic2::Army> sourceArmies;
	std::vector<DivisionType> divisions;
};

} // namespace HoI4



#endif // HOI4_ARMY_H