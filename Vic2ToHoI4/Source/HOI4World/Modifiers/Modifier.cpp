#include "Modifier.h"
#include "ParserHelpers.h"



HoI4::Modifier::Modifier(const std::string& modifierName, std::istream& theStream): name(modifierName)
{
	registerKeyword("icon", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString iconString(theStream);
		icon = iconString.getString();
	});
	registerKeyword("enable", [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringOfItem enableString(theStream);
		enable = enableString.getString();
	});
	registerKeyword("remove_trigger", [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringOfItem removeTriggerString(theStream);
		removeTrigger = removeTriggerString.getString();
	});
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& theEffect, std::istream& theStream) {
		commonItems::singleString effectsString(theStream);
		effects.insert(make_pair(theEffect, effectsString.getString()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}
