#ifndef OUT_DIVISION_H
#define OUT_DIVISION_H


#include "HOI4World/Military/DivisionType.h"



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const DivisionType&);

}



#endif // OUT_DIVISION_H