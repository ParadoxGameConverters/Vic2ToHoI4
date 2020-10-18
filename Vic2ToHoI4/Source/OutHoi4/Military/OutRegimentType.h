#ifndef OUT_REGIMENT_H
#define OUT_REGIMENT_H



#include "HOI4World/Military/RegimentType.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const RegimentType& regiment);

}



#endif // OUT_REGIMENT_H