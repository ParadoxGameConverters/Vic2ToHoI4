#ifndef NAVAL_TREATY_EVENT_UPDATERS_H
#define NAVAL_TREATY_EVENT_UPDATERS_H



#include <set>
#include "Event.h"



namespace HoI4
{

void updateNavalTreatyEventOne(Event& event, const std::set<std::string>& majorIdeologies);
	
}




#endif // NAVAL_TREATY_EVENT_UPDATERS_H