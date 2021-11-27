#ifndef OUT_TANK_MODULES_H
#define OUT_TANK_MODULES_H



#include "HOI4World/TankDesigns/TankModules.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const TankModules& theModules);

}



#endif // OUT_TANK_MODULES_H
