#ifndef OUT_PLANE_DESIGN
#define OUT_PLANE_DESIGN



#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const PlaneDesign& the_design);

} // namespace HoI4



#endif // OUT_PLANE_DESIGN