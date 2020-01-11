#include "Event.h"
#include "ParserHelpers.h"



HoI4::Event::Event(const std::string& theType, std::istream& theStream):
	type(theType)
{
	registerKeyword(std::regex("id"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString idString(theStream);
			id = idString.getString();
		}
	);
	registerKeyword(std::regex("title"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString titleString(theStream);
			title = titleString.getString();
		}
	);
	registerKeyword(std::regex("desc"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfItem descriptionString(theStream);
			descriptions.push_back("desc " + descriptionString.getString());
		}
	);
	registerKeyword(std::regex("picture"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString pictureString(theStream);
			picture = pictureString.getString();
		}
	);
	registerKeyword(std::regex("major"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString majorString(theStream);
			majorEvent = (majorString.getString() == "yes");
		}
	);
	registerKeyword(std::regex("is_triggered_only"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString triggeredString(theStream);
			triggeredOnly = (triggeredString.getString() == "yes");
		}
	);
	registerKeyword(std::regex("hidden"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::singleString hiddenString(theStream);
			hidden = (hiddenString.getString() == "yes");
		}
	);
	registerKeyword(std::regex("trigger"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject triggerString(theStream);
			trigger = triggerString.getString();
		}
	);
	registerKeyword(std::regex("mean_time_to_happen"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject MTTHString(theStream);
			meanTimeToHappen = MTTHString.getString();
		}
	);
	registerKeyword(std::regex("immediate"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject immediateString(theStream);
			immediate = immediateString.getString();
		}
	);
	registerKeyword(std::regex("option"), [this](const std::string& unused, std::istream& theStream)
		{
			commonItems::stringOfObject optionString(theStream);
			options.push_back(optionString.getString());
		}
	);

	parseStream(theStream);
}