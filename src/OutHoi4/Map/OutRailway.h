#ifndef OUTHOI4_MAP_OUTRAILWAY_H
#define OUTHOI4_MAP_OUTRAILWAY_H



#include "src/HOI4World/Map/Railway.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Railway& railway);

}



#endif // OUTHOI4_MAP_OUTRAILWAY_H