#include "src/HOI4World/Landmarks/LandmarkModifiers.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::LandmarkModifiers::LandmarkModifiers(std::istream& theStream)
{
	registerKeyword("enable_for_controllers", [this](std::istream& theStream) {
		enabledControllers = commonItems::stringList{theStream}.getStrings();
	});
	registerKeyword("modifiers", [this](std::istream& theStream) {
		modifiers = commonItems::stringOfItem{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}