#include "StateHistory.h"
#include "StateBuildings.h"
#include "ParserHelpers.h"



HoI4::StateHistory::StateHistory(std::istream& theStream)
{
	registerKeyword(std::regex("owner"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ownerString(theStream);
		owner = ownerString.getString();
	});
	registerKeyword(std::regex("buildings"), [this](const std::string& unused, std::istream& theStream) {
		HoI4::StateBuildings theBuildings(theStream);
		civFactories = theBuildings.getCivFactories();
		milFactories = theBuildings.getMilFactories();
		dockyards = theBuildings.getDockyards();
	});
	registerKeyword(std::regex("[a-zA-Z0-9\\._]+"), commonItems::ignoreItem);

	parseStream(theStream);
}