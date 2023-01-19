#ifndef OUT_AIRPLANE_H
#define OUT_AIRPLANE_H



#include "src/HOI4World/Military/Airplane.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const Airplane& instance);

}



#endif // OUT_AIRPLANE_H