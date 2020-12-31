#include "SupplyArea.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::SupplyArea::SupplyArea(std::istream& theStream)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt idInt(theStream);
		ID = idInt.getInt();
	});
	registerKeyword("value", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt valueInt(theStream);
		value = valueInt.getInt();
	});
	registerKeyword("states", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList stateIntList(theStream);
		states = stateIntList.getInts();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}