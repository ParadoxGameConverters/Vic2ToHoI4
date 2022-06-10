#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Events/EventsFile.h"
#include <sstream>



TEST(HoI4World_Events_EventsFileTests, EventsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::EventsFile theEventsFile(input);

	ASSERT_TRUE(theEventsFile.takeEvents().empty());
}


TEST(HoI4World_Events_EventsFileTests, EventsCanBeAdded)
{
	std::stringstream input;
	input << "country_event = {\n";
	input << "}";
	HoI4::EventsFile theEventsFile(input);

	std::stringstream eventInput;
	HoI4::Event expectedEvent("country_event", eventInput);

	ASSERT_EQ(1, theEventsFile.takeEvents().size());
}