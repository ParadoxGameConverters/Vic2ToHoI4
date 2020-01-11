#ifndef EVENT_OUTPUTTER_H
#define EVENT_OUTPUTTER_H



#include "../../HOI4World/Events/Event.h"
#include <ostream>



namespace HoI4
{
std::ofstream& operator << (std::ofstream& out, const Event& theEvent);
}




#endif // EVENT_OUTPUTTER_H