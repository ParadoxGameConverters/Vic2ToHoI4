#include "DivisionTemplate.h"
#include "ParserHelpers.h"
#include "RegimentTypeGroup.h"



HoI4::DivisionTemplateType::DivisionTemplateType(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("regiments", [this](const std::string& unused, std::istream& theStream) {
		const RegimentTypeGroup regimentsGroup(theStream);
		regiments = regimentsGroup.takeRegimentTypes();
	});
	registerKeyword("support", [this](const std::string& unused, std::istream& theStream) {
		const RegimentTypeGroup supportRegimentsGroup(theStream);
		supportRegiments = supportRegimentsGroup.takeRegimentTypes();
	});
	registerKeyword("priority", commonItems::ignoreItem);
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}