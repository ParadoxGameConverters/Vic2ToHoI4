#include "src/HOI4World/Events/EventsFile.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::EventsFile::EventsFile(std::istream& theStream)
{
	registerKeyword("add_namespace", commonItems::ignoreItem);
	registerRegex(commonItems::catchallRegex, [this](const std::string& type, std::istream& theStream) {
		const Event theEvent(type, theStream);
		theEvents.push_back(theEvent);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}