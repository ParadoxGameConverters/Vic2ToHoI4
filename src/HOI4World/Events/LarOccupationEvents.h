#ifndef LAR_OCCUPATION_EVENTS_H
#define LAR_OCCUPATION_EVENTS_H



#include "src/HOI4World/Events/Event.h"
#include <set>
#include <string>



namespace HoI4
{

void updateCreateUprisingEvent(HoI4::Event& theEvent, const std::set<std::string>& majorIdeologies);

}



#endif // LAR_OCCUPATION_EVENTS_H