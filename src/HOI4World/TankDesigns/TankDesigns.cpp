#include "src/HOI4World/TankDesigns/TankDesigns.h"



HoI4::TankDesigns::TankDesigns(const PossibleTankDesigns& possibleTankDesigns, const technologies& ownedTechs)
{
	for (auto& possibleDesign: possibleTankDesigns.getPossibleTankDesigns())
	{
		if (possibleDesign.isValidDesign(ownedTechs))
		{
			auto newDesign(possibleDesign);
			tankDesigns.insert(std::make_pair(newDesign.getName(), newDesign));
		}
	}
}