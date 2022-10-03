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
	PlaneDesigns(const PossiblePlaneDesigns& possiblePlaneDesigns, const technologies& ownedTechs);

	[[nodiscard]] bool hasPlaneDesign(const std::string& designName) const { return planeDesigns.contains(designName); }

	friend std::ostream& operator<<(std::ostream& output, const PlaneDesigns& theDesigns);

  private:
	std::map<std::string, PlaneDesign> planeDesigns;
};

} // namespace HoI4



#endif // PLANE_DESIGNS_H