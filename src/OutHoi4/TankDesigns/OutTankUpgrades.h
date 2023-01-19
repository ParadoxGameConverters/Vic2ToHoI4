#ifndef OUT_TANK_UPGRADES_H
#define OUT_TANK_UPGRADES_H



#include "src/HOI4World/TankDesigns/TankUpgrades.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const TankUpgrades& theUpgrades);

}



#endif // OUT_TANK_UPGRADES_H
