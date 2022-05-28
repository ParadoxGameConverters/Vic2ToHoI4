#ifndef OUT_DIVISION_TEMPLATE
#define OUT_DIVISION_TEMPLATE



#include "HOI4World/Military/DivisionTemplate.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const DivisionTemplateType& rhs);

}



#endif // OUT_DIVISION_TEMPLATE