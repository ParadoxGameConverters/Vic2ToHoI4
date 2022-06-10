#ifndef OUT_SHARED_FOCUS_H
#define OUT_SHARED_FOCUS_H



#include "src/HOI4World/SharedFocus.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const SharedFocus& focus);

}



#endif // OUT_SHARED_FOCUS_H