#ifndef OUT_OCCUPATION_LAW_H
#define OUT_OCCUPATION_LAW_H



#include "src/HOI4World/Scorers/Scorer.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const Scorer& scorer);

}



#endif // OUT_OCCUPATION_LAW_H