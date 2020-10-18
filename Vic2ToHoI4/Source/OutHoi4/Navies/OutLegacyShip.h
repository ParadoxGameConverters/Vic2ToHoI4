#ifndef OUT_LEGACY_SHIP_H
#define OUT_LEGACY_SHIP_H



#include "HOI4World/Navies/LegacyShip.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const LegacyShip& instance);

}



#endif // OUT_LEGACY_SHIP_H