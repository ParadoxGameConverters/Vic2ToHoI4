#ifndef OUT_OCCUPATION_LAW_H
#define OUT_OCCUPATION_LAW_H


#include <ostream>
#include "HOI4World/OccupationLaws/OccupationLaw.h"



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const OccupationLaw& occupationLaw);
	
}



#endif // OUT_OCCUPATION_LAW_H