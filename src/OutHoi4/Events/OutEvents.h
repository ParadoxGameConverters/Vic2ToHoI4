#ifndef OUT_EVENTS_H
#define OUT_EVENTS_H



#include "src/HOI4World/Events/Events.h"



namespace HoI4
{

void outputEvents(const Events& theEvents, const std::filesystem::path& outputName);

}



#endif // OUT_EVENTS_H