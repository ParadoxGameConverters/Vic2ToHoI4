#include "src/HOI4World/PlaneDesigns/PlaneDesigns.h"



HoI4::PlaneDesigns::PlaneDesigns(const PossiblePlaneDesigns& possible_plane_designs, const technologies& owned_techs)
{
	for (auto& possible_design: possible_plane_designs.GetPossiblePlaneDesigns())
	{
		if (possible_design.IsValidDesign(owned_techs))
		{
			auto new_design(possible_design);
			plane_designs_.emplace(std::make_pair(new_design.GetName(), new_design));
		}
	}
}