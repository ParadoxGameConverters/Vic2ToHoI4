#include "Event.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Event::Event(const std::string& _type, std::istream& theStream): type(_type)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString idString(theStream);
		id = idString.getString();
	});
	registerKeyword("title", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString titleString(theStream);
		title = titleString.getString();
	});
	registerKeyword("desc", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem descriptionString(theStream);
		descriptions.push_back(descriptionString.getString());
	});
	registerKeyword("picture", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString pictureString(theStream);
		picture = pictureString.getString();
	});
	registerKeyword("major", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString majorString(theStream);
		majorEvent = (majorString.getString() == "yes");
	});
	registerKeyword("is_triggered_only", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString triggeredString(theStream);
		triggeredOnly = (triggeredString.getString() == "yes");
	});
	registerKeyword("hidden", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString hiddenString(theStream);
		hidden = (hiddenString.getString() == "yes");
	});
	registerKeyword("trigger", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem triggerString(theStream);
		trigger = triggerString.getString();
	});
	registerKeyword("fire_only_once", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString fireOnlyOnceString(theStream);
		fireOnlyOnce = (fireOnlyOnceString.getString() == "yes");
	});
	registerKeyword("mean_time_to_happen", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem MTTHString(theStream);
		meanTimeToHappen = MTTHString.getString();
	});
	registerKeyword("immediate", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem immediateString(theStream);
		immediate = immediateString.getString();
	});
	registerKeyword("option", [this](const std::string& unused, std::istream& theStream) {
		const EventOption theOption(theStream);
		options.push_back(theOption);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}