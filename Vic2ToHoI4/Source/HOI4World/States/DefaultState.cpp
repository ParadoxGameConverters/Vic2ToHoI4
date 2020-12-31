#include "DefaultState.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "StateHistory.h"



HoI4::DefaultState::DefaultState(std::istream& theStream)
{
	registerKeyword("impassable", [this](const std::string& unused, std::istream& theStream) {
		impassable = true;
		commonItems::ignoreItem(unused, theStream);
	});
	registerKeyword("provinces", [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList provinceNums(theStream);
		for (auto province: provinceNums.getInts())
		{
			provinces.insert(province);
		}
	});
	registerKeyword("history", [this](const std::string& unused, std::istream& theStream) {
		StateHistory theHistory(theStream);
		civFactories = theHistory.getCivFactories();
		milFactories = theHistory.getMilFactories();
		dockyards = theHistory.getDockyards();
		ownerTag = theHistory.getOwner();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}