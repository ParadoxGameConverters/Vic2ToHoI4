#ifndef TANK_DESIGNS_H
#define TANK_DESIGNS_H



#include "HOI4World/Technologies.h"
#include "Parser.h"
#include "PossibleTankDesigns.h"
#include "TankDesign.h"



namespace HoI4
{

class TankDesigns
{
  public:
	TankDesigns(const PossibleTankDesigns& possibleTankDesigns, const technologies& ownedTechs);

	[[nodiscard]] bool hasTankDesign(const std::string& designName) const { return tankDesigns.contains(designName); }

	friend std::ostream& operator<<(std::ostream& output, const TankDesigns& theDesigns);

  private:
	std::map<std::string, TankDesign> tankDesigns;
};

} // namespace HoI4



#endif // TANK_DESIGNS_H