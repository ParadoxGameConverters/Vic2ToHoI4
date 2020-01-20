#ifndef EVENT_OPTION_OUTPUTTER
#define EVENT_OPTION_OUTPUTTER



#include "../../HOI4World/Events/EventOption.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator << (std::ostream& out, const EventOption& theOption);
}



#endif // EVENT_OPTION_OUTPUTTER