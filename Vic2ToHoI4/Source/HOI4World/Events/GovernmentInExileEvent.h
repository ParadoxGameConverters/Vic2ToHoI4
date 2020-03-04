#ifndef GOVERNMENT_IN_EXILE_EVENT_H
#define GOVERNMENT_IN_EXILE_EVENT_H



#include "Event.h"
#include <set>
#include <string>


namespace HoI4
{

Event createGovernmentInExileEvent(const std::set<std::string>& majorIdeologies);

} // namespace HoI4



#endif // GOVERNMENT_IN_EXILE_EVENT_H