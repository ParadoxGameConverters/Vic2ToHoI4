#ifndef MTG_SHIP_OUTPUTTER
#define MTG_SHIP_OUTPUTTER



#include "../../HOI4World/Navies/MtgShip.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator << (std::ostream& output, const MtgShip& instance);
}



#endif // MTG_SHIP_OUTPUTTER