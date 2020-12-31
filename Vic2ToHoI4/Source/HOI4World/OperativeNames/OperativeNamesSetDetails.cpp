#include "OperativeNamesSetDetails.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::OperativeNamesSet::Details::Details()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		operativeNamesSet->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("type", commonItems::ignoreItem);
	registerKeyword("fallback_name", commonItems::ignoreItem);
	registerKeyword("unique", [this](const std::string& unused, std::istream& theStream) {
		operativeNamesSet->names = commonItems::stringList{theStream}.getStrings();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}



std::unique_ptr<HoI4::OperativeNamesSet> HoI4::OperativeNamesSet::Details::getOperativeNamesSet(std::istream& theStream)
{
	operativeNamesSet = std::make_unique<OperativeNamesSet>();
	parseStream(theStream);
	return std::move(operativeNamesSet);
}