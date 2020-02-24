#include "EventsFile.h"
#include "ParserHelpers.h"



HoI4::EventsFile::EventsFile(std::istream& theStream)
{
	registerKeyword("add_namespace", commonItems::ignoreItem);
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& type, std::istream& theStream) {
		const Event theEvent(type, theStream);
		theEvents.push_back(theEvent);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}