#ifndef OUT_WAR_H
#define OUT_WAR_H


#include "HOI4World/Diplomacy/HoI4War.h"
#include <ostream>


namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const War& theWar);

}



#endif // OUT_WAR_H