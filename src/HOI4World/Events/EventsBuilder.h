#ifndef EVENTS_BUILDER_H
#define EVENTS_BUILDER_H



#include "Events.h"
#include <memory>



namespace HoI4
{

class Events::Builder
{
  public:
	Builder() { events = std::make_unique<Events>(); }
	std::unique_ptr<Events> Build() { return std::move(events); }

	Builder& addEventNumber(const std::string& eventName, int eventNumber)
	{
		events->eventNumbers.insert(std::make_pair(eventName, eventNumber));
		return *this;
	}

  private:
	std::unique_ptr<Events> events;
};

} // namespace HoI4



#endif // EVENTS_BUILDER_H