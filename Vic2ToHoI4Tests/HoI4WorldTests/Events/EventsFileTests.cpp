#include "../Vic2ToHoI4/Source/HOI4World/Events/EventsFile.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Events_EventsFile, EventsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::EventsFile theEventsFile(input);

	ASSERT_TRUE(theEventsFile.takeEvents().empty());
}


TEST(HoI4World_Events_EventsFile, EventsCanBeAdded)
{
	std::stringstream input;
	input << "country_event = {\n";
	input << "}";
	HoI4::EventsFile theEventsFile(input);

	std::stringstream eventInput;
	HoI4::Event expectedEvent("country_event", eventInput);

	ASSERT_EQ(1, theEventsFile.takeEvents().size());
}