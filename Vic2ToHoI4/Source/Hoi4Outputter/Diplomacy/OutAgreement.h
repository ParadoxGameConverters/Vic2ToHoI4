#ifndef OUT_AGREEMENT_H
#define OUT_AGREEMENT_H



#include "../../HOI4World/Diplomacy/Agreement.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const Agreement& agreement);

}



#endif // OUT_AGREEMENT_H