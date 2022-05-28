#ifndef OUT_TANK_DESIGN
#define OUT_TANK_DESIGN



#include "HOI4World/TankDesigns/TankDesign.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const TankDesign& theDesign);

}



#endif // OUT_TANK_DESIGN