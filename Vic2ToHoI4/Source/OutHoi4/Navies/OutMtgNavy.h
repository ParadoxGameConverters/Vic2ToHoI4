#ifndef OUT_MTG_NAVY_H
#define OUT_MTG_NAVY_H



#include "HOI4World/Navies/MtgNavy.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const MtgNavy& instance);

}



#endif // OUT_MTG_NAVY_H