#ifndef OUT_OCCUPATION_LAW_H
#define OUT_OCCUPATION_LAW_H



#include "src/HOI4World/OccupationLaws/OccupationLaw.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const OccupationLaw& occupationLaw);

}



#endif // OUT_OCCUPATION_LAW_H