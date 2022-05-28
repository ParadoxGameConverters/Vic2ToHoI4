#ifndef OUT_EVENT_OPTION_H
#define OUT_EVENT_OPTION_H



#include "HOI4World/Events/EventOption.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const EventOption& theOption);

}



#endif // OUT_EVENT_OPTION_H