#ifndef OUT_PLANE_DESIGNS_H
#define OUT_PLANE_DESIGNS_H



#include "src/HOI4World/PlaneDesigns/PlaneDesigns.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const PlaneDesigns& theDesigns);

} // namespace HoI4



#endif // OUT_PLANE_DESIGNS_H