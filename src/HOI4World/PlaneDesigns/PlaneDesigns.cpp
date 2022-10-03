#include "src/HOI4World/PlaneDesigns/PlaneDesigns.h"



HoI4::PlaneDesigns::PlaneDesigns(const PossiblePlaneDesigns& possiblePlaneDesigns, const technologies& ownedTechs)
{
	for (auto& possibleDesign : possiblePlaneDesigns.getPossiblePlaneDesigns())
	{
		if (possibleDesign.isValidDesign(ownedTechs))
		{
			auto newDesign(possibleDesign);
			planeDesigns.insert(std::make_pair(newDesign.getName(), newDesign));
		}
	}
}