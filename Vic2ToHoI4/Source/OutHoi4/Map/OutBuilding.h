#ifndef OUT_BUILDING_H
#define OUT_BUILDING_H


#include "HOI4World/Map/Hoi4Building.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Building& building);

}



#endif // OUT_BUILDING_H