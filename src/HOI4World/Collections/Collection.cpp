#include "src/HOI4World/Collections/Collection.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"



HoI4::Collection::Collection(const std::string& id, std::istream& theStream): id(std::move(id))
{
	registerKeyword("input", [this](std::istream& theStream) {
		input = commonItems::getString(theStream);
	});
	registerKeyword("name", [this](std::istream& theStream) {
		name = commonItems::getString(theStream);
	});
	registerKeyword("operators", [this](std::istream& theStream) {
		operators = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);
	clearRegisteredKeywords();
}

bool HoI4::Collection::operator==(const Collection& other) const
{
	return id == other.id && input == other.input && name == other.name && operators == other.operators;
}