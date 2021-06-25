#ifndef NAVAL_TREATY_EVENT_UPDATERS_H
#define NAVAL_TREATY_EVENT_UPDATERS_H



#include "Event.h"
#include <set>



namespace HoI4
{

void updateNavalTreatyEventOne(Event& event, const std::set<std::string>& majorIdeologies);
void updateNavalTreatyEventFour(Event& event, const std::set<std::string>& majorIdeologies);
void updateNavalTreatyEventSix(Event& event, const std::set<std::string>& majorIdeologies);
void updateNavalTreatyEventTen(Event& event, const std::set<std::string>& majorIdeologies);

} // namespace HoI4



#endif // NAVAL_TREATY_EVENT_UPDATERS_H