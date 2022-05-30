#ifndef OUT_SHIP_MODULES_H
#define OUT_SHIP_MODULES_H



#include "HOI4World/ShipTypes/ShipModules.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const shipModules& theModules);

}



#endif // OUT_SHIP_MODULES_H
