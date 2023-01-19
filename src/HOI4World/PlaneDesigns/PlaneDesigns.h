#ifndef PLANE_DESIGNS_H
#define PLANE_DESIGNS_H



#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include "src/HOI4World/PlaneDesigns/PossiblePlaneDesigns.h"
#include "src/HOI4World/Technologies.h"



namespace HoI4
{

class PlaneDesigns
{
  public:
	PlaneDesigns(const PossiblePlaneDesigns& possible_plane_designs, const technologies& owned_techs);

	[[nodiscard]] bool HasPlaneDesign(const std::string& design_name) const
	{
		return plane_designs_.contains(design_name);
	}

	friend std::ostream& operator<<(std::ostream& output, const PlaneDesigns& the_designs);

  private:
	std::map<std::string, PlaneDesign> plane_designs_;
};

} // namespace HoI4



#endif // PLANE_DESIGNS_H