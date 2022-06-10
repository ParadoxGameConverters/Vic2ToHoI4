#include "src/HOI4World/OperativeNames/OperativeNamesSetDetails.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::OperativeNamesSet::Details::Details()
{
	registerKeyword("name", [this](std::istream& theStream) {
		operativeNamesSet->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("type", commonItems::ignoreItem);
	registerKeyword("fallback_name", commonItems::ignoreItem);
	registerKeyword("unique", [this](std::istream& theStream) {
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