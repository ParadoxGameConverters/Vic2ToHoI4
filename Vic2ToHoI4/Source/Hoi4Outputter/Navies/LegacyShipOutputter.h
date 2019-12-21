#ifndef LEGACY_SHIP_OUTPUTTER
#define LEGACY_SHIP_OUTPUTTER



#include "../../HOI4World/Navies/LegacyShip.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator << (std::ostream& output, const LegacyShip& instance);
}



#endif // LEGACY_SHIP_OUTPUTTER