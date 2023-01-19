#ifndef OUT_TANK_DESIGNS_H
#define OUT_TANK_DESIGNS_H



#include "src/HOI4World/TankDesigns/TankDesigns.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const TankDesigns& theDesigns);

}



#endif // OUT_TANK_DESIGNS_H