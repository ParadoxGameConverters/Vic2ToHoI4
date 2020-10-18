#ifndef OUT_EVENT_H
#define OUT_EVENT_H



#include "HOI4World/Events/Event.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Event& theEvent);

}



#endif // OUT_EVENT_H