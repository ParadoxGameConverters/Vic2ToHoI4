#include "DivisionTemplate.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "RegimentTypeGroup.h"



HoI4::DivisionTemplateType::DivisionTemplateType(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("regiments", [this](std::istream& theStream) {
		const RegimentTypeGroup regimentsGroup(theStream);
		regiments = regimentsGroup.takeRegimentTypes();
	});
	registerKeyword("support", [this](std::istream& theStream) {
		const RegimentTypeGroup supportRegimentsGroup(theStream);
		supportRegiments = supportRegimentsGroup.takeRegimentTypes();
	});
	registerKeyword("required_technology", [this](std::istream& theStream) {
		requiredTechnologies.push_back(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("priority", commonItems::ignoreItem);
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}