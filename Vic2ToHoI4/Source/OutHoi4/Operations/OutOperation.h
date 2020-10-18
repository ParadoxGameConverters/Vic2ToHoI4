#ifndef OUT_OPERATION_H
#define OUT_OPERATION_H



#include "HOI4World/Operations/Operation.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Operation& operation);

}



#endif // OUT_OPERATION_H