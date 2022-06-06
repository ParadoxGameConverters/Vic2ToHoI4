#ifndef EVENTS_FILE_H
#define EVENTS_FILE_H



#include "Event.h"
#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class EventsFile: commonItems::parser
{
  public:
	explicit EventsFile(std::istream& theStream);

	auto&& takeEvents() { return std::move(theEvents); }

  private:
	std::vector<Event> theEvents;
};

} // namespace HoI4



#endif // EVENTS_FILE_H