#ifndef OUT_PLANE_MODULES_H
#define OUT_PLANE_MODULES_H



#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const PlaneModules& the_modules);

}



#endif // OUT_PLANE_MODULES_H