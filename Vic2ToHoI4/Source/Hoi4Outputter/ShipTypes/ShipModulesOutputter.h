#ifndef SHIP_MODULES_OUTPUTTER
#define SHIP_MODULES_OUTPUTTER



#include "../../HOI4World/ShipTypes/ShipModules.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator<<(std::ostream& output, const shipModules& theModules);
}



#endif // SHIP_MODULES_OUTPUTTER
