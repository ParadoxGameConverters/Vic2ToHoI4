#ifndef EVENTS_MOCK_H
#define EVENTS_MOCK_H



#include "HOI4World/Events/Events.h"
#include "gmock/gmock.h"



class mockEvents final: public HoI4::Events
{
  public:
	MOCK_METHOD(std::optional<int>, getEventNumber, (const std::string& eventName), (const, override));
};



#endif // EVENTS_MOCK_H