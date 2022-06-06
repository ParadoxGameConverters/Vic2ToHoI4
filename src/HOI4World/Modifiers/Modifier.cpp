#include "Modifier.h"
#include "external/common_items/ParserHelpers.h"



HoI4::Modifier::Modifier(const std::string& modifierName, std::istream& theStream): name(modifierName)
{
	registerKeyword("icon", [this](const std::string& unused, std::istream& theStream) {
		icon = commonItems::singleString(theStream).getString();
	});
	registerKeyword("enable", [this](const std::string& unused, std::istream& theStream) {
		enable = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("remove_trigger", [this](const std::string& unused, std::istream& theStream) {
		removeTrigger = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& theEffect, std::istream& theStream) {
		effects.insert(make_pair(theEffect, commonItems::singleString(theStream).getString()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}
