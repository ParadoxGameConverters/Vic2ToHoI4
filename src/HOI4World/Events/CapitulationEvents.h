#ifndef CAPITULATION_EVENTS_H
#define CAPITULATION_EVENTS_H



#include "src/HOI4World/Events/Event.h"
#include <set>
#include <string>



void updateCapitulationEvent(HoI4::Event& theEvent, const std::set<std::string>& majorIdeologies);



#endif // CAPITULATION_EVENTS_H