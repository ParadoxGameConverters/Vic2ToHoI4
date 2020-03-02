#include "DivisionTemplate.h"
#include "ParserHelpers.h"
#include "RegimentTypeGroup.h"



HoI4::DivisionTemplateType::DivisionTemplateType(std::istream& theStream)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword(std::regex("regiments"), [this](const std::string& unused, std::istream& theStream){
		HoI4::RegimentTypeGroup regimentsGroup(theStream);
		regiments = regimentsGroup.takeRegimentTypes();
	});
	registerKeyword(std::regex("support"), [this](const std::string& unused, std::istream& theStream){
		HoI4::RegimentTypeGroup supportRegimentsGroup(theStream);
		supportRegiments = supportRegimentsGroup.takeRegimentTypes();
	});
	registerKeyword(std::regex("priority"),  commonItems::ignoreItem);

	parseStream(theStream);
}