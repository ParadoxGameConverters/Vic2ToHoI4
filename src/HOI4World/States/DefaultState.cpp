#include "DefaultState.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "StateHistory.h"



HoI4::DefaultState::DefaultState(std::istream& theStream)
{
	registerKeyword("impassable", [this](const std::string& unused, std::istream& theStream) {
		impassable = true;
		commonItems::ignoreItem(unused, theStream);
	});
	registerKeyword("provinces", [this](std::istream& theStream) {
		commonItems::intList provinceNums(theStream);
		for (auto province: provinceNums.getInts())
		{
			provinces.insert(province);
		}
	});
	registerKeyword("history", [this](std::istream& theStream) {
		StateHistory theHistory(theStream);
		civFactories = theHistory.getCivFactories();
		milFactories = theHistory.getMilFactories();
		dockyards = theHistory.getDockyards();
		ownerTag = theHistory.getOwner();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}