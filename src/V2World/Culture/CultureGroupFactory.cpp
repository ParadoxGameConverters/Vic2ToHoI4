#include "CultureGroupFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::CultureGroupFactory::CultureGroupFactory()
{
	registerKeyword("union", commonItems::ignoreItem);
	registerKeyword("leader", commonItems::ignoreItem);
	registerKeyword("unit", commonItems::ignoreItem);
	registerKeyword("is_overseas", commonItems::ignoreItem);
	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureName, std::istream& theStream) {
		cultureGroup.push_back(cultureName);
		commonItems::ignoreItem(cultureName, theStream);
	});
}



std::vector<std::string> Vic2::CultureGroupFactory::getCultureGroup(std::istream& theStream)
{
	cultureGroup.clear();
	parseStream(theStream);
	return cultureGroup;
}