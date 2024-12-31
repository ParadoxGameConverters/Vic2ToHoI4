#include "src/HOI4World/Map/AdjacencyRule.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::AdjacencyRule::AdjacencyRule(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		name = commonItems::singleString{theStream}.getString();
	});
	registerRegex("contested|enemy|friend|neutral", [this](const std::string& rule, std::istream& theStream) {
		rules[rule] = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("required_provinces", [this](std::istream& theStream) {
		requiredProvinces = commonItems::intList{theStream}.getInts();
	});
	registerKeyword("is_disabled", [this](std::istream& theStream) {
		isDisabledStr = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("icon", [this](std::istream& theStream) {
		icon = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("offset", [this](std::istream& theStream) {
		offset = commonItems::doubleList{theStream}.getDoubles();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}