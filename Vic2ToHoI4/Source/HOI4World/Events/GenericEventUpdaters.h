#ifndef GENERIC_EVENT_UPDATERS
#define GENERIC_EVENT_UPDATERS



#include <string>
#include <set>



namespace HoI4
{
class Event;

void updateGenericEventOne(Event& eventOne);
void updateGenericEventTwo(Event& eventTwo, const std::set<std::string>& majorIdeologies);
void updateGenericEventsThreeFourAndSix(Event& event, int eventNum, const std::set<std::string>& majorIdeologies);
void updateGenericEventFive(Event& eventFive, const std::set<std::string>& majorIdeologies);
void updateGenericEventSeven(Event& eventFive, const std::set<std::string>& majorIdeologies);

}



#endif // GENERIC_EVENT_UPDATERS