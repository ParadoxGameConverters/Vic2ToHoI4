#include "SupplyArea.h"
#include "ParserHelpers.h"



SupplyArea::SupplyArea(std::istream& theStream)
{
	registerKeyword(std::regex("id"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt idInt(theStream);
		ID = idInt.getInt();
	});
	registerKeyword(std::regex("value"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt valueInt(theStream);
		value = valueInt.getInt();
	});
	registerKeyword(std::regex("states"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList stateIntList(theStream);
		states = stateIntList.getInts();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}