#ifndef OUT_ARMY_H
#define OUT_ARMY_H



#include "HOI4World/Military/HoI4Army.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const Army& theArmy);

}



#endif // OUT_ARMY_H