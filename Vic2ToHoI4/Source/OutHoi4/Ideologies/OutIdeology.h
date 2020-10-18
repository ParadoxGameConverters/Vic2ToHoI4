#ifndef OUT_IDEOLOGY_H
#define OUT_IDEOLOGY_H



#include "HOI4World/Ideologies/Ideology.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Ideology& ideology);

}



#endif // OUT_IDEOLOGY_H