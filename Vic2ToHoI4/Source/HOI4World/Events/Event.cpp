#include "Event.h"
#include "ParserHelpers.h"



HoI4::Event::Event(const std::string& theType, std::istream& theStream):
	type(theType)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString idString(theStream);
			id = idString.getString();
		}
	);
	registerKeyword("title", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString titleString(theStream);
			title = titleString.getString();
		}
	);
	registerKeyword("desc", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfItem descriptionString(theStream);
			descriptions.push_back(descriptionString.getString());
		}
	);
	registerKeyword("picture", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString pictureString(theStream);
			picture = pictureString.getString();
		}
	);
	registerKeyword("major", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString majorString(theStream);
			majorEvent = (majorString.getString() == "yes");
		}
	);
	registerKeyword("is_triggered_only", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString triggeredString(theStream);
			triggeredOnly = (triggeredString.getString() == "yes");
		}
	);
	registerKeyword("hidden", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString hiddenString(theStream);
			hidden = (hiddenString.getString() == "yes");
		}
	);
	registerKeyword("trigger", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject triggerString(theStream);
			trigger = triggerString.getString();
		}
	);
	registerKeyword("mean_time_to_happen", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject MTTHString(theStream);
			meanTimeToHappen = MTTHString.getString();
		}
	);
	registerKeyword("immediate", [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject immediateString(theStream);
			immediate = immediateString.getString();
		}
	);
	registerKeyword("option", [this](const std::string& unused, std::istream& theStream)
		{
			EventOption theOption(theStream);
			options.push_back(theOption);
		}
	);

	parseStream(theStream);
	clearRegisteredKeywords();
}