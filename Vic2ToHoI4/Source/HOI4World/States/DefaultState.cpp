#include "DefaultState.h"
#include "StateHistory.h"
#include "ParserHelpers.h"



HoI4::DefaultState::DefaultState(std::istream& theStream)
{
	registerKeyword(std::regex("impassable"), [this](const std::string& unused, std::istream& theStream) {
		impassable = true;
		commonItems::ignoreItem(unused, theStream);
	});
	registerKeyword(std::regex("provinces"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList provinceNums(theStream);
		for (auto province : provinceNums.getInts())
		{
			provinces.insert(province);
		}
	});
	registerKeyword(std::regex("history"), [this](const std::string& unused, std::istream& theStream) {
		StateHistory theHistory(theStream);
		civFactories = theHistory.getCivFactories();
		milFactories = theHistory.getMilFactories();
		dockyards = theHistory.getDockyards();
		ownerTag = theHistory.getOwner();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}