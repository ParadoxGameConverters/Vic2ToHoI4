#ifndef OUT_MTG_SHIP_H
#define OUT_MTG_SHIP_H



#include "src/HOI4World/Navies/MtgShip.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const MtgShip& instance);

}



#endif // OUT_MTG_SHIP_H