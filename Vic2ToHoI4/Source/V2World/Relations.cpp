#include "Relations.h"
#include "ParserHelpers.h"



Vic2::Relations::Relations(const std::string& theTag, std::istream& theStream): tag(theTag)
{
	registerKeyword("value", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt valueInt(theStream);
		value = valueInt.getInt();
	});
	registerKeyword("level", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt levelInt(theStream);
		level = levelInt.getInt();
	});
	registerKeyword("military_access", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString stateString(theStream);
		militaryAccess = (stateString.getString() == "yes");
	});
	registerKeyword("last_send_diplomat", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString dateString(theStream);
		lastSentDiplomat = date(dateString.getString());
	});
	registerKeyword("last_war", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString dateString(theStream);
		lastWar = date(dateString.getString());
	});
	registerKeyword("truce_until", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString dateString(theStream);
		truceUntil = date(dateString.getString());
	});
	registerKeyword("influence_value", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt valueInt(theStream);
		influenceValue = valueInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}